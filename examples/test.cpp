#include <string>
#include <iostream>
#include <unordered_map>

int main(){
	std::string s("hellorunqi");
	std::unordered_map<std::string, std::string> mp;
	mp[s] = "yes";
	for (auto each: mp)
	{
		std::cout << each.first << " " << each.second << std::endl;
	}
	s[3] = 'c';
	for (auto each: mp)
	{
		std::cout << each.first << " " << each.second << std::endl;
	}
	return 0;
}