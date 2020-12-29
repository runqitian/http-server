#ifndef RQJSON_PARSER_H
#define RQJSON_PARSER_H

#include "JSON.h"

#include <string>

namespace httplib
{
	class JSONParser
	{
	public:
		JSONParser();
		~JSONParser();
		JSONParser(const JSONParser &p) = delete;

		JSON parse(const std::string &input);

		JSON parseArray(const char *&p);
		JSON parseObject(const char *&p);
		std::string readString(const char *&p);
		JSON readUnknowText(const char *&p);
		std::pair<std::string, JSON> readKeyPair(const char *&p);
		void skipBlankChar(const char *&p);
	};
}

#endif