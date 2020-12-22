#include "HTTPRequest.h"

#include <string>
#include <unordered_map>

httplib::HTTPRequest::HTTPRequest()
{}


std::string httplib::HTTPRequest::toString(){
	std::string output;
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