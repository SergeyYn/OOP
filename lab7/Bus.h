#pragma once
#include <iostream>
#include <string.h>
#include "List.h"
#include "iterator.h"
#pragma warning( disable :4996)
class Bus
{
public:
	Bus();
	Bus(const char* _driver, const char* _bus_number, const char* _route_number);
	~Bus();
	//
	bool operator==(const Bus& obj) const;
	char* getBusNumber();
	char* getRouteNumber();
	char* getName();
	void setName(const char* newName);


	//
	friend std::ostream& operator<<(std::ostream& stream, Bus &obj);
private:
	char *driver;
	char *bus_number;
	char *route_number;
};
