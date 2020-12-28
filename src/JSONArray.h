#ifndef RQJSON_ARRAY_H
#define RQJSON_ARRAY_H

#include "JSONObject.h"

#include <initializer_list>
#include <string>
#include <vector>
/**
**/

namespace httplib{
	class JSONArray
	{
	private:
		std::vector<JSONObject> array;

	public:
		JSONArray();
		~JSONArray();
		JSONArray(const JSONArray &src);

		JSONArray(std::initializer_list<JSONObject> ls);

		JSONArray& operator=(std::initializer_list<JSONObject> ls);

	};
}

#endif