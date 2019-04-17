#ifndef __ARG_KV_PARSER_H__
#define __ARG_KV_PARSER_H__

#include <functional>
#include <string>
#include <vector>
#include <map>

using arg_kv_t = std::map<std::string, std::function<void(std::string &)>>;
void arg_parse(std::vector<std::string> const & argv, arg_kv_t & arg_kv);

#endif
