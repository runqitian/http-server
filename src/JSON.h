#ifndef RQJSON_H
#define RQJSON_H

#include "HTTPRequest.h"
#include "JSONObject.h"

#include <initializer_list>
#include <unordered_map>
#include <string>
#include <utility>
#include <vector>
#include <iostream>
/**
**/

namespace httplib{

	class JSON : public JSONObject
	{
	private:

	public:
		bool is_array = false;
		std::vector<JSONObject> array;

		using JSONObject::JSONObject;
		using JSONObject::operator=;
		using JSONObject::operator[];
		// using JSONObject::operator<<;
		using JSONObject::toString;
		using JSONObject::set;

		JSON();
		~JSON();
		JSON(const JSON &src);
		JSON(const httplib::JSONObject &arg);
		JSON(std::initializer_list<JSONObject> ls);

		JSON& operator=(const httplib::JSONObject &arg);
		JSON& operator=(const httplib::JSON &arg);
		JSON& operator=(std::initializer_list<JSONObject> ls);

		JSON& operator=(const char *arg);
		JSON& operator=(int arg);
		JSON& operator=(double arg);
		JSON& operator=(bool arg);
		JSON& operator=(std::initializer_list<std::pair<const char*, JSON>> ls);

		JSON& operator[](const std::string key);
		JSONObject& operator[](int idx);

		friend std::ostream& operator<<(std::ostream& os, const JSON &obj);

		void append(const JSONObject &obj);
		std::string toString() const;
	};
	std::ostream& operator<<(std::ostream& os, const JSON &obj);
}

#endif