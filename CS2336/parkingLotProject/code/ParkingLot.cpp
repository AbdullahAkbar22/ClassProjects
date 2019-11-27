/*
		   ____   _____  _____ ____  _____  ______
	 /\   |  _ \ / ____|/ ____/ __ \|  __ \|  ____|
	/  \  | |_) | (___ | |   | |  | | |  | | |__
   / /\ \ |  _ < \___ \| |   | |  | | |  | |  __|
  / ____ \| |_) |____) | |___| |__| | |__| | |____
 /_/    \_\____/|_____/ \_____\____/|_____/|______|

Abdullah Akbar CS 2336.001

This file contains the ParkingLot class.  The lot has code to display all the levels in it,add a level, get a level
and check if the lot is full for a vehicle, a requirement for the program to terminate.

*/

#include "ParkingLot.h"
#include <vector>
#include <iostream>
using namespace std;

//Default constructor/destructor for the class
ParkingLot::ParkingLot(){
}
ParkingLot::~ParkingLot(){
}


//Displays each level in the lot with the level number alongside it
void ParkingLot::displayLot() {

	for (int i = 0; i < this->lotLevels.size(); i++) {
		cout << (i + 1) << " ";
		this->lotLevels[i].displayLevel();
		

	}
}

//Adds the level passed as a parameter to the lot
void ParkingLot::addLevel(ParkingLotLevel levelToAdd) {
	this->lotLevels.push_back(levelToAdd);

}

//Gets a level from the lot from its number
ParkingLotLevel* ParkingLot::getLevel(int levelNumb) {
	return &lotLevels[levelNumb];
}


//Given a vehicle's number type, determine if the lot is full for that vehicle
bool ParkingLot::fullForVehicle(int vehicleNumb) {
	
	for (int i = 0; i < this->lotLevels.size(); i++) {
		
		if (lotLevels[i].canAddVehicleInLevel(vehicleNumb)) {
			
			return false;
		}
		
	}
	return true;
}

