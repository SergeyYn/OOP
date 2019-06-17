#pragma once

#include"Manager.h"
#include<vector>

class Database
{
public:
	Database() {};
	~Database() {};
	bool LoadFromFile(const char *file);
	void ArrangeSubordinates();
	Person* HireEmployee(Person *p);
	void DisplayDepartmentEmployees(string _department);
	bool FireEmployee(int id);
	void DisplayAll();
	vector<Person*> SQL(const char *field, const char * cond,
		const char* value);
	void ShowRecordSet(vector<Person*> rs);

private:
	vector <Person*> employees;
};

