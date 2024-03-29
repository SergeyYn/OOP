#include <iostream>
#include "List.h"
#include "Bus.h"
using namespace std;
void loadFromFile(const char * file, List<Bus> *inPark)
{
	if (file == NULL) {
		cout << "NO FILE NAME SET" << endl;
		exit(1);
	}
	FILE *f;
	if ((f = fopen(file, "r")) == NULL) {
		cout << "CSV FILE BROKEN OR DOESN'T EXIST" << endl;
		exit(1);
	}
	char name[100], busNumber[100], routeNumber[100];
	char temp;
	int count = 0;
	int symbol_count = 0;
	while (!feof(f)) {
		fscanf(f, "%c", &temp);
		if (temp == ';') {
			symbol_count++;
		}
		if (symbol_count == 2 && temp == '\n') {
			symbol_count = 0;
			count++;
		}
		else if (feof(f) && symbol_count == 2) {
			count++;
			break;
		}
	}
	fclose(f);
	if ((f = fopen(file, "r")) == NULL) {
		cout << "CSV FILE BROKEN OR DOESN'T EXIST" << endl;
		exit(1);
	}
	for (int i = 0; i < count; i++) {
		fscanf(f, "%[^;];%[^;];%[^\n]\n", &name, &busNumber, &routeNumber);
		Bus t(name, busNumber, routeNumber);
		inPark->push_front(t);
	}
	fclose(f);
}

void goOnRoute(const char* bus_number, List<Bus> *inPark, List<Bus> *onRoute){
	if (bus_number == NULL) {
		cout << "INVALID PARAMETERS SET FOR FUNCTION" << endl;
		return;
	}
	for (_iterator<List<Bus>::node_type> i = inPark->begin(); i != NULL; i++){
		if (!strcmp(bus_number, (*i).data.getBusNumber())){
			inPark->splice(i, *onRoute);
			break;
		}
	}
}

void goInPark(const char* bus_number, List<Bus> *inPark, List<Bus> *onRoute){
	if (bus_number == NULL) {
		cout << "INVALID PARAMETERS SET FOR FUNCTION" << endl;
		return;
	}
	for (_iterator<List<Bus>::node_type> i = onRoute->begin(); i != NULL; i++){
		if (!strcmp(bus_number, (*i).data.getBusNumber())){
			onRoute->splice(i, *inPark);
			break;
		}
	}
}

void changeName(const char* oldName, const char* newName, List<Bus> *inPark){
	if (oldName == NULL || newName == NULL) {
		cout << "INVALID PARAMETERS SET FOR FUNCTION" << endl;
		return;
	}
	for (_iterator<List<Bus>::node_type> i = inPark->begin(); i != NULL; i++){
		if (!strcmp(oldName, (*i).data.getName()))
			(*i).data.setName(newName);
	}
}

void printByRouteNumber(const char* route_number, List<Bus> *onRoute) {
	cout << "ON ROUTE ARE THESE BUSES WITH ROUTE NUMBER " << route_number << ":" << endl;
	bool flag = false;
	for (_iterator<List<Bus>::node_type> i = onRoute->begin(); i != NULL; i++)
	{
		if (!strcmp(route_number, (*i).data.getRouteNumber()))
		{
			cout << (*i).data;
			flag = true;
		}
	}
	if (!flag)
	{
		cout << "NO BUSES ARE ON THIS ROUTE" << endl;
	}
}

void printAll(List<Bus> *inPark, List<Bus> *onRoute) {
	cout << "BUSES IN PARK:\n";
	if (inPark->empty())
		cout << "NO BUSES IN PARK" << endl;
	else
		inPark->Print();
	cout << "BUSES ON THE ROUTE:\n";
	if (onRoute->empty())
		cout << "NO BUSES ON ROUTE" << endl;
	else
		onRoute->Print();
}

int main()
{
	List<Bus> inPark;
	List<Bus> onRoute;
	loadFromFile("input.csv", &inPark);
	cout << endl << "BEGINNING SITUATION" << endl;
	printAll(&inPark, &onRoute);
	goOnRoute("341", &inPark, &onRoute);
	goOnRoute("22", &inPark, &onRoute);
	cout << endl << "UPDATED SITUATION" << endl;
	printAll(&inPark, &onRoute);
	goInPark("22", &inPark, &onRoute);
	cout << endl << "NOW IN PARK" << endl;;
	printAll(&inPark, &onRoute);
	char a[] = "2";
	printByRouteNumber(a, &onRoute);
	changeName("Antonio", "NotAntonio", &inPark);
	cout << endl << "AFTER DRIVER CHANGE" << endl;
	printAll(&inPark, &onRoute);

}


