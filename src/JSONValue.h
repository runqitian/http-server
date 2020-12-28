#ifndef JSON_VALUE_H
#define JSON_VALUE_H

#include <string>

namespace httplib
{
	class JSONValue
	{
	public:
		std::string json;

		JSONValue();
		~JSONValue();
		JSONValue(const JSONValue &src);

		JSONValue(const char *arg);
		JSONValue(int arg);
		JSONValue(bool arg);
		JSONValue(double arg);

		JSONValue& operator=(const char *arg);
		JSONValue& operator=(int arg);
		JSONValue& operator=(bool arg);
		JSONValue& operator=(double arg);
	};

}
#endif