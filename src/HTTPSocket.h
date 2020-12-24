#ifndef HTTPSOCKET_H
#define HTTPSOCKET_H

#include <string>
#include "HTTPRequest.h"
#include "HTTPResponse.h"

namespace httplib {

	class HTTPSocket {
	public:
		int sockfd;

		HTTPSocket(int sockfd);
		httplib::HTTPRequest* readRequest();
		void sendResponse(httplib::HTTPResponse &resp);
	private:
		static const int BUFF_SIZE = 64 * 1024;
		char * sbuff;
		int sbuff_size;

		std::string readline();
		void readBytes(char *dest, int len);
		void sendBytes(const char *msg, const unsigned int len);

		void _readHeader(httplib::HTTPRequest &req);
		void _readBody(httplib::HTTPRequest &req);
		void _extractBodyInfo(httplib::HTTPRequest &req);

		bool _checkRequestValid(const std::string &type, const std::string &version);
	};

}

#endif