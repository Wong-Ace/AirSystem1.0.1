#pragma once
#include <iostream>
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <conio.h>
#include <fstream>
//All libraries included are necessary for get access to the file system.


void addFlight();
void deleteFlight();
void showFlight();
void backupData();
void fileCheck();
int countFlight();
void admin();
void guest();
void editFlight();
//Fuctions prototype above.

std::string password;
//This is a variable used to store user-input password.


class Flight
{
	int serial;//Serial number of flights. It is unique.
	char dep[30];// Departure IATA code. Set to a maximum of 30, in case of user enters a string too long and crashes program.
	char arr[30];// Arrival IATA code. Same as above.
	float price;// Ticket price of the flight.
	int date;// Date of the flight, in the form of "Day in the year". From 1 to 366.
public:
	void inputFlight();
	void inputWithoutSettingSerial();
	void printFlight();
	int checkExistence(int);
	int returnSerial()
	{
		return serial;
	}
	void setSerial(int x)// Those are the functions in the class. 
	{
		serial = x;
	}
}myFlight, tempFlight; //Two objects are created. Use myFlight to store the information that needs to be written into the file, and use tempFlight to stor information temporarily.