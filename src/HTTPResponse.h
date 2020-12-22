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
		int serialize(char **arg_p);
		void setVersion(std::string version);
		void setHeader(std::string key, std::string val);
		std::string getHeader(std::string key);
		void setStatus(std::string code, std::string msg);
		void setBody(const char *arg_body, int arg_length);
	private:
		std::string version;
		std::string status_code;
		std::string status_msg;
		std::unordered_map<std::string, std::string> header;
		const char *body;
		int body_length;
	};
}

#endif