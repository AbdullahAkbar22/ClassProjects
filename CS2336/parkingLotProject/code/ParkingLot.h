#pragma once
#include <vector>
#include "ParkingLotLevel.h"
#include "ParkingSpace.h"
using namespace std;
class ParkingLot{

private:
	
	vector<ParkingLotLevel> lotLevels;

public:
	ParkingLot();
	~ParkingLot();
	void displayLot();
	void addLevel(ParkingLotLevel levelToAdd);
	ParkingLotLevel* getLevel(int levelNumb);
	bool fullForVehicle(int vehicleNumb);
};

