#ifndef RQJSON_H
#define RQJSON_H

#include "HTTPRequest.h"

// #include "JSONArray.h"
// class JSONObject;

#include <initializer_list>
#include <unordered_map>
#include <string>
#include <utility>
/**
**/

namespace httplib{
	class JSON
	{
	private:
		bool is_array = false;
		void *json;

	public:
		JSON();
		~JSON();
		JSON(const JSON &src);

		JSON(const httplib::JSONObject &arg);
		JSON(const httplib::JSONArray &arg);

		JSON& operator=(const httplib::JSONObject &arg);
		JSON& operator=(const httplib::JSONArray &arg);

		JSONArray& operator[](int idx);
		JSONObject& operator[](const std::string key);

		std::string serialize();
	};

	class JSONArray
	{
	private:
		std::vector<JSONObject> array;

	public:
		JSONArray();
		~JSONArray();
		JSONArray(const JSONArray &src);

		JSONArray(std::initializer_list<JSONObject> ls);

		JSONArray& operator=(std::initializer_list<JSONObject> ls);

	};

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