#ifndef RQJSON_OBJECT_H
#define RQJSON_OBJECT_H

#include <initializer_list>
#include <unordered_map>
#include <string>
#include <utility>
#include <iostream>
/**
**/


namespace httplib{

	class JSON;

	class JSONObject
	{
	private:

	public:
		std::string str;
		std::unordered_map<std::string, JSON*> map;

		JSONObject();
		~JSONObject();
		JSONObject(const JSONObject &src);

		JSONObject(const char *arg);
		JSONObject(int arg);
		JSONObject(double arg);
		JSONObject(bool arg);
		JSONObject(std::initializer_list<std::pair<const char*, JSON>> ls);

		JSONObject& operator=(const JSONObject &src);
		JSONObject& operator=(const char *arg);
		JSONObject& operator=(int arg);
		JSONObject& operator=(double arg);
		JSONObject& operator=(bool arg);
		JSONObject& operator=(std::initializer_list<std::pair<const char*, JSON>> ls);

		JSON& operator[](std::string key);

		friend std::ostream& operator<<(std::ostream& os, const JSONObject &obj);

		void set(std::string key, const httplib::JSON &val);
		void set(std::string key, const char *val);
		void set(std::string key, int val);
		void set(std::string key, double val);
		void set(std::string key, bool val);

		std::string toString() const;
	};
	std::ostream& operator<<(std::ostream& os, const JSONObject &obj);
}

#endif