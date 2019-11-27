/*
		   ____   _____  _____ ____  _____  ______
	 /\   |  _ \ / ____|/ ____/ __ \|  __ \|  ____|
	/  \  | |_) | (___ | |   | |  | | |  | | |__
   / /\ \ |  _ < \___ \| |   | |  | | |  | |  __|
  / ____ \| |_) |____) | |___| |__| | |__| | |____
 /_/    \_\____/|_____/ \_____\____/|_____/|______|

Abdullah Akbar CS 2336.001

This file contains the ParkingSpace class.  The space has a character indicating what type of vehicle is parked in it (l, c, or m  if unoccupied, B, C, or M if occupied)
The space also has code to add a vehicle, remove a vehicle, and to display what sort of space it is/what vehicle is parked in it.

*/
#include "ParkingSpace.h"
#include <iostream>

using namespace std;

//Constructor, sets the character for the parking space type (l, c or m) and -1 to signify the space originally starts unoccupied
ParkingSpace::ParkingSpace(char ParkingSpaceType){
	this->ParkingSpaceType = ParkingSpaceType;
	
	this->occupiedBy = -1;
	
}


ParkingSpace::~ParkingSpace()
{
}


//Sets the occupiedBy variable to the number type of vehicle that is being added
void ParkingSpace::addVehicle(int vehicleType) {
	
	occupiedBy = vehicleType;
	
	
}

//Set occupiedBy to -1, therefore removing the vehicle type on the spot
void ParkingSpace::removeVehicle() {
	
	this->occupiedBy = -1;

}

// If the space is unoccupied, return the type of parking space the space is. Otherwise, return the type of vehicle on the space
char ParkingSpace::returnType(){
	int occupiedBy = this->occupiedBy;
	int ParkingSpaceType = this->ParkingSpaceType;


	switch (occupiedBy) {
		case -1:
			
			return ParkingSpaceType;
			break;
		case 0:
			return 'M';
			break;
		case 1:
			return 'C';
			break;
		case 2:
			return 'B';
			break;

	}
	
}

//Prints the result of returnType to the console
void ParkingSpace::displaySpace() {
	cout << returnType();
}

//Checks if the space is occupied or not
bool ParkingSpace::isOccupied() {
	return this->occupiedBy != -1;

}

