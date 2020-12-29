#include "JSON.h"
#include "JSONObject.h"

#include <iostream>
#include <string>
#include <initializer_list>
#include <utility>
#include <stdexcept>

httplib::JSON::JSON()
{}

httplib::JSON::~JSON()
{}

httplib::JSON::JSON(const JSON &src)
{
	*this = src;
}

httplib::JSON::JSON(const JSONObject &arg)
{
	*this = arg;
}

httplib::JSON::JSON(std::initializer_list<httplib::JSONObject> ls)
{
	*this = ls;
}

httplib::JSON& httplib::JSON::operator=(const httplib::JSON &arg)
{
	httplib::JSONObject::operator=(arg);
	array = arg.array;
	is_array = arg.is_array;
	return *this;
}

httplib::JSON& httplib::JSON::operator=(const httplib::JSONObject &arg)
{
	httplib::JSONObject::operator=(arg);
	is_array = false;
	array.clear();
	return *this;
}

httplib::JSON& httplib::JSON::operator=(std::initializer_list<httplib::JSONObject> ls)
{
	is_array = true;
	array = ls;
	str = "";
	// clear map
	for (auto each: map)
	{
		delete each.second;
	}
	map.clear();
	return *this;
}

httplib::JSON& httplib::JSON::operator=(const char *arg)
{
	is_array = false;
	array.clear();
	httplib::JSONObject::operator=(arg);
	return *this;
}

httplib::JSON& httplib::JSON::operator=(int arg)
{
	is_array = false;
	array.clear();
	httplib::JSONObject::operator=(arg);
	return *this;
}

httplib::JSON& httplib::JSON::operator=(double arg)
{
	is_array = false;
	array.clear();
	httplib::JSONObject::operator=(arg);
	return *this;
}

httplib::JSON& httplib::JSON::operator=(bool arg)
{
	is_array = false;
	array.clear();
	httplib::JSONObject::operator=(arg);
	return *this;
}

httplib::JSON& httplib::JSON::operator=(std::initializer_list<std::pair<const char*, JSON>> ls)
{
	is_array = false;
	array.clear();
	httplib::JSONObject::operator=(ls);
	return *this;
}

httplib::JSON& httplib::JSON::operator[](const std::string key)
{
	if (is_array)
		throw std::runtime_error("JSON is array!");
	httplib::JSON &result = httplib::JSONObject::operator[](key);
	return result;
}

httplib::JSONObject& httplib::JSON::operator[](int idx)
{
	if (!is_array)
		throw std::runtime_error("JSON is not array!");
	if (idx >= array.size())
		throw std::runtime_error("array idx exceeds.");
	return array[idx];
}

std::ostream& httplib::operator<<(std::ostream& os, const JSON &obj)
{
	os << obj.toString();
	return os;
}

void httplib::JSON::append(const JSONObject &obj)
{
	if (is_array)
		array.push_back(obj);
	else{
		is_array = true;
		str = "";
		// clear map
		for (auto each: map)
		{
			delete each.second;
		}
		map.clear();
		array.push_back(obj);
	}
}


std::string httplib::JSON::toString() const
{
	if (is_array)
	{
		std::string output = "[";
		for (auto each: array)
		{
			output += each.toString();
			output += ", ";
		}
		output[output.size() - 2] = ']';
		return output;
	}
	// otherwise
	return httplib::JSONObject::toString();
}
