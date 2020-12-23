#include "HTTPRequest.h"

#include <string>
#include <unordered_map>

httplib::HTTPRequest::HTTPRequest()
{}

std::string httplib::HTTPRequest::toString(){
	std::string output;
	output += type + " " + url + " " + version + "\n";
	output += "params:\n";
	for (auto each: params){
		output += each.first + ": " + each.second + "\n";
	}
	output += "headers:\n";
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

void httplib::HTTPRequest::setUrl(const char *url)
{
	this -> url = std::string(url);
}

std::string httplib::HTTPRequest::getUrl()
{
	return url;
}

void httplib::HTTPRequest::setType(const char *type)
{
	this -> type = std::string(type);
}

std::string httplib::HTTPRequest::getType()
{
	return type;
}

void httplib::HTTPRequest::setVersion(const char *version)
{
	this -> version = std::string(version);
}

std::string httplib::HTTPRequest::getVersion()
{
	return version;
}

void httplib::HTTPRequest::setParam(const char *key, const char *val)
{
	params[std::string(key)] = std::string(val);
}

std::string httplib::HTTPRequest::getParam(const char *key)
{	
	std::string s(key);
	if (key == nullptr){
		return std::string("");
	}
	if (params.find(s) == params.end()){
		return std::string("");
	}
	return params[std::string(key)];
}

void httplib::HTTPRequest::setForm(const char *key, const char *val)
{
	form[std::string(key)] = std::string(val);
}

std::string httplib::HTTPRequest::getForm(const char *key)
{	
	std::string s(key);
	if (key == nullptr){
		return std::string("");
	}
	if (form.find(s) == form.end()){
		return std::string("");
	}
	return form[std::string(key)];
}


const char* httplib::HTTPRequest::getBody()
{
	return body;
}
void httplib::HTTPRequest::setBody(char * input){
	body = input;
}

int httplib::HTTPRequest::getBodyLen(){
	return body_len;
}
void httplib::HTTPRequest::setBodyLen(int len){
	body_len = len;
}