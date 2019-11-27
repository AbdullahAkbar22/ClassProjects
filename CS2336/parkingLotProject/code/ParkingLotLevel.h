#pragma once
#include <vector>
#include "ParkingSpace.h"
#include <string>

using namespace std;

class ParkingLotLevel{

private:
	
	int numberRows;
	int spacesPerRow;
	int totalSpaces;
	vector<ParkingSpace> ParkingSpaces;
public:
	ParkingLotLevel();
	~ParkingLotLevel();
	void setUpLevel(int numberRows, int spacesPerRow, double percentLargeSpots, double percentMotorcycleSpots);
	void displayLevel();
	void addVehicle(int vehicleNumb, int firstSpace);
	bool canAddBus(int firstSpace);
	bool canAddVehicleInLevel(int vehicleNumb);
	bool canAddCar(int firstSpace);
	bool canAddMotorcycle(int firstSpace);
	bool removeBus(int firstSpace);
	bool removeCar(int firstSpace);
	bool removeMotorcycle(int firstSpace);
	ParkingSpace * getSpace(int spaceNumber);


	


};

