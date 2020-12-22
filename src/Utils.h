#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <unordered_map>
#include <unordered_set>

namespace httplib
{
	void initializeGlobalVar();

	namespace utils
	{
		std::string jsonify(std::unordered_map<std::string, std::string> dict);
	}
	namespace rules
	{
		extern std::unordered_set<std::string> valid_req_types;
		bool checkRequestType(const char *type);
	}
}

#endif