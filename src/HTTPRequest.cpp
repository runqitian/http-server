#include "HTTPRequest.h"

#include <cstring>

#include <string>
#include <unordered_map>

httplib::HTTPRequest::HTTPRequest()
{}

httplib::HTTPRequest::HTTPRequest(HTTPRequest& req)
{
	version = req.version;
	type = req.type;
	url = req.url;
	header = req.header;
	params = req.params;
	form = req.form;
	body_len = req.body_len;
	body = (char *)malloc(sizeof(char) * body_len);
	memcpy(body, req.body, body_len);
}

httplib::HTTPRequest::~HTTPRequest()
{
	free(body);
}

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

void httplib::HTTPRequest::setHeader(const std::string &key, const std::string &val)
{
	header[key] = val;
}


std::string httplib::HTTPRequest::getHeader(const std::string &key)
{
	if (header.find(key) == header.end())
	{
		return "";
	}
	return header[key];
}

void httplib::HTTPRequest::decodeUrl(const std::string &url)
{
	int idx;
	if ((idx = url.find('?')) == -1) {
		this -> url = url;
		return;
	}
	this -> url = url.substr(0, idx);
	const char *p = url.c_str() + idx + 1;
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
				this -> setParam(key, val);
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
		this -> setParam(key, val);
	}
}

std::string httplib::HTTPRequest::getUrl()
{
	return url;
}

void httplib::HTTPRequest::setType(const std::string &type)
{
	this -> type = type;
}

std::string httplib::HTTPRequest::getType()
{
	return type;
}

void httplib::HTTPRequest::setVersion(const std::string &version)
{
	this -> version = version;
}

std::string httplib::HTTPRequest::getVersion()
{
	return version;
}

void httplib::HTTPRequest::setParam(const std::string &key, const std::string &val)
{
	params[key] = val;
}

std::string httplib::HTTPRequest::getParam(const std::string &key)
{	
	if (params.find(key) == params.end()){
		return std::string("");
	}
	return params[key];
}

void httplib::HTTPRequest::setForm(const std::string &key, const std::string &val)
{
	form[key] = val;
}

std::string httplib::HTTPRequest::getForm(const std::string &key)
{	
	if (form.find(key) == form.end()){
		return std::string("");
	}
	return form[key];
}


const char* httplib::HTTPRequest::getBodyPointer()
{
	return body;
}

size_t httplib::HTTPRequest::getBodyLen(){
	return body_len;
}

void httplib::HTTPRequest::setBody(const char *pbody, const size_t len){
	if (pbody == nullptr){
		free(body);
		body = nullptr;
		body_len = 0;
		return;
	}
	free(body);
	body = (char *)malloc(sizeof(char) * len);
	memcpy(body, pbody, len);
	body_len = len;
}

void httplib::HTTPRequest::decodeFormUrlencoded()
{
	if (body == nullptr)
		return;
	const char *p = body;
	std::string key;
	std::string val;
	bool readKey = true;
	int idx = 0;
	while(p - body < body_len)
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
				this -> setForm(key, val);
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
		this -> setForm(key, val);
	}
}

void httplib::HTTPRequest::decodeMultiFormData(std::string boundary)
{
	const char *p = body;
	
}