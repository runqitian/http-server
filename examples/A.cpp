#include <iostream>

class A
{
public:
	int num;
	A()
	{
		std::cout << "A()" << std::endl;
	}
	
	A(const A &a)
	{
		std::cout << "A(const A &a)" << std::endl;
	}
	
	~A()
	{
		std::cout << "~A()" << std::endl;
	}

	A& operator=(const A &a)
	{
		std::cout << "A operator=(const A &a)" << std::endl;
		num = a.num;
		return *this;
	}

	A& operator=(int num)
	{
		std::cout << "A operator()=(int num)" << std::endl;
		this -> num = num;
		return *this;
	}

	void norm_func()
	{
		std::cout << "norm_func()" << std::endl;
	}
};


class B : public A
{
public:
	using A::A;
	using A::operator=;

	B()
	{
		std::cout << "B()" << std::endl;
	}
	B(const B &b)
	// :A(b)
	{
		std::cout << "B(const B &b)" << std::endl;
	}
	// B(const A &a)
	// {
	// 	std::cout << "B(const A &a)" << std::endl;
	// }
	~B()
	{
		std::cout << "~B()" << std::endl;
	}

	B& operator=(const B &b)
	{
		A::operator=(b);
		std::cout << "B operator=(const B &b)" << std::endl;
		// num = b.num;
		return *this;
	}

};


int main()
{
	// A a;
	B b;
	B b2;
	b2.num = 100001;
	b = b2;
	std::cout << b.num << std::endl;
	// std::cout << b.num << " " << b2.num << std::endl;
	// A a;
	// b.norm_func();
	// b = a;
	// b = 100;
	return 0;
}