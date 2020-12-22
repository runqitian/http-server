#include "Utils.h"

#include <string>
#include <unordered_map>
#include <unordered_set>

namespace httplib
{
	namespace rules
	{
		std::unordered_set<std::string> valid_req_types;
	}
}

std::string httplib::utils::jsonify(std::unordered_map<std::string, std::string> dict)
{
	return "";
}

bool httplib::rules::checkRequestType(const char *type)
{
	std::string s(type);
	if (valid_req_types.find(s) == valid_req_types.end())
	{
		return false;
	}
	return true;
}


void httplib::initializeGlobalVar()
{
	// request types
	std::string tmp[] = {"GET", "HEAD", "POST", "PUT", "DELETE", "CONNECT", "OPTIONS", "TRACE"};
	httplib::rules::valid_req_types = std::unordered_set<std::string>(tmp, tmp + 8);

}
