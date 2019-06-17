#include"Database.h"

int main()
{
	Database db;
	if (!db.LoadFromFile("emp_list.csv")) {
		cout << "ERROR: CAN'T LOAD FROM FILE" << endl;
		exit(1);
	}
	db.DisplayAll();
	db.ArrangeSubordinates();
	db.DisplayAll();
	Person *p = new Manager("Evan","Smith",19,5);
	dynamic_cast<Manager*>(p)->SetDepartment("IT");
	dynamic_cast<Manager*>(p)->SetSalary(2000);
	db.HireEmployee(p);
	db.DisplayAll();
	db.DisplayDepartmentEmployees("PR");
	db.FireEmployee(1);
	db.DisplayAll();
	vector <Person*> rs = db.SQL("salary", "le", "1898");
	db.ShowRecordSet(rs);
	return 0;
}