#include "HTTPResponse.h"
#include <cstring>

httplib::HTTPResponse::HTTPResponse()
{}

int httplib::HTTPResponse::serialize(char **arg_p)
{
	std::string output;
	output += version + " " + status_code + " " + status_msg + "\r\n";
	for (auto each: header)
	{
		output += each.first + ": " + each.second + "\r\n";
	}
	output += "\r\n";
	char *msg = (char *)malloc(sizeof(char) * (output.size() + body_length));
	memcpy(msg, output.c_str(), output.size());
	char *pbody = msg + output.size();
	memcpy(pbody, body, body_length);
	*arg_p = msg;
	return output.size() + body_length;
}

void httplib::HTTPResponse::setHeader(std::string key, std::string val)
{
	header[key] = val;
}


std::string httplib::HTTPResponse::getHeader(std::string key)
{
	if (header.find(key) == header.end()){
		return "";
	}
	return header[key];
}

void httplib::HTTPResponse::setBody(const char *arg_body, int arg_length)
{
	body = arg_body;
	body_length = arg_length;
}

void httplib::HTTPResponse::setStatus(std::string code, std::string msg)
{
	this -> status_code = code;
	this -> status_msg = msg;
}

void httplib::HTTPResponse::setVersion(std::string version)
{
	this -> version = version;
}
