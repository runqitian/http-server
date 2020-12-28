#include "JSONObject.h"
#include "JSONValue.h"
#include "JSON.h"

httplib::JSONObject::JSONObject()
{}

httplib::JSONObject::~JSONObject()
{}

httplib::JSONObject::JSONObject(const JSONObject &src)
{
	this -> str = src.str;
	this -> map = src.map;
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

httplib::JSONObject::JSONObject(std::initializer_list<std::pair<std::string, JSON>> ls)
{
	*this = ls;
}

httplib::JSONObject& httplib::JSONObject::operator=(const char* arg)
{
	str = "\"";
	str += std::string(arg);
	str += "\"";
	return *this;
}

httplib::JSONObject& httplib::JSONObject::operator=(int arg)
{
	str = std::to_string(arg);
	return *this;
}

httplib::JSONObject& httplib::JSONObject::operator=(double arg)
{
	str = std::to_string(arg);
	return *this;
}

httplib::JSONObject& httplib::JSONObject::operator=(bool arg)
{
	str = std::to_string(arg);
	return *this;
}

httplib::JSONObject& httplib::JSONObject::operator=(std::initializer_list<std::pair<std::string, JSON>> ls)
{
	for (auto each = ls.begin(); each < ls.end(); each++)
	{
		map[each -> first] = each -> second;
	}
	return *this;
}