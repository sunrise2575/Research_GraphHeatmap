#include "arg_kv_parser.h"

static void usage(
		std::vector<std::string> const & argv,
		arg_kv_t & arg_kv)
{
	fprintf(stderr, "Usage: %s --[KEY]=[VALUE]\n\t[KEYs]\n", argv[0].c_str());

	for (auto iter = arg_kv.begin(); iter != arg_kv.end(); iter++) {
		fprintf(stderr, "\t\t%s\n", iter->first.c_str());
	}
	fprintf(stderr, "\n");
	exit(EXIT_FAILURE);
}

void arg_parse(
		std::vector<std::string> const & argv,
		arg_kv_t & arg_kv)
{
	if (argv.size() < 2) {
		usage(argv, arg_kv);
	}

	// parse and store all arg to vector kv
	std::map<std::string, std::string> _kv;
	for (int i = 1; i < argv.size(); i++) {
		if (argv[i].size() < 5) {
			fprintf(stderr, "Argument %s doesn't satisfy '--[KEY]=[VALUE]' form\n\n", argv[i].c_str());
			usage(argv, arg_kv);
		}

		if (argv[i][0] != '-' || argv[i][1] != '-') {
			fprintf(stderr, "Argument %s doesn't satisfy '--[KEY]=[VALUE]' form\n\n", argv[i].c_str());
			usage(argv, arg_kv);
		}

		std::string s = argv[i];
		auto eq_pos = s.find('=');
		auto key = s.substr(2, eq_pos - 2);
		auto value = s.substr(eq_pos + 1, s.size() - eq_pos - 1);

		if (key.size() == 0 || value.size() == 0) {
			fprintf(stderr, "Argument %s doesn't satisfy '--[KEY]=[VALUE]' form\n\n", argv[i].c_str());
			usage(argv, arg_kv);
		}

		_kv[key] = value;
	}

	for (auto _kv_iter = _kv.begin(); _kv_iter != _kv.end(); ++_kv_iter) {
		auto arg_kv_iter = arg_kv.find(_kv_iter->first);
		if (arg_kv_iter != arg_kv.end()) {
			arg_kv_iter->second(_kv_iter->second);
		} else {
			fprintf(stderr, "Key %s is unrecognized\n\n", _kv_iter->first.c_str());
			usage(argv, arg_kv);
		}
	}
}
