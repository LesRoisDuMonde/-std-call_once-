#include <iostream>   
#include "Once.h"

int CommonFunction(int n)
{
	std::cout << "CommonFunction n = " << n << std::endl;
	return n;
}

class FunctionObject {
public:
	int operator()(int i) {
		std::cout << "FunctionObject i = " << i << std::endl;
		return i;
	}
};

class Object {
public:
	 static void test() {
		std::cout << "Object Static test() " << std::endl;
	}

	int test1(int n){
		std::cout << "Object Member test1() " << std::endl;
		return n;
	}
};

int main()
{
	Once once;
	//接受普通函数
	once.Do(CommonFunction, 111);
	//接受lambda表达式
	once.Do([](int n, int m) {
		std::cout << " Lambda Function " << std::endl;
		return n + 1;}, 1, 2);
	//接受函数对象
	FunctionObject object;
	once.Do(object, 666);
	//接受类的普通成员函数
	Object obj;
	once.Do(&Object::test1, &obj, 888);
	//接受类的静态函数
	once.Do(&Object::test);
	return 0;
}


