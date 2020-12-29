#include "../bin/include/httplib.h"
#include <iostream>

int main()
{
	const char *s1 = "\"hello, world\"";
	httplib::JSONParser parser;
	std::string r = parser.readString(s1);
	std::cout << r << std::endl;

	const char *s2 = "123";
	const char *s3 = "3.462";
	const char *s4 = "false";
	const char *s5 = "34ab";
	const char *s6 = "true3";
	std::cout << parser.readUnknowText(s2) << std::endl;
	std::cout << parser.readUnknowText(s3) << std::endl;
	std::cout << parser.readUnknowText(s4) << std::endl;
	// std::cout << parser.readUnknowText(s5) << std::endl;
	// std::cout << parser.readUnknowText(s6) << std::endl;
	

	const char *s7 = "{\"name\":\"runqi\", \"age\": 178}";
	httplib::JSON r2 = parser.parse(s7);
	std::cout << r2 << std::endl;


	const char *s8 = "[{\"name\":[\"runqi\", \"tian\"], \"age\": 178}, 12345, \"ffff\"]";
	httplib::JSON r3 = parser.parse(s8);
	std::cout << r3 << std::endl;
}