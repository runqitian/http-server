#include <regex>
#include <string>
#include <iostream>

void test_regex()
{
	std::string s = "multipart/form-data; boundary=---------------------------974767299852498929531610575";
	if (std::regex_match(s, std::regex("^multipart/form-data;.*")))
	{
		std::smatch m;
		std::string boundary;
		if (std::regex_search(s, m, std::regex("boundary=(.*)"))){
			boundary = m[1];
		}
		else{
			std::cout << "wrong boundary" << std::endl;
		}
		std::cout << boundary << std::endl;
	}
}

int main()
{
	test_regex();
}