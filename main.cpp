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
	//������ͨ����
	once.Do(CommonFunction, 111);
	//����lambda���ʽ
	once.Do([](int n, int m) {
		std::cout << " Lambda Function " << std::endl;
		return n + 1;}, 1, 2);
	//���ܺ�������
	FunctionObject object;
	once.Do(object, 666);
	//���������ͨ��Ա����
	Object obj;
	once.Do(&Object::test1, &obj, 888);
	//������ľ�̬����
	once.Do(&Object::test);
	return 0;
}


