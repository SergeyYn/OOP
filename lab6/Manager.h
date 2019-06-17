#pragma once
#include "Employee.h"
#include<list>
#include<iterator>

class Manager :
	public Employee
{
public:
	Manager() {};
	Manager(string _f_name, string _l_name, int _age, int _id) :
		Employee(_f_name, _l_name, _age, _id) {};
	Manager(const Manager &m);
	Manager& operator=(const Manager &m);
	virtual void Display();
	Person* AddSubordinate(Person *p);
	void DisplaySubordinates();
	void RemoveSubordinate(int _id);
	int GetAge();
	int GetSalary();

private:
	list <Person *> subordinates;
};
