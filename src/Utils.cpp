#include "Utils.h"

#include <string>
#include <unordered_map>
#include <unordered_set>

namespace httplib
{
	namespace constant
	{
		const std::unordered_set<std::string> REQUEST_TYPES = {"GET", "HEAD", "POST", "PUT", "DELETE", "CONNECT", "OPTIONS", "TRACE"};
		const std::unordered_set<std::string> HTTP_VERSIONS = {"HTTP/1.1", "HTTP/1.0"};
	}
}

std::string httplib::utils::jsonify(std::unordered_map<std::string, std::string> dict)
{
	return "";
}


