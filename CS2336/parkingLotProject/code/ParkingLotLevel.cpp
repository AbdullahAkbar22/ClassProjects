/*
		   ____   _____  _____ ____  _____  ______
	 /\   |  _ \ / ____|/ ____/ __ \|  __ \|  ____|
	/  \  | |_) | (___ | |   | |  | | |  | | |__
   / /\ \ |  _ < \___ \| |   | |  | | |  | |  __|
  / ____ \| |_) |____) | |___| |__| | |__| | |____
 /_/    \_\____/|_____/ \_____\____/|_____/|______|

Abdullah Akbar CS 2336.001

This file contains ParkingLotLevel class. Each ParkingLotLevel must be set up with the data inputted by the user (passed as parameters to the setUpLevel method)
The ParkingLotLevel class also contains methods to add and remove each vehicle, along with methods to figure out if we can add any more of a certain
vehicle to the level.

*/
#include "ParkingLotLevel.h"
#include <vector>
#include "ParkingSpace.h"
#include <iostream>

using namespace std;


//Default constructor and destructor for the class
ParkingLotLevel::ParkingLotLevel(){
}


ParkingLotLevel::~ParkingLotLevel(){
}


//Method to set up the level, taking in the total spaces, the number of spaces per row, the percent of large spaces, and the percent of motorcycle spaces
void ParkingLotLevel::setUpLevel(int totalSpaces, int spacesPerRow, double percentLargeSpots, double percentMotorcycleSpots) {
	this->totalSpaces = totalSpaces;
	//Get the number of rows there will be per level
	this->numberRows = totalSpaces / spacesPerRow;
	this->spacesPerRow = spacesPerRow;

	//Use the percentage values to calculate the int number of large and motorcycle spaces
	int totalLargeSpaces = (int)(percentLargeSpots * totalSpaces);
	int totalMotorcycleSpaces = (int)(percentMotorcycleSpots * totalSpaces);
	int totalCompactSpaces = totalSpaces - (totalLargeSpaces + totalMotorcycleSpaces);

	//Setup the large, motorcycle, and compact spaces
	for (int i = 0; i < totalLargeSpaces; i++) {
		ParkingSpace largeSpace = ParkingSpace('l');
		this->ParkingSpaces.push_back(largeSpace);

	}
	for (int i = 0; i < totalCompactSpaces; i++) {
		ParkingSpace compactSpace = ParkingSpace('c');
		this->ParkingSpaces.push_back(compactSpace);

	}
	for (int i = 0; i < totalMotorcycleSpaces; i++) {
		ParkingSpace motorcycleSpace = ParkingSpace('m');
		this->ParkingSpaces.push_back(motorcycleSpace);

	}



}

//Displays every parking space in the level, separating them by their rows
void ParkingLotLevel::displayLevel() {
	for (int i = 0; i < this->numberRows; i++) {
		for (int j = 0; j < this->spacesPerRow; j++) {
			(this->ParkingSpaces[i * this->spacesPerRow + j]).displaySpace();
			cout << " ";

		}
		cout << "  ";
	}
	cout << endl;
	
}


//Checks if a bus can be added with the given space as its first space (leftmost space occupied)
bool ParkingLotLevel::canAddBus(int firstSpace) {
	for (int i = firstSpace; i < firstSpace + 5; i++) {
		
		//makes sure the spot is in the level
		if (i > totalSpaces || i < 0) {
			
			return false;
		}

		//Checks to make sure we are not parking the bus in two separate rows
		if (i > firstSpace) {
			if (i % spacesPerRow == 0) {
				return false;
			}
			
		}
		
		//makes sure we are not parking the bus in any non-large or occupied spaces
		if (ParkingSpaces[i].returnType() != 'l') {
			return false;
		}
	}
	
	return true;

}

//Checks if we can park a car in the space whose number is passed
bool ParkingLotLevel::canAddCar(int firstSpace) {
	
	//makes sure the space is in the level
	if (firstSpace > totalSpaces || firstSpace < 0) {
		return false;
	}
	//Makes sure the space isn't occupied or a motorcycle space
	if (ParkingSpaces[firstSpace].isOccupied() || ParkingSpaces[firstSpace].returnType() == 'm') {
		return false;
	}
	
	return true;

}

//Checks if we can park a motorcycle in the space whose number is passed
bool ParkingLotLevel::canAddMotorcycle(int firstSpace) {
	//makes sure the space is in the level
	if (firstSpace > totalSpaces || firstSpace < 0) {
		
		return false;
	}
	//makes sure the space is unoccupied
	if (ParkingSpaces[firstSpace].isOccupied()) {
		return false;
	}
	return true;

}


//Since buses are longer, we need to make sure the remove method works on any space with a bus on it, not just the start of the bus
bool ParkingLotLevel::removeBus(int firstSpace) {
	if (ParkingSpaces[firstSpace].returnType() != 'B') {
		return false;
	}
	int farthestLeft = 0;
	int spaceOn = firstSpace - 1;
	while (ParkingSpaces[spaceOn].returnType() == 'B') {
		farthestLeft++;
		spaceOn--;
		if (spaceOn < 0) {
			break;
		}
	}

	//Makes sure we are only removing the selected bus
	farthestLeft %= 5;

	//figures out the starting space for the bus
	int startSpace = firstSpace - farthestLeft;
	for (int i = startSpace; i < startSpace + 5; i++) {
		ParkingSpaces[i].removeVehicle();
	}

	return true;
}


//If there is a car parked on the space whose number is passed, remove it and return true. Otherwise, return false 
bool ParkingLotLevel::removeCar(int firstSpace) {
	if (ParkingSpaces[firstSpace].returnType() != 'C') {
		return false;
	}
	ParkingSpaces[firstSpace].removeVehicle();

	return true;
}

//If there is a motorcycle parked on the space whose number is passed, remove it and return true. Otherwise, return false 
bool ParkingLotLevel::removeMotorcycle(int firstSpace) {
	if (ParkingSpaces[firstSpace].returnType() != 'M') {
		return false;
	}
	ParkingSpaces[firstSpace].removeVehicle();

	return true;
}



//Park a vehicle whose number type is passed to the function on the space whose number is passed to the function
void ParkingLotLevel::addVehicle(int vehicleNumb, int firstSpace) {
	int spacesTaken = 1;
	if (vehicleNumb == 2) {
		spacesTaken = 5;
	}
	
	for (int i = firstSpace; i < firstSpace + spacesTaken; i++) {
		getSpace(i)->addVehicle(vehicleNumb);
	}

}

//Return the parking space whose number is passed
ParkingSpace *  ParkingLotLevel::getSpace(int spaceNumber) {
	return &ParkingSpaces[spaceNumber];
}

//Checks if any more of the vehicle whose number type is passed can be added in the level
bool ParkingLotLevel::canAddVehicleInLevel(int vehicleNumb) {
	
	for (int i = 0; i < ParkingSpaces.size(); i++) {
		
		if (canAddBus(i) && vehicleNumb == 2) {
			
			return true;
		}
		
		if (vehicleNumb == 1) {
			if (canAddCar(i)) {
				
				return true;
			}
		}
		
		if (canAddMotorcycle(i) && vehicleNumb == 0) {
			
			return true;
		}
		
	}
	
	return false;
}
