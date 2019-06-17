#include "Manager.h"


Manager::Manager(const Manager & m)
{
	this->age = m.age;
	this->department = m.department;
	this->f_name = m.f_name;
	this->id = m.id;
	this->l_name = m.l_name;
	this->salary = m.salary;
	this->subordinates = m.subordinates;
}

Manager & Manager::operator=(const Manager & m)
{
	this->id = m.id;
	this->f_name = m.f_name;
	this->l_name = m.l_name;
	this->age = m.age;
	this->department = m.department;
	this->salary = m.salary;
	this->subordinates = m.subordinates;
	return *this;
}

void Manager::Display()
{
	cout << f_name << "  " << l_name << endl;
	cout << "Position: MANAGER" << endl;
	cout << "Manager's id: " << id << endl;
	cout << "Manager's age: " << age << endl;
	cout << "Manager's salary: " << salary << endl;
	cout << "Manager's department: " << department << endl << endl;
	this->DisplaySubordinates();
}

Person * Manager::AddSubordinate(Person * p)
{
	bool flag = true;
	list <Person*>::iterator it;
	for (it = subordinates.begin(); it != subordinates.end(); it++)
		if (typeid(**it) == typeid(Employee)) {
			if (dynamic_cast<Employee*>(*it)->GetId() == dynamic_cast<Employee*>(p)->GetId())
				flag = false;
		}
	if (flag) {
		subordinates.push_back(p);
		return subordinates.back();
	}
	else
		return NULL;
	
}

void Manager::DisplaySubordinates()
{
	cout << "Subordinates:" << endl;
	if (subordinates.empty())
		cout << "No subordinates for this manager" << endl << endl;
	else {
		list <Person*>::iterator it;
		for (it = subordinates.begin(); it != subordinates.end(); it++)
				(*it)->Display();
	}
	cout << "Subordinates ended" << endl;
}

void Manager::RemoveSubordinate(int _id)
{
	list <Person*>::iterator it;
	for (it = subordinates.begin(); it != subordinates.end(); it++)
		if (typeid(**it) == typeid(Employee)) 
			if (dynamic_cast<Employee*>(*it)->GetId() == _id) {
				subordinates.erase(it);
				break;
			}
}

int Manager::GetAge()
{
	return age;
}

int Manager::GetSalary()
{
	return salary;
}



