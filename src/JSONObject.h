#ifndef RQJSON_OBJECT_H
#define RQJSON_OBJECT_H

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

	public:
		std::string str;
		std::unordered_map<std::string, JSON> map;

		JSONObject();
		~JSONObject();
		JSONObject(const JSONObject &src);

		JSONObject(const char *arg);
		JSONObject(int arg);
		JSONObject(double arg);
		JSONObject(bool arg);
		JSONObject(std::initializer_list<std::pair<std::string, JSON>> ls);

		JSONObject& operator=(const char *arg);
		JSONObject& operator=(int arg);
		JSONObject& operator=(double arg);
		JSONObject& operator=(bool arg);
		JSONObject& operator=(std::initializer_list<std::pair<std::string, JSON>> ls);

	};
}

#endif