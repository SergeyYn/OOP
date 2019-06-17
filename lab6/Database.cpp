#include "Database.h"

bool Database::LoadFromFile(const char * file)
{
	FILE *f;
	if ((f = fopen(file, "r")) == NULL)
		return false;
	int type, id, age, salary,i=0;
	string fn, ln, dt;
	char temp;
	char bufFn[100], bufLn[100], bufDt[10];
	int count = 0;
	int symbol_count = 0;
	while (!feof(f)) {
		fscanf(f, "%c", &temp);
		if (temp == ';') {
			symbol_count++;
		}
		if (symbol_count == 6 && temp == '\n') {
			symbol_count = 0;
			count++;
		}
		else if (feof(f) && symbol_count == 6) {
			count++;
			break;
		}
	}
	fclose(f);
	if ((f = fopen(file, "r")) == NULL)
		return false;
	for (int i = 0; i < count; i++) {
		fscanf(f, "%d;%d;%[^;];%[^;];%d;%[^;];%d\n", &type, &id, &bufFn, &bufLn, &age, &bufDt, &salary);
		Person *tempP;
		fn = bufFn;
		ln = bufLn;
		dt = bufDt;
		if (type == 0) {
			tempP = new Employee(fn, ln, age, id);
			dynamic_cast <Employee*>(tempP)->SetDepartment(dt);
			dynamic_cast <Employee*>(tempP)->SetSalary(salary);
		}
		else {
			tempP = new Manager(fn, ln, age, id);
			dynamic_cast <Manager*>(tempP)->SetDepartment(dt);
			dynamic_cast <Manager*>(tempP)->SetSalary(salary);
		}
		employees.push_back(tempP);
	}
	fclose(f);
	return true;
}

void Database::ArrangeSubordinates()
{
	vector <Person*>::iterator it;
	for (it = employees.begin(); it != employees.end(); it++)
		if (typeid(**it) == typeid(Employee)) {
			vector <Person*>::iterator k;
			for (k = employees.begin(); k != employees.end(); k++)
				if (typeid(**k) == typeid(Manager)) {
					if (dynamic_cast<Manager*>(*k)->GetDepartment() == dynamic_cast<Employee*>(*it)->GetDepartment())
						dynamic_cast<Manager*>(*k)->AddSubordinate(dynamic_cast<Person*>(*it));
				}

		}
}

Person * Database::HireEmployee(Person * p)
{
	bool flag = true;
	int id;
	Person *Temp=NULL;
	if (p == NULL)
		return NULL;
	if (typeid(*p) == typeid(Employee)) {
		id = dynamic_cast<Employee*>(p)->GetId();
		Temp = new Employee(*dynamic_cast<Employee*>(p));
		if ((dynamic_cast<Employee*>(Temp)->GetDepartment()).empty())
			flag = false;
	}
	else if (typeid(*p) == typeid(Manager)) {
		id = dynamic_cast<Manager*>(p)->GetId();
		Temp = new Manager(*dynamic_cast<Manager*>(p));
		if ((dynamic_cast<Employee*>(Temp)->GetDepartment()).empty())
			flag = false;
	}
	vector <Person*>::iterator it;
	if (flag) {
		for (it = employees.begin(); it != employees.end(); it++) {
			if (typeid(**it) == typeid(Employee)) {
				if (dynamic_cast<Employee*>(*it)->GetId() == id || dynamic_cast<Employee*>(*it)->GetAge() == dynamic_cast<Employee*>(Temp)->GetAge() &&  dynamic_cast<Employee*>(*it)->GetDepartment() == dynamic_cast<Employee*>(Temp)->GetDepartment() &&  dynamic_cast<Employee*>(*it)->GetSalary() == dynamic_cast<Employee*>(Temp)->GetSalary())
					flag = false;
			}
			else if (typeid(**it) == typeid(Manager)) {
				if (dynamic_cast<Manager*>(*it)->GetId() == id ||  dynamic_cast<Manager*>(*it)->GetAge() == dynamic_cast<Manager*>(Temp)->GetAge() && dynamic_cast<Manager*>(*it)->GetDepartment() == dynamic_cast<Manager*>(Temp)->GetDepartment() && dynamic_cast<Manager*>(*it)->GetSalary() == dynamic_cast<Manager*>(Temp)->GetSalary())
					flag = false;
			}
		}
	}
	if (flag){
		employees.push_back(Temp);
		this->ArrangeSubordinates();
		return employees.back();
	}
	else {
		delete Temp;
		return NULL;
	}
}

void Database::DisplayDepartmentEmployees(string _department)
{
	cout << "PEOPLE WORKING AT DEPARTMENT OF " << _department << endl << endl;
	vector <Person*>::iterator it;
	for (it = employees.begin(); it != employees.end(); it++)
		if (typeid(**it) == typeid(Employee)) {
			if (dynamic_cast<Employee*>(*it)->GetDepartment() == _department) {
				(*it)->Display();
				cout << endl;
			}
		}
		else if (typeid(**it) == typeid(Manager)) 
				if (dynamic_cast<Manager*>(*it)->GetDepartment() == _department) {
					(*it)->Display();
					cout << endl;
				}
	cout << "LIST OF PEOPLE WORKING AT DEPARTMENT OF " << _department << "ENDED" << endl << endl;
}

bool Database::FireEmployee(int id)
{
	vector <Person*>::iterator it;
	bool flag = false;
	for (it = employees.begin(); it != employees.end(); it++)
		if (typeid(**it) == typeid(Employee)) {
			if (dynamic_cast<Employee*>(*it)->GetId() == id){ 
				employees.erase(it);
				flag = true;
				break;
			}
		}
		else if (typeid(**it) == typeid(Manager)) {
			if (dynamic_cast<Manager*>(*it)->GetId() == id){
				employees.erase(it);
				flag = true;
				break;
			}
		}
	for (it = employees.begin(); it != employees.end(); it++)
		if (typeid(**it) == typeid(Manager)) {
			dynamic_cast<Manager*>(*it)->RemoveSubordinate(id);
		}
	return flag;
}

void Database::DisplayAll()
{
	cout << "LIST OF ALL EMPLOYEES AND MANAGERS" << endl << endl;

	for (int i = 0; i < employees.size(); i++)
	{
		employees[i]->Display();
		cout << endl;
	}
	cout << "LIST OF ALL EMPLOYEES AND MANAGERS ENDED" << endl << endl;
}

vector<Person*> Database::SQL(const char * field, const char * cond, const char * value)
{
	vector<Person*> recordSet;
	if (field == NULL || cond == NULL || value == NULL)
		return recordSet;
	int n = atoi(value);
	vector <Person*>::iterator it;
	for (it = employees.begin(); it != employees.end(); it++) {
		if (typeid(**it) == typeid(Employee)) {
			if (!strcmp(field, "age"))
			{
				if (!strcmp(cond, "le"))
				{
					if (dynamic_cast<Employee*>(*it)->GetAge() <= n)
						recordSet.push_back((dynamic_cast<Person*>(*it)));
				}
				else if (!strcmp(cond, "ge"))
				{
					if (dynamic_cast<Employee*>(*it)->GetAge() >= n)
						recordSet.push_back((dynamic_cast<Person*>(*it)));
				}
			}
			else if (!strcmp(field, "salary"))
			{
				if (!strcmp(cond, "le"))
				{
					if (dynamic_cast<Employee*>(*it)->GetSalary() <= n)
						recordSet.push_back((dynamic_cast<Person*>(*it)));
				}
				else if (!strcmp(cond, "ge"))
				{
					if (dynamic_cast<Employee*>(*it)->GetSalary() >= n)
						recordSet.push_back((dynamic_cast<Person*>(*it)));
				}
			}
		}
		else if (typeid(**it) == typeid(Manager)) {
			if (typeid(**it) == typeid(Manager)) {
				if (!strcmp(field, "age"))
				{
					if (!strcmp(cond, "le"))
					{
						if (dynamic_cast<Manager*>(*it)->GetAge() <= n)
							recordSet.push_back((dynamic_cast<Person*>(*it)));
					}
					else if (!strcmp(cond, "ge"))
					{
						if (dynamic_cast<Manager*>(*it)->GetAge() >= n)
							recordSet.push_back((dynamic_cast<Person*>(*it)));
					}
				}
				else if (!strcmp(field, "salary"))
				{
					if (!strcmp(cond, "le"))
					{
						if (dynamic_cast<Manager*>(*it)->GetSalary() <= n)
							recordSet.push_back((dynamic_cast<Person*>(*it)));
					}
					else if (!strcmp(cond, "ge"))
					{
						if (dynamic_cast<Manager*>(*it)->GetSalary() >= n)
							recordSet.push_back((dynamic_cast<Person*>(*it)));
					}
				}
			}
		}
	}

	return recordSet;
}

void Database::ShowRecordSet(vector<Person*> rs)
{
	cout << "RECORD SET WITH PARAMETERS SET" << endl << endl;
	vector <Person*>::iterator it;
	for (it = rs.begin(); it != rs.end(); it++) {
			(*it)->Display();
			cout << endl;
		}
	cout << "RECORD SET WITH PARAMETERS SET ENDED" << endl << endl;
}
