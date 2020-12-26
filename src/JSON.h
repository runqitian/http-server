#ifndef RQJSON_H
#define RQJSON_H

#include "HTTPRequest.h"

#include <initializer_list>
#include <unordered_map>
#include <string>
#include <utility>
/**
**/

namespace httplib{
	class JSON
	{
		std::string output;
		std::unordered_map<std::string, JSON*> dict;

		JSON();
		~JSON();
		// JSON(JSON& org);
		// JSON(const std::string &s);
		// JSON(const char *s);
		// JSON(std::initializer_list<std::pair<std::string, std::string>> ls);

		// JSON& operator[](const std::string &key);
		// JSON& operator=(const std::string &s);
		// JSON& operator=(const char *s);


	};
}

#endif