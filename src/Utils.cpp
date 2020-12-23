#include "Utils.h"
#include "HTTPRequest.h"

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

void httplib::rules::decodeRequestUrl(const char *url, httplib::HTTPRequest &req)
{
	std::string s = std::string(url);
	int idx;
	if ((idx = s.find('?')) == -1) {
		req.setUrl(url);
		return;
	}
	req.setUrl(s.substr(0, idx).c_str());
	const char *p = s.c_str() + idx + 1;
	std::string key;
	std::string val;
	bool readKey = true;
	while(*p != 0)
	{
		if (readKey){
			if (*p == '='){
				readKey = false;
			}else{
				key += *p;
			}
			p++;
			continue;
		}else{
			if (*p == '&'){
				readKey = true;
				req.setParam(key.c_str(), val.c_str());
				key = "";
				val = "";
			}else{
				val += *p;
			}
			p++;
			continue;
		}
	}
	if (!readKey){
		req.setParam(key.c_str(), val.c_str());
	}
}

void httplib::rules::decodeFormUrlencoded(const char *input, httplib::HTTPRequest &req)
{
	std::string s = std::string(input);
	const char *p = s.c_str();
	std::string key;
	std::string val;
	bool readKey = true;
	while(*p != 0)
	{
		if (readKey){
			if (*p == '='){
				readKey = false;
			}else{
				key += *p;
			}
			p++;
			continue;
		}else{
			if (*p == '&'){
				readKey = true;
				req.setForm(key.c_str(), val.c_str());
				key = "";
				val = "";
			}else{
				val += *p;
			}
			p++;
			continue;
		}
	}
	if (!readKey){
		req.setForm(key.c_str(), val.c_str());
	}
}



void httplib::initializeGlobalVar()
{
	// request types
	std::string tmp[] = {"GET", "HEAD", "POST", "PUT", "DELETE", "CONNECT", "OPTIONS", "TRACE"};
	httplib::rules::valid_req_types = std::unordered_set<std::string>(tmp, tmp + 8);

	// http version
}

