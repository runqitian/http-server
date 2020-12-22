#include "HTTPRequest.h"

#include <string>
#include <unordered_map>

httplib::HTTPRequest::HTTPRequest()
{}

void httplib::HTTPRequest::setBasicInfo(const char *type, const char *url, const char *version)
{
	this -> type = std::string(type);
	this -> url = std::string(url);
	this -> version = std::string(version);
}

std::string httplib::HTTPRequest::toString(){
	std::string output;
	output += type + " " + url + " " + version + "\n";
	for (auto each: header)
	{
		output += each.first + ": " + each.second + "\n";
	}
	return output;
}

void httplib::HTTPRequest::setHeader(std::string key, std::string val)
{
	header[key] = val;
}


std::string httplib::HTTPRequest::getHeader(std::string key)
{
	if (header.find(key) == header.end())
	{
		return "";
	}
	return header[key];
}


std::string httplib::HTTPRequest::getUrl()
{
	return url;
}

std::string httplib::HTTPRequest::getType()
{
	return type;
}

std::string httplib::HTTPRequest::getVersion()
{
	return version;
}