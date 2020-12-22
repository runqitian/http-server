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

		std::string toString();

		void setBasicInfo(const char *type, const char *url, const char *version);
		std::string getUrl();
		std::string getType();
		std::string getVersion();

		void setHeader(std::string key, std::string val);
		std::string getHeader(std::string key);
		
	private:
		std::string version;
		std::string type;
		std::string url;
		std::unordered_map<std::string, std::string> header;
		

	};
}

#endif