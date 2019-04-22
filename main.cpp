#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>
#include <fstream>
#include <string>

#include "arg_kv_parser.h"

#define BASIC_GWIDTH 2048
#define BASIC_BINCRE 1

static void get_vertices(
		std::string const & in_path,
		unsigned int & vertices,
		unsigned long long & edges)
{
	std::ifstream ifs(in_path);
	std::string line;

	unsigned int grids = 0;
	char * context;
	// get size
	unsigned int truemax = 0;
	edges = 0;
	while (std::getline(ifs, line)) {
		if (line[0] == '#') {
			continue;
		}

		char * ptr, *str = (char *)line.c_str();

		ptr = strtok(str, "\t");
		unsigned int src = atoi(ptr);
		ptr = strtok(nullptr, "\t");
		unsigned int dst = atoi(ptr);

		unsigned int max = std::max(src, dst);
		if (max > truemax) {
			truemax = max;
		}

		edges++;
	}
	ifs.close();

	vertices = truemax + 1;
}

static void tsv2mat(
		std::string const & in_path,
		cv::Mat & out,
		unsigned int gwidth,
		unsigned int bincre,
		unsigned int vertices = 0)
{
	unsigned int grids = 0;
	unsigned long long edges = 0;

	if (!vertices) {
		get_vertices(in_path, vertices, edges);
	}

	grids = (vertices % gwidth) ? (vertices / gwidth + 1) : (vertices / gwidth);

	printf("Vertices : %d\n", vertices);
	if (edges) {
		printf("Edges    : %lld\n", edges);
	}
	printf("GridSize : %d\n", gwidth);
	printf("ImageSize: %d x %d\n", grids, grids);

	out = cv::Mat::zeros(grids, grids, CV_8UC1);

	// This could be dangerous! 65536*65536==UINT_MAX, INT_MAX == UINTMAX >> 1
	cv::Mat count = cv::Mat::zeros(grids, grids, CV_32SC1);

	std::ifstream ifs(in_path);
	std::string line;
	while (std::getline(ifs, line)) {
		if (line[0] == '#') {
			continue;
		}

		char * ptr, *str = (char *)line.c_str();

		ptr = strtok(str, "\t");
		unsigned int src = atoi(ptr);
		ptr = strtok(nullptr, "\t");
		unsigned int dst = atoi(ptr);

		auto & cur_pixel = out.at<unsigned char>(src / gwidth, dst / gwidth);

		if ((unsigned int)cur_pixel + bincre <= 255) {
			cur_pixel += (unsigned char)bincre;
		}
	}

	ifs.close();
}

static void tsv2mat_logscale(
		std::string const & in_path,
		cv::Mat & out,
		unsigned int gwidth,
		unsigned int bincre,
		unsigned int vertices = 0)
{
	unsigned int grids = 0;
	unsigned long long edges = 0;

	if (!vertices) {
		get_vertices(in_path, vertices, edges);
	}

	grids = (vertices % gwidth) ? (vertices / gwidth + 1) : (vertices / gwidth);

	printf("Vertices : %d\n", vertices);
	if (edges) {
		printf("Edges    : %lld\n", edges);
	}
	printf("GridSize : %d\n", gwidth);
	printf("ImageSize: %d x %d\n", grids, grids);

	out = cv::Mat::zeros(grids, grids, CV_8UC1);

	// This could be dangerous! 65536*65536==UINT_MAX, INT_MAX == UINTMAX >> 1
	cv::Mat count = cv::Mat::zeros(grids, grids, CV_32SC1);

	std::ifstream ifs(in_path);
	std::string line;
	while (std::getline(ifs, line)) {
		if (line[0] == '#') {
			continue;
		}

		char * ptr, *str = (char *)line.c_str();

		ptr = strtok(str, "\t");
		unsigned int src = atoi(ptr);
		ptr = strtok(nullptr, "\t");
		unsigned int dst = atoi(ptr);

		count.at<int>(src / gwidth, dst / gwidth)++;
	}

	for (unsigned int row = 0; row < grids; row++) {
		for (unsigned int col = 0; col < grids; col++) {
			out.at<unsigned char>(row, col) += bincre * std::log2(count.at<int>(row, col));
		}
	}

	ifs.close();
}

int main(int argc, char * argv[]) {
	std::string input_path, output_path;
	unsigned int gwidth=BASIC_GWIDTH, bincre=BASIC_BINCRE, vertices=0;
	bool logscale = false;

	arg_kv_t arg_kv;
	arg_kv["input"] = [&](std::string & val){ input_path = val; };
	arg_kv["output"] = [&](std::string & val){ output_path = val; };
	arg_kv["grid-width"] = [&](std::string & val){ gwidth = std::atoi(val.c_str()); };
	arg_kv["brightness-increment"] = [&](std::string & val){ bincre = std::atoi(val.c_str());};
	arg_kv["vertices"] = [&](std::string & val){ vertices = std::atoi(val.c_str());};
	arg_kv["logscale"] = [&](std::string & val){ logscale = true; };
	
	std::vector<std::string> argv_arr(argc);
	for (unsigned int i = 0; i < (unsigned int)argc; i++) {
		argv_arr[i] = std::string(argv[i]);
	}
	arg_parse(argv_arr, arg_kv);

	cv::Mat matrix(1, 1, CV_8UC1);

	if (logscale) {
		tsv2mat_logscale(input_path, matrix, gwidth, bincre, vertices);
	} else {
		tsv2mat(input_path, matrix, gwidth, bincre, vertices);
	}
	cv::imwrite(output_path, matrix);

	return 0;
}
