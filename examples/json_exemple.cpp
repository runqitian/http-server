#include "../bin/include/httplib.h"

#include <iostream>
#include <string>

int main()
{
	httplib::JSON obj = {{"name", "runqi"}, {"age", "26"}};
	// httplib::JSONObject obj = ;
	std::cout << obj.json_str << std::endl;
	return 0;
}