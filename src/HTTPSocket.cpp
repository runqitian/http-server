#include "HTTPSocket.h"
#include "Utils.h"

#include <cstring>
#include <cstdio>
#include <sys/socket.h>
#include <unistd.h>

#include <string>
#include <stdexcept>
#include <iostream>

httplib::HTTPSocket::HTTPSocket(int sockfd)
:sockfd(sockfd)
{
	sbuff = (char *)malloc(sizeof(char) * BUFF_SIZE);
	sbuff_size = 0;
}

httplib::HTTPSocket::~HTTPSocket()
{
	free(sbuff);
}

httplib::HTTPRequest* httplib::HTTPSocket::readRequest()
{
	httplib::HTTPRequest *req = new httplib::HTTPRequest();
	std::string line = readline();
	
	// check start line
	char *_type = (char *)malloc(sizeof(char) * 10);
	char *_url = (char *)malloc(sizeof(char) * 2500);
	char *_version = (char *)malloc(sizeof(char) * 50);
	int _tmp;
	if ((_tmp = sscanf(line.c_str(), "%s %s %s\r\n", _type, _url, _version)) != 3 || !_checkRequestValid(_type, _version))
	{
		throw std::runtime_error("Invalid request!");
	}
	req -> decodeUrl(_url);
	req -> setType(_type);
	req -> setVersion(_version);
	free(_type);
	free(_url);
	free(_version);

	_readHeader(*req);
	_readBody(*req);

	return req;
}
	
void httplib::HTTPSocket::_readHeader(httplib::HTTPRequest &req)
{
	std::string line;
	// read header
	while(true)
	{
		line = readline();

		// end of header
		if (line == std::string("\r\n"))
		{
			break;
		}

		//check valid
		if (line.size() < 2)
		{
			throw std::runtime_error("request header format invalid!");
		}
		if (line[line.size() - 1] != '\n' || line[line.size() - 2] != '\r')
		{
			throw std::runtime_error("request header format invalid!");
		}
		line = line.substr(0, line.size() - 2);

		// deserialize
		int idx;
		if ((idx = line.find(":")) == -1)
		{
			throw std::runtime_error("request header format invalid!");
		}
		std::string key = line.substr(0, idx);
		++idx;
		while(idx < line.size() && line[idx] == ' '){
			++idx;
		}
		if (idx == line.size()){
			req.setHeader(key, "");
		}else{
			req.setHeader(key, line.substr(idx, -1));
		}
	}
}

void httplib::HTTPSocket::_readBody(httplib::HTTPRequest &req)
{
	if (req.getHeader("Content-Length") != ""){
		// read body bytes from socket
		size_t test_tmp;
		size_t cont_len = std::stol(req.getHeader("Content-Length"), &test_tmp, 10);
		if (test_tmp != req.getHeader("Content-Length").size()){
			throw std::runtime_error("request header format invalid! Contetn-Length invalid!");
		}
		char *buff_tmp = (char *)malloc(sizeof(char) * cont_len);
		readBytes(buff_tmp, cont_len);
		req.setBody(buff_tmp, cont_len);
		free(buff_tmp);

		// extract info
		_extractBodyInfo(req);

	}else{
		req.setBody(nullptr, 0);
	}
}

void httplib::HTTPSocket::_extractBodyInfo(httplib::HTTPRequest &req){
	if (req.getType() == "GET")
	{
		// nothing to do
	}
	else if (req.getType() == "POST")
	{
		if (req.getHeader("Content-Type") == "application/x-www-form-urlencoded")
		{
			req.decodeFormUrlencoded();
		}
	}
}

void httplib::HTTPSocket::sendResponse(httplib::HTTPResponse &resp)
{
	char *msg;
	size_t len = resp.serialize(&msg);
	sendBytes(msg, len);
	free(msg);
}

std::string httplib::HTTPSocket::readline()
{
	if (sbuff_size == 0){
		if ((sbuff_size = recv(sockfd, sbuff, BUFF_SIZE, 0)) <= 0) {
			throw std::runtime_error("Connection closed!");
		}
	}
	std::string msg;
	bool lf = false;
	size_t idx = 0;
	while(!lf) {
		while(idx < sbuff_size){
			if (sbuff[idx] == '\n'){
				msg += sbuff[idx];
				++idx;
				lf = true;
				break;
			}
			msg += sbuff[idx];
			++idx;
		}
		if (!lf){
			if ((sbuff_size = recv(sockfd, sbuff, BUFF_SIZE, 0)) <= 0){
				throw std::runtime_error("Connection closed!");
			}
			idx = 0;
		}
	}
	memmove(sbuff, sbuff + idx, sbuff_size - idx);
	sbuff_size = sbuff_size - idx;
	return msg;
}

void httplib::HTTPSocket::readBytes(char *dest, size_t len)
{
	if (len == 0){
		return;
	}
	if (sbuff_size == 0){
		if ((sbuff_size = recv(sockfd, sbuff, BUFF_SIZE, 0)) <= 0) {
			throw std::runtime_error("Connection closed!");
		}
	}
	size_t need = len;
	char *p = dest;
	while (sbuff_size < need){
		memcpy(p, sbuff, sbuff_size);
		need -= sbuff_size;
		p += sbuff_size;
		if ((sbuff_size = recv(sockfd, sbuff, BUFF_SIZE, 0)) <= 0){
			throw std::runtime_error("Connection closed!");
		}
	}
	memcpy(p, sbuff, need);
	memmove(sbuff, sbuff + need, sbuff_size - need);
	sbuff_size = sbuff_size - need;
}

void httplib::HTTPSocket::sendBytes(const char *msg, const size_t len)
{
	size_t remain = len;
	const char *p = msg;
	while(remain > BUFF_SIZE){
		size_t num = send(sockfd, p, BUFF_SIZE, 0);
		if (num == -1){
			throw std::runtime_error("Sending bytes error!");
		}
		p += num;
		remain -= num;
	}
	if (remain > 0){
		size_t num = send(sockfd, p, remain, 0);
		if (num == -1){
			throw std::runtime_error("Sending bytes error!");
		}
	}
}

bool httplib::HTTPSocket::_checkRequestValid(const std::string &type, const std::string &version)
{
	if (httplib::constant::REQUEST_TYPES.find(type) == httplib::constant::REQUEST_TYPES.end())
	{
		return false;
	}
	if (httplib::constant::HTTP_VERSIONS.find(version) == httplib::constant::HTTP_VERSIONS.end())
	{
		return false;
	}
	return true;
}


