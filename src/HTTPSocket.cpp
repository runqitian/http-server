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

httplib::HTTPRequest* httplib::HTTPSocket::readRequest()
{
	httplib::HTTPRequest *req = new httplib::HTTPRequest();
	std::string line = readline();
	
	// check start line
	char *req_type = new char[10];
	char *url = new char[2500];
	char *version = new char[50];
	int temp;
	if ((temp = sscanf(line.c_str(), "%s %s %s\r\n", req_type, url, version)) != 3)
	{
		throw std::runtime_error("request header format invalid!");
	}
	if (!httplib::rules::checkRequestType(req_type))
	{
		throw std::runtime_error("request header format invalid!");
	}
	req -> setBasicInfo(req_type, url, version);
	delete req_type;
	delete url;
	delete version;

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
			req -> setHeader(key, "");
		}else{
			req -> setHeader(key, line.substr(idx, line.size() - idx));
		}
	}
	return req;
}

void httplib::HTTPSocket::sendResponse(httplib::HTTPResponse &resp)
{
	char *msg;
	int len = resp.serialize(&msg);
	sendBytes(msg, len);
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
	int idx = 0;
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

void httplib::HTTPSocket::sendBytes(const char *msg, const unsigned int len){
	unsigned int remain = len;
	const char *p = msg;
	while(remain > BUFF_SIZE){
		int num = send(sockfd, p, BUFF_SIZE, 0);
		if (num == -1){
			throw std::runtime_error("Sending bytes error!");
		}
		p += num;
		remain -= num;
	}
	if (remain > 0){
		int num = send(sockfd, p, remain, 0);
		if (num == -1){
			throw std::runtime_error("Sending bytes error!");
		}
	}
}


