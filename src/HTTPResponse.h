#ifndef HTTPRESPONSE_H
#define HTTPRESPONSE_H

#include <string>
#include <unordered_map>

namespace httplib
{
	class HTTPResponse
	{
	public:
		HTTPResponse();
		HTTPResponse(HTTPResponse &resp);
		~HTTPResponse();

		int serialize(char **pdes);

		void setVersion(const std::string &version);
		void setStatus(const std::string &code, const std::string &msg);

		void setHeader(const std::string &key, const std::string &val);
		std::string getHeader(const std::string &key);

		void setBody(const char *pbody, int len);

		void createHtmlResponse(const std::string &text);
		void create404Response();

		const static char *MSG404;
		std::string version;
		std::string status_code;
		std::string status_msg;
		std::unordered_map<std::string, std::string> header;

		char *body = nullptr;
		int body_len = 0;
	};
}

#endif