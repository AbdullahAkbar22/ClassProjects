/*
		   ____   _____  _____ ____  _____  ______
	 /\   |  _ \ / ____|/ ____/ __ \|  __ \|  ____|
	/  \  | |_) | (___ | |   | |  | | |  | | |__
   / /\ \ |  _ < \___ \| |   | |  | | |  | |  __|
  / ____ \| |_) |____) | |___| |__| | |__| | |____
 /_/    \_\____/|_____/ \_____\____/|_____/|______|

Abdullah Akbar CS 2336.001

This file contains the main() method. It asks the user for input regarding the lot's dimensions, creating the lot
with inputted dimensions. It then takes commands inputted by the user, adding and removing vehicles until none of the vehicles
of inputted type can be added.


*/
                                                   
                                                   

#include <iostream>
#include <string>
#include <vector>
#include "ParkingSpace.h"
#include "ParkingLotLevel.h"
#include "ParkingLot.h"



using namespace std;

ParkingLot theLot = ParkingLot();
//Character that separates the data in user commands when adding/removing vehicles
char dataSeparator = ':';

//Default setup values for the various aspects of the parking lot
int NUM_OF_LEVELS = 5;
int SPOTS_PER_LEVEL = 30;
int SPOTS_PER_ROW = 10;
double LARGE_PERCENTAGE = .2;
double MOTORCYCLE_PERCENTAGE = .2;



//Method I wrote to make sure the string received is indeed a positive integer (used multiple times for input validation)
bool isStringInt(string passedString) {
	//The method makes sure that the ascii value for every character in the string is that of a single int digit
	for (int i = 0; i < passedString.length(); i++) {
		if ((int)passedString[i] < 48 || (int)passedString[i] > 57){
			return false;

		}

	}
	return true;
}


//Method used to display to the user how commands are formatted. Include 4 sample commands
void displayCommandSyntax() {
	cout << endl;
	
	cout << "Commands are formatted as follows:" << endl;
	cout << "NOTE: Commands are NOT case-sensitive" << endl;
	cout << "Single Key Commands:" << endl;
	cout << "X - exits out of program" << endl;
	cout << "? - displays command list" << endl;
	cout << "ADD/REMOVE Commands: " << endl;
	cout << "<A,R>:<C,B,M>:<integer>:<integer>" << endl;
	cout << "Example 1: Adding a car to level 1, space 4" << endl;
	cout << "A:C:1:4" << endl;
	cout << "Alternative syntax:" << endl;
	cout << "Add:Car:1:4" << endl;
	cout << "Example 2: Removing a bus on level 1, space 4" << endl;
	cout << "R:B:1:4" << endl;
	cout << "Alternative syntax:" << endl;
	cout << "Remove:Bus:1:4" << endl;
	cout << endl;
}



//This method takes in a user inputted string and attempts to execute a command using it
//Returns 0 if the command failed, 1 if command succeeded, 2 if parking lot is full
int executeCommand(string commandGiven) {


	//Terminates program if user types x
	if (commandGiven == "x" || commandGiven == "X") {
		cout << "Terminating program" << endl;
		return 2;
	}

	//Display the command syntax if the user simply types ?
	if (commandGiven == "?") {
		displayCommandSyntax();
		return 1;
	}

	//NOTE: from now on, an add/remove command will be referred to as an AR command
	//String vector used to hold the 4 parts of an AR command
	vector<string> data;

	//The following for loop gets all the parts separated by the dataSeparator char defined earlier and pushes them to the data vector
	string dataChunk = "";
	for (int i = 0; i < commandGiven.length(); i++) {
		if (commandGiven[i] == dataSeparator || i == commandGiven.length() - 1) {
			if (i == commandGiven.length() - 1) {
				dataChunk += commandGiven[i];
			}
			data.push_back(dataChunk);
			dataChunk = "";
		}
		else {
			dataChunk += commandGiven[i];
		}
	}
	
	//If there are less than 4 strings in data, the user input was formatted incorrectly
	if (data.size() < 4) {
		cout << "Error: command format incorrect." << endl;
		return 0;
	}

	//in order to allow both the first letter and the whole name of the action and the vehicle type to work, we just get the first character of both data strings
	char commandLetter = data[0][0];
	char vehicleType = data[1][0];

	//VEHICLE NUMBER ASSOCIATION: 0 = Motorcycle, 1 = Car, 2 = Bus. This is used in the ParkingSpace class as well.
	int vehicleNumb = 0;
	if (vehicleType == 'B' || vehicleType == 'b') {
		vehicleNumb = 2;
	}
	else if (vehicleType == 'C' || vehicleType == 'c') {
		vehicleNumb = 1;
	}
	else if (vehicleType == 'M' || vehicleType == 'm') {

	}
	//If the user did not input a valid vehicle, we tell them that
	else {
		cout << "ERROR: Please enter a valid vehicle type (M, C, or B)" << endl;
		return 0;
	}

	//Make sure the level and parking space number data strings are actually valid integers
	if (!isStringInt(data[2]) || !isStringInt(data[3])) {
		cout << "ERROR: Please enter valid integers for the parking space location" << endl;
		return 0;
	}
	//Turn the level and space data strings into integers (we subtract 1 since in the code the spaces start at 0)
	int level = stoi(data[2]) - 1;
	int startSpace = stoi(data[3]) - 1;
	//Makes sure the level and startSpace numbers are within the lot
	if (level >= NUM_OF_LEVELS) {
		cout << "ERROR: Please enter a value within the valid range of levels" << endl;
		return 0;
	}
	if (startSpace >= SPOTS_PER_LEVEL) {
		cout << "ERROR: Please enter a value within the valid range of spaces per level" << endl;
		return 0;
	}


	//Conditional if we have to add a car
	if (commandLetter == 'a' || commandLetter == 'A') {

		//If we cannot add any more of this vehicle, return 2
		if (theLot.fullForVehicle(vehicleNumb)) {
			cout << "Lot full!" << endl;
			return 2;
		}
		
		
		//If we can't add the vehicle at the space given, tell the user
		if ((!theLot.getLevel(level)->canAddBus(startSpace) && vehicleNumb == 2) || (!theLot.getLevel(level)->canAddCar(startSpace) && vehicleNumb == 1) || (!theLot.getLevel(level)->canAddMotorcycle(startSpace) && vehicleNumb == 0) ){
			cout << "Cannot add vehicle in this location !" << endl;
			return 0;
		}
		
		//Otherwise, add the vehicle starting at the space given
		theLot.getLevel(level)->addVehicle(vehicleNumb, startSpace);
		cout << "Successfully added vehicle!" << endl;
		return 1;
	
	}
	//Conditional for removing a vehicle
	else if (commandLetter == 'r' || commandLetter == 'R') {
		if (vehicleNumb == 2) {
			if (theLot.getLevel(level)->removeBus(startSpace)) {
				cout << "Successfully removed bus!" << endl;
				return 1;
			}
			cout << "No bus at that location!" << endl;
			return 0;
		}
		else if (vehicleNumb == 1) {
			if (theLot.getLevel(level)->removeCar(startSpace)) {
				cout << "Successfully removed car!" << endl;
				return 1;
			}
			cout << "No car at that location!" << endl;
			return 0;
		}
		else{
			if (theLot.getLevel(level)->removeMotorcycle(startSpace)) {
				cout << "Successfully removed motorcycle!" << endl;
				return 1;
			}
			cout << "No motorcycle at that location!" << endl;
			return 0;
		}
	}

	//If the AR command did not start with an A or R, tell the user
	else {
		cout << "ERROR: commands must begin with an A or R" << endl;
		return 0;
	}
	return 1;
}


int main()
{
	//This boolean is used to make sure we keep querying the user for setup variables until they input valid setup variables
	bool shouldQuery = true;
	cout << "Leave any of the following values blank for default value" << endl;
	string inputString = "";

	//While loop to get the number of levels
	while (shouldQuery) {
		cout << "Enter number of levels: ";
		getline(cin, inputString);
		if (inputString.size() > 0 && isStringInt(inputString)) {
			NUM_OF_LEVELS = stoi(inputString);
			if (NUM_OF_LEVELS <= 0) {
				cout << "ERROR: number of levels must be greater than 0!" << endl;
				NUM_OF_LEVELS = 5;
			}
			else {
				shouldQuery = false;
			}
		}
		else if (inputString.size() == 0) {
			cout << "Using default value of: " << NUM_OF_LEVELS<< endl;
			shouldQuery = false;
		}
		else {
			cout << "ERROR: Please enter a valid number or leave field blank" << endl;
		}
		inputString = "";

		
	}
	cout << endl;
	shouldQuery = true;
	while (shouldQuery) {
		cout << "Enter number of spaces per level: ";
		getline(cin, inputString);
		if (inputString.size() > 0 && isStringInt(inputString)) {
			SPOTS_PER_LEVEL = stoi(inputString);
			if (SPOTS_PER_LEVEL <= 0) {
				cout << "ERROR: number of spaces per level must be greater than 0!" << endl;
				SPOTS_PER_LEVEL = 30;
			}
			else {
				shouldQuery = false;
			}
		}

		else if (inputString.size() == 0) {
			cout << "Using default value of: " << SPOTS_PER_LEVEL << endl;
			shouldQuery = false;
		}
		else {
			cout << "ERROR: Please enter a valid number or leave field blank" << endl;
		}
		inputString = "";
	}
	cout << endl;
	shouldQuery = true;
	//While loop to get the number of spaces per row
	while (shouldQuery) {

		cout << "Enter number of spaces per row: ";
		getline(cin, inputString);
		if (inputString.size() > 0 && isStringInt(inputString)) {
			SPOTS_PER_ROW = stoi(inputString);
			if (SPOTS_PER_ROW <= 0) {
				cout << "ERROR: number of spaces per row must be greater than 0!" << endl;
				SPOTS_PER_ROW = 10;
			}
			else if (SPOTS_PER_LEVEL % SPOTS_PER_ROW != 0) {
				cout << "ERROR: number of spaces per row must evenly divide the number of spaces per level!" << endl;
				SPOTS_PER_ROW = 10;
			}
			else {
				shouldQuery = false;
			}
		}
		
		else if (inputString.size() == 0) {
			if (SPOTS_PER_LEVEL % SPOTS_PER_ROW != 0) {
				cout << "ERROR: number of spots per row must evenly divide the number of spots per level!" << endl;
			}
			else {
				cout << "Using default value of: " << SPOTS_PER_ROW << endl;
				shouldQuery = false;
			}
		}
		else {
			cout << "ERROR: Please enter a valid number or leave field blank" << endl;
		}
		inputString = "";
	}
	cout << endl;
	shouldQuery = true;
	//While loop to get the percentage of large spaces
	while (shouldQuery) {
		cout << "Enter percentage of spaces per row that are large (0-100): ";
		getline(cin, inputString);
		if (inputString.size() > 0 && isStringInt(inputString)) {
			
			double percentageGiven = stod(inputString);
			if (percentageGiven < 0 || percentageGiven > 100) {
				cout << "ERROR: Percentage must be between 0 and 100!" << endl;
				
			}
			else {
				LARGE_PERCENTAGE = percentageGiven / 100;
				
				shouldQuery = false;
			}
		}

		else if (inputString.size() == 0) {
			
			cout << "Using default value of: " << (LARGE_PERCENTAGE * 100) << "%" << endl;
			shouldQuery = false;
		}
		else {
			cout << "ERROR: Please enter a valid number or leave field blank" << endl;
		}
		inputString = "";
	}

	cout << endl;


	shouldQuery = true;
	//While loop to get the percentage of motorcycle spaces
	while (shouldQuery) {
		cout << "Enter percentage of spaces per row that are for motorcycles (0-100): ";
		getline(cin, inputString);
		if (inputString.size() > 0 && isStringInt(inputString)) {

			double percentageGiven = stod(inputString);
			if (percentageGiven < 0 || percentageGiven > 100) {
				cout << "ERROR: Percentage must be between 0 and 100!" << endl;

			}
			else {
				MOTORCYCLE_PERCENTAGE = percentageGiven / 100;

				if (MOTORCYCLE_PERCENTAGE + LARGE_PERCENTAGE > 1) {
					cout << "ERROR: Motorcycle space percentage and large spot percentage together cannot exceed 100%!" << endl;
					MOTORCYCLE_PERCENTAGE = .2;

					//Tacter
				}
				else {
					shouldQuery = false;
				}
			}
		}

		else if (inputString.size() == 0) {

			cout << "Using default value of: " << (MOTORCYCLE_PERCENTAGE * 100) << "%" << endl;
			shouldQuery = false;
		}
		else {
			cout << "ERROR: Please enter a valid number or leave field blank" << endl;
		}
		inputString = "";
	}

	cout << endl;
	
	//Set up the parking lot based on the setup variable values we have just received
	for (int i = 0; i < NUM_OF_LEVELS; i++) {
		ParkingLotLevel theLevel = ParkingLotLevel();
		theLevel.setUpLevel(SPOTS_PER_LEVEL, SPOTS_PER_ROW, LARGE_PERCENTAGE, MOTORCYCLE_PERCENTAGE);
		theLot.addLevel(theLevel);
	}
	
	
	
	
	//The following code displays a prompt asking the user to input a command
	//It then executes the command and displays the updated parking lot until a certain vehicle cannot be added
	//After which the program terminates.
	theLot.displayLot();
	cout << endl;
	string commandString = "";
	cout << "Type ? to view command syntax" << endl;
	cout << "Enter parking command: ";
	getline(cin, commandString);

	while (executeCommand(commandString) != 2) {
		theLot.displayLot();
		cout << endl;
		cout << "Type ? to view command syntax" << endl;
		cout << "Enter parking command: ";
		getline(cin, commandString);
		
	}
	theLot.displayLot();
}
