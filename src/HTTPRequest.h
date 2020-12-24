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

		void decodeUrl(const std::string &url);
		std::string getUrl();
		void setType(const std::string &type);
		std::string getType();
		void setVersion(const std::string &version);
		std::string getVersion();

		void setHeader(const std::string &key, const std::string &val);
		std::string getHeader(const std::string &key);

		void setParam(const std::string &key, const std::string &val);
		std::string getParam(const std::string &key);
		
		void setForm(const std::string &key, const std::string &val);
		std::string getForm(const std::string &key);

		void setBody(const char *pbody, int len);
		const char* getBodyPointer();
		int getBodyLen();

		void decodeFormUrlencoded();

	private:
		std::string version;
		std::string type;
		std::string url;
		std::unordered_map<std::string, std::string> header;
		std::unordered_map<std::string, std::string> params;
		std::unordered_map<std::string, std::string> form;
		char *body = nullptr;
		int body_len = 0;

	};
}

#endif