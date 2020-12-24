#ifndef UTILS_H
#define UTILS_H

#include "HTTPRequest.h"

#include <string>
#include <unordered_map>
#include <unordered_set>

namespace httplib
{
	namespace constant
	{
		extern const std::unordered_set<std::string> REQUEST_TYPES;
		extern const std::unordered_set<std::string> HTTP_VERSIONS;
	}
	namespace utils
	{
		std::string jsonify(std::unordered_map<std::string, std::string> dict);
	}
}

#endif