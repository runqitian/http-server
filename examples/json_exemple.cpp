#include "../bin/include/httplib.h"

#include <iostream>
#include <string>
#include <cstdio>

int main()
{
	httplib::JSON obj = {{{"name", "runqi"}, {"age", 26}}, {{"name", "runqi"}, {"age", 26}}};
	// httplib::JSON obj = "aab";
	// std::cout << obj.map.size() << std::endl;
	// printf("%s", obj.toString().c_str());
	std::cout << obj[1] << std::endl;
	obj[1] = {{"tool", "computer"}};
	std::cout << obj << std::endl;
	obj = {{"msg", "success"}};
	std::cout << obj << std::endl;
	return 0;
}