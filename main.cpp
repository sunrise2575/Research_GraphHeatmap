#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>
#include <string>
#include <map>
#include <set>
#include <fstream>

static void tsv2mat(std::string const in_path, unsigned int GRIDWIDTH, unsigned int ADDVAL, cv::Mat & out) {
	std::ifstream ifs(in_path);
	std::string line;
	char * context;
	// get size
	unsigned int truemax = 0;
	unsigned long long edges = 0;
	while (std::getline(ifs, line)) {
		if (line[0] == '#') continue;
		char * ptr; char *str = (char *)line.c_str();
		ptr = strtok(str, "\t");
		unsigned int src = atoi(ptr);
		ptr = strtok(nullptr, "\t");
		unsigned int dst = atoi(ptr);
		unsigned int max = std::max(src, dst);
		if (max > truemax) truemax = max;
		edges++;
	}
	
	unsigned int vertices = truemax + 1;
	unsigned int grids = (vertices % GRIDWIDTH) ? (vertices / GRIDWIDTH + 1) : (vertices / GRIDWIDTH);
	printf("Vertices : %d\n", vertices);
	printf("Edges    : %lld\n", edges);
	printf("GridSize : %d\n", GRIDWIDTH);
	printf("ImageSize: %d x %d\n", grids, grids);
	out = cv::Mat::zeros(grids, grids, CV_8UC1);

	ifs.close();
	ifs.open(in_path);
	while (std::getline(ifs, line)) {
		if (line[0] == '#') continue;
		char * ptr; char *str = (char *)line.c_str();
		ptr = strtok(str, "\t");
		unsigned int src = atoi(ptr);
		ptr = strtok(nullptr, "\t");
		unsigned int dst = atoi(ptr);
		auto & cur_pixel = out.at<unsigned char>(src / GRIDWIDTH, dst / GRIDWIDTH);
		if ((unsigned int)cur_pixel + ADDVAL <= 255) cur_pixel += (unsigned char)ADDVAL;
	}
	ifs.close();
}

// <key, (variable address, variable size)>
//using arg_kv_value_t = std::pair<void *, std::function<void(std::string &)>>;
using arg_kv_t = std::map<std::string, std::function<void(std::string &)>>;

static void usage(char * argv0, arg_kv_t& arg_kv) {
	fprintf(stderr,
			"Usage: %s --[KEY]=[VALUE]\n"
			"\t[KEYs]\n"
			, argv0);

	for (auto iter = arg_kv.begin(); iter != arg_kv.end(); iter++) {
		fprintf(stderr, "\t\t%s\n", iter->first.c_str());
	}
	fprintf(stderr, "\n");
	exit(EXIT_FAILURE);
}

static void arg_parse(int argc, char * argv[], arg_kv_t& arg_kv) {
	if (argc < 2) usage(argv[0], arg_kv);

	// parse and store all arg to vector kv
	std::map<std::string, std::string> _kv;
	for (int i = 1; i < argc; i++) {
		if (strlen(argv[i]) < 5) {
			fprintf(stderr, "Argument %s doesn't satisfy '--[KEY]=[VALUE]' form\n\n", argv[i]);
			usage(argv[0], arg_kv);
		}

		if (argv[i][0] != '-' || argv[i][1] != '-') {
			fprintf(stderr, "Argument %s doesn't satisfy '--[KEY]=[VALUE]' form\n\n", argv[i]);
			usage(argv[0], arg_kv);
		}

		std::string s = argv[i];
		auto eq_pos = s.find('=');
		auto key = s.substr(2, eq_pos - 2);
		auto value = s.substr(eq_pos + 1, s.size() - eq_pos - 1);

		if (key.size() == 0 || value.size() == 0) {
			fprintf(stderr, "Argument %s doesn't satisfy '--[KEY]=[VALUE]' form\n\n", argv[i]);
			usage(argv[0], arg_kv);
		}

		_kv[key] = value;
	}

	for (auto _kv_iter = _kv.begin(); _kv_iter != _kv.end(); ++_kv_iter) {
		auto arg_kv_iter = arg_kv.find(_kv_iter->first);
		if (arg_kv_iter != arg_kv.end()) {
			arg_kv_iter->second(_kv_iter->second);
		} else {
			fprintf(stderr, "Key %s is unrecognized\n\n", _kv_iter->first.c_str());
			usage(argv[0], arg_kv);
		}
	}
}

int main(int argc, char * argv[]) {
	std::string input_path, output_path;
	unsigned int gwidth = 65536, bincre = 1;

	arg_kv_t arg_kv;
	arg_kv["input"] = [&](std::string & val){ input_path = val; };
	arg_kv["output"] = [&](std::string & val){ output_path = val; };
	arg_kv["grid-width"] = [&](std::string & val){ gwidth = std::atoi(val.c_str()); };
	arg_kv["brightness-increment"] = [&](std::string & val){ bincre = std::atoi(val.c_str());};
	arg_parse(argc, argv, arg_kv);

	cv::Mat matrix(1, 1, CV_8UC1);
	tsv2mat(input_path, gwidth, bincre, matrix);
	cv::imwrite(output_path, matrix);

	return 0;
}
