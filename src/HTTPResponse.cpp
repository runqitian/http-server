#include "HTTPResponse.h"

#include <cstring>
#include <cstdlib>

#include <stdexcept>

const char *httplib::HTTPResponse::MSG404 = "404 NOT FOUND";

httplib::HTTPResponse::HTTPResponse()
{}

int httplib::HTTPResponse::serialize(char **pdes)
{
	std::string output;
	output += version + " " + status_code + " " + status_msg + "\r\n";
	for (auto each: header)
	{
		output += each.first + ": " + each.second + "\r\n";
	}
	output += "\r\n";
	char *msg = (char *)malloc(sizeof(char) * (output.size() + body_len));
	memcpy(msg, output.c_str(), output.size());
	char *pbody = msg + output.size();
	memcpy(pbody, body, body_len);
	*pdes = msg;
	return output.size() + body_len;
}

void httplib::HTTPResponse::setHeader(const std::string &key, const std::string &val)
{
	header[key] = val;
}


std::string httplib::HTTPResponse::getHeader(const std::string &key)
{
	if (header.find(key) == header.end()){
		return "";
	}
	return header[key];
}

void httplib::HTTPResponse::setBody(const char *pbody, int len)
{
	body = (char *)malloc(sizeof(char)*len);
	memcpy(body, pbody, len);
	body_len = len;
}

void httplib::HTTPResponse::setStatus(const std::string &code, const std::string &msg)
{
	this -> status_code = code;
	this -> status_msg = msg;
}

void httplib::HTTPResponse::setVersion(const std::string &version)
{
	this -> version = version;
}

void httplib::HTTPResponse::createHtmlResponse(const std::string &text)
{
	setStatus("200", "OK");
	setHeader("Content-Type", "text/html; charset=utf-8");

	int len = text.size();
	setHeader("Content-Length", std::to_string(len));
	setBody(text.c_str(), len);
}

void httplib::HTTPResponse::create404Response()
{
	setStatus("404", "Not Found");
	setHeader("Content-Type", "text/html; charset=utf-8");

	int len = strlen(MSG404);
	setHeader("Content-Length", std::to_string(len));
	setBody(MSG404, len);
}
