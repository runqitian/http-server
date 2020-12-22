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

		void setUrl(const char *url);
		std::string getUrl();
		void setType(const char *type);
		std::string getType();
		void setVersion(const char *version);
		std::string getVersion();

		void setHeader(std::string key, std::string val);
		std::string getHeader(std::string key);

		void setParam(const char *key, const char *val);
		
	private:
		std::string version;
		std::string type;
		std::string url;
		std::unordered_map<std::string, std::string> header;
		std::unordered_map<std::string, std::string> params;
		

	};
}

#endif