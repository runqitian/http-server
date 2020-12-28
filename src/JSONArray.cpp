// #include "JSONArray.h"
// #include "JSONObject.h"

#include "JSON.h"

httplib::JSONArray::JSONArray()
{}

httplib::JSONArray::~JSONArray()
{}

httplib::JSONArray::JSONArray(const JSONArray &src)
{
	this -> array = src.array;
}

httplib::JSONArray::JSONArray(std::initializer_list<httplib::JSONObject> ls)
{
	*this = ls;
}

httplib::JSONArray& httplib::JSONArray::operator=(std::initializer_list<httplib::JSONObject> ls)
{
	array = ls;
	return *this;
}