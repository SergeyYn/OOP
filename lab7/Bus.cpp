#include "Bus.h"

Bus::Bus(){
	this->driver = NULL;
	this->bus_number = NULL;
	this->route_number = NULL;
}

Bus::Bus(const char* _driver, const char* _bus_number, const char* _route_number){
	this->driver = new char[strlen(_driver)];
	this->bus_number = new char[strlen(_bus_number)];
	this->route_number = new char[strlen(_route_number)];
	strcpy(this->driver, _driver);
	strcpy(this->bus_number, _bus_number);
	strcpy(this->route_number, _route_number);
}

Bus::~Bus(){
}

bool Bus::operator==(const Bus & obj) const{
	return !strcmp(this->driver, obj.driver) && !strcmp(this->bus_number, obj.bus_number) && !strcmp(this->route_number, obj.route_number);
}

char * Bus::getBusNumber(){
	return this->bus_number;
}

char * Bus::getRouteNumber(){
	return this->route_number;
}

char * Bus::getName(){
	return this->driver;
}

void Bus::setName(const char * newName){
	if (newName != NULL) {
		driver = new char(strlen(newName));
		strcpy(driver, newName);
	}
}


std::ostream & operator<<(std::ostream & stream, Bus & obj){
	stream << "Driver: " << obj.driver << "\tBus number: " << obj.bus_number << "\tRoute number: " << obj.route_number << '\n';
	return stream;
}
