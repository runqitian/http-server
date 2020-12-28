#ifndef RQJSON_OBJECT_H
#define RQJSON_OBJECT_H

#include "JSONValue.h"
#include "JSON.h"

#include <initializer_list>
#include <unordered_map>
#include <string>
#include <utility>
/**
**/

namespace httplib{
	class JSONObject
	{
	private:
		std::string str;
		std::unordered_map<std::string, JSON> map;

	public:
		JSONObject();
		~JSONObject();
		JSONObject(const JSONObject &src);

		JSONObject(const httplib::JSONValue &arg);
		JSONObject(std::initializer_list<std::pair<std::string, JSON>> ls);

		JSONObject& operator=(const httplib::JSONValue &arg);
		JSONObject& operator=(std::initializer_list<std::pair<std::string, JSON>> ls);

	};
}

#endif