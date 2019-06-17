#pragma once

#include<iostream>
#include<string>
#include <typeinfo>

using namespace std;

class Person {
public:
	Person() {};
	Person(string _f_name, string _l_name, int _age) : age(_age),
		f_name(_f_name), l_name(_l_name) {};
	virtual void Display() = 0;
protected:
	string f_name;
	string l_name;
	int age;
};
