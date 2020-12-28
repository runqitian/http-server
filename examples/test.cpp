#include <iostream>
#include <string>

void func1(bool x)
{
	std::cout << std::to_string(x) << std::endl;
}

void func1(int x)
{
	std::cout << "int" << std::endl;
}

int main()
{
	func1(true);
	return 0;
}