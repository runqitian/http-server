#include "../bin/include/httplib.h"

#include <iostream>
#include <string>

int main()
{
	httplib::JSONObject obj = {{"name", "runqi"}, {"age", "26"}};
	// httplib::JSON obj = "aab";
	std::cout << obj.map.size() << std::endl;
	return 0;
}