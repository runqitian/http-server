#include "JSON.h"
// #include "JSONObject.h"
// #include "JSONArray.h"

#include <iostream>
#include <string>
#include <initializer_list>
#include <utility>
#include <stdexcept>

httplib::JSON::JSON()
{
	json = nullptr;
}

httplib::JSON::~JSON()
{
	if (is_array)
		delete (JSONArray*)json;
	else
		delete (JSONObject*)json;
}

httplib::JSON::JSON(const JSON &src)
{
	if (src.is_array)
		this -> json = new httplib::JSONArray(*(JSONArray*)src.json);
	else
		this -> json = new httplib::JSONObject(*(JSONObject*)src.json);
	this -> is_array = src.is_array;
}

httplib::JSON::JSON(const JSONObject &arg)
{
	*this = arg;
}

httplib::JSON::JSON(const JSONArray &arg)
{
	*this = arg;
}

httplib::JSON& httplib::JSON::operator=(const httplib::JSONObject &arg)
{
	is_array = false;
	json = new JSONObject(arg);
	return *this;
}

httplib::JSON& httplib::JSON::operator=(const httplib::JSONArray &arg)
{
	is_array = true;
	json = new JSONArray(arg);
	return *this;
}

httplib::JSONArray& httplib::JSON::operator[](int idx)
{
	if (!is_array){
		throw std::runtime_error("JSON is not array!");
	}
	return *(JSONArray*)json;
}
httplib::JSONObject& httplib::JSON::operator[](const std::string key)
{
	if (is_array)
		throw std::runtime_error("JSON is array!");
	return *(JSONObject*)json;
}

std::string httplib::JSON::serialize()
{
	return "";
}
