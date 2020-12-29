#include "JSONObject.h"
#include "JSON.h"

#include <iostream>
#include <string>

httplib::JSONObject::JSONObject()
{}

httplib::JSONObject::~JSONObject()
{
	// clear map
	for (auto each: map)
	{
		delete each.second;
	}
	map.clear();
}

httplib::JSONObject::JSONObject(const JSONObject &src)
{
	*this = src;
}

httplib::JSONObject::JSONObject(const char *arg)
{
	*this = arg;
}

httplib::JSONObject::JSONObject(int arg)
{
	*this = arg;
}

httplib::JSONObject::JSONObject(double arg)
{
	*this = arg;
}

httplib::JSONObject::JSONObject(bool arg)
{
	*this = arg;
}

httplib::JSONObject::JSONObject(std::initializer_list<std::pair<const char*, JSON>> ls)
{
	*this = ls;
}

httplib::JSONObject& httplib::JSONObject::operator=(const JSONObject &arg)
{
	str = arg.str;
	// clear old map
	for (auto each: map)
	{
		delete each.second;
	}
	map.clear();
	// add new map
	for (auto each: arg.map)
	{
		map[each.first] = new JSON(*each.second);
	}
	return *this;
}

httplib::JSONObject& httplib::JSONObject::operator=(const char* arg)
{
	// clear old map
	for (auto each: map)
	{
		delete each.second;
	}
	map.clear();
	// add new string
	str = "\"";
	str += std::string(arg);
	str += "\"";
	return *this;
}

httplib::JSONObject& httplib::JSONObject::operator=(int arg)
{
	// clear old map
	for (auto each: map)
	{
		delete each.second;
	}
	map.clear();
	// add new string
	str = std::to_string(arg);
	return *this;
}

httplib::JSONObject& httplib::JSONObject::operator=(double arg)
{
	// clear old map
	for (auto each: map)
	{
		delete each.second;
	}
	map.clear();
	// add new string
	str = std::to_string(arg);
	return *this;
}

httplib::JSONObject& httplib::JSONObject::operator=(bool arg)
{
	// clear old map
	for (auto each: map)
	{
		delete each.second;
	}
	map.clear();
	// add new string
	str = arg ? "true" : "false";
	return *this;
}

httplib::JSONObject& httplib::JSONObject::operator=(std::initializer_list<std::pair<const char*, JSON>> ls)
{
	str = "";
	// clear old map
	for (auto each: map)
	{
		delete each.second;
	}
	map.clear();

	// add new items
	for (auto each = ls.begin(); each < ls.end(); each++)
	{
		map[std::string(each -> first)] = new JSON(each -> second);
	}
	return *this;
}

httplib::JSON& httplib::JSONObject::operator[](std::string key)
{
	if (map.find(key) == map.end())
	{
		throw std::runtime_error("JSON does not contain key");
	}
	return *map[key];
}

std::ostream& httplib::operator<<(std::ostream& os, const JSONObject &obj)
{
	os << obj.toString();
	return os;
}

void httplib::JSONObject::set(std::string key, const httplib::JSON &val)
{
	map[key] = new JSON(val);
}

void httplib::JSONObject::set(std::string key, const char *val)
{
	map[key] = new JSON(val);
}

void httplib::JSONObject::set(std::string key, int val)
{
	map[key] = new JSON(val);
}

void httplib::JSONObject::set(std::string key, double val)
{
	map[key] = new JSON(val);
}

void httplib::JSONObject::set(std::string key, bool val)
{
	map[key] = new JSON(val);
}


std::string httplib::JSONObject::toString() const
{
	if (map.size() == 0)
		return str;

	std::string output = "{";
	for (auto each: map)
	{
		output += "\"";
		output += each.first;
		output += "\": ";
		output += each.second -> toString();
		output += ", ";
	}
	output[output.size() - 2] = '}';
	output[output.size() - 1] = ' ';
	return output;
}
