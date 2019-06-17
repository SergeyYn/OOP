#include "Employee.h"

Employee::Employee(const Employee & e)
{
	this->f_name = e.f_name;
	this->l_name = e.l_name;
	this->id = e.id;
	this->age = e.age;
	this->department = e.department;
	this->salary = e.salary;
}

Employee & Employee::operator=(const Employee & e)
{
	this->f_name = e.f_name;
	this->l_name = e.l_name;
	this->id = e.id;
	this->age = e.age;
	this->department = e.department;
	this->salary = e.salary;
	return *this;
}

void Employee::SetSalary(int s)
{
	salary = s;
}

void Employee::SetDepartment(string dept)
{
	department = dept;
}

void Employee::SetId(int n)
{
	id = n;
}

int Employee::GetId()
{
	return id;
}

string Employee::GetDepartment()
{
	return department;
}

void Employee::Display()
{
	cout << f_name << "  " << l_name << endl;
	cout << "Position: EMPLOYEE" << endl;
	cout << "Employee's id: " << id << endl;
	cout << "Employee's age: " << age << endl;
	cout << "Employee's salary: " << salary << endl;
	cout << "Employee's department: " << department << endl;
	cout << endl;
}

int Employee::GetAge()
{
	return age;
}

int Employee::GetSalary()
{
	return salary;
}
