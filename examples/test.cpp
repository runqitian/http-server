#include <string>
#include <iostream>

int main(){
	std::string s("abc");
	std::cout << s.substr(3,-1) << std::endl;
	return 0;
}