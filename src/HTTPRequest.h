#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

#include <unordered_map>
#include <string>

namespace httplib
{
	class HTTPRequest
	{
	public:
		HTTPRequest();
		void setHeader(std::string key, std::string val);
		std::string getHeader(std::string key);
		std::string toString();
	private:
		std::unordered_map<std::string, std::string> header;
		

	};
}

#endif