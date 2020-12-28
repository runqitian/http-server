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
	// this -> map = src.map;
}

httplib::JSONObject::JSONObject(const httplib::JSONValue &arg)
{
	*this = arg;
}

httplib::JSONObject::JSONObject(std::initializer_list<std::pair<std::string, JSON>> ls)
{
	*this = ls;
}

httplib::JSONObject& httplib::JSONObject::operator=(const httplib::JSONValue &arg)
{
	str = arg.json;
	return *this;
}

httplib::JSONObject& httplib::JSONObject::operator=(std::initializer_list<std::pair<std::string, JSON>> ls)
{
	// for (auto each = ls.begin(); each < ls.end(); each++)
	// {
	// 	map[each -> first] = each -> second;
	// }
	return *this;
}