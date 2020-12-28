#include "JSONValue.h"

#include <string>

httplib::JSONValue::JSONValue()
{}

httplib::JSONValue::~JSONValue()
{}

httplib::JSONValue::JSONValue(const JSONValue &src)
{
	this -> json = src.json;
}

httplib::JSONValue::JSONValue(const char *arg)
{
	*this = arg;
}

httplib::JSONValue::JSONValue(int arg)
{
	*this = arg;
}

httplib::JSONValue::JSONValue(bool arg)
{
	*this = arg;
}

httplib::JSONValue::JSONValue(double arg)
{
	*this = arg;
}

httplib::JSONValue& httplib::JSONValue::operator=(const char *arg)
{
	this -> json = "\"";
	this -> json += std::string(arg);
	this -> json += "\"";
	return *this;
}

httplib::JSONValue& httplib::JSONValue::operator=(int arg)
{
	this -> json = std::to_string(arg);
	return *this;
}

httplib::JSONValue& httplib::JSONValue::operator=(bool arg)
{
	this -> json = arg? "true" : "false";
	return *this;
}

httplib::JSONValue& httplib::JSONValue::operator=(double arg)
{
	this -> json = std::to_string(arg);
	return *this;
}