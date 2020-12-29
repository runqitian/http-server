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
		HTTPRequest(HTTPRequest& req);
		~HTTPRequest();

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

		void setBody(const char *pbody, size_t len);
		const char* getBodyPointer();
		size_t getBodyLen();

		void decodeFormUrlencoded();
		void decodeMultiFormData(std::string boundary);


		std::string version;
		std::string type;
		std::string url;
		std::unordered_map<std::string, std::string> header;
		std::unordered_map<std::string, std::string> params;
		std::unordered_map<std::string, std::string> form;
		char *body = nullptr;
		size_t body_len = 0;

	};
}

#endif