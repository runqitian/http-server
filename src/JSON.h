#ifndef RQJSON_H
#define RQJSON_H

#include "HTTPRequest.h"

// #include "JSONArray.h"

#include <initializer_list>
#include <unordered_map>
#include <string>
#include <utility>
/**
**/

namespace httplib{
	class JSONArray;
	
	class JSONObject;

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
}

#endif