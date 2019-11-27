#pragma once
#include <string>

class ParkingSpace{

private:
	//'l' for large, 'c' for compact, 'm' for motorcycle
	char ParkingSpaceType;

	//-1 if unoccupied, 0 if motorcycle, 1 if car, 2 if bus
	
	int occupiedBy;
	

public:
	
	ParkingSpace(char ParkingSpaceType);
	~ParkingSpace();
	void addVehicle(int vehicleType);
	void removeVehicle();
	void displaySpace();
	bool isOccupied();
	char returnType();
	


};

