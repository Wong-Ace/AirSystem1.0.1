/*
This program provides a group of function for users to edit the database of flight information.
*/
#include"define.h"

void Flight::inputWithoutSettingSerial() // The function used to get the flight information, without asking for serial number.
{
	dep[3] = '\0';
	std::cout << "Input the departure IATA code:\n"; 
	std::cin >> dep;
	while (dep[0] < 'A' || dep[0]>'Z' || dep[1] < 'A' || dep[1]>'Z' || dep[2] < 'A' || dep[2]>'Z' || dep[3] != '\0') // Check whether user is entering wrong information. The IATA code must be 3 capital characters.
	{
		std::cout << "Please input 3 capital characters.\n"; 
		std::cin >> dep;
	}
	std::cout << "Input the arrival IATA code:\n"; 
	std::cin >> arr;
	while (arr[0] < 'A' || arr[0]>'Z' || arr[1] < 'A' || arr[1]>'Z' || arr[2] < 'A' || arr[2]>'Z' || arr[3] != '\0')
	{
		std::cout << "Please input 3 capital characters.\n"; 
		std::cin >> arr;
	}
	std::cout << "Set the ticket price:\n"; 
	std::cin >> price;
	std::cout << "Set the date of the flight:(day of the year)\n"; 
	std::cin >> date; 
	while (date > 366 || date < 1) 
	{ 
		std::cout << "Please input a number between 1 and 365.\n"; 
		std::cin >> date;
	}//Check whether user is entering right date. Day of the year must be between 1 and 366. I wrote 365 here because 2017 is not a leap year.
}

void Flight::inputFlight()// The function used to get the flight information. Asking for serial number.
{
	dep[3] = '\0';
	do
	{
		std::cout << "Input serial number of the flight:\n"; 
		std::cin >> serial; //Calling out the checking function, to ensure that user won't input the same serial number which already exists in the database.
		if (checkExistence(serial) == 1) 
		{ 
			std::cout << "A flight of the same serial number already exists, please try again.\n";
		}
	} 
	while (checkExistence(serial) == 1);
	std::cout << "Input the departure IATA code:\n"; 
	std::cin >> dep;
	while (dep[0] < 'A' || dep[0]>'Z' || dep[1] < 'A' || dep[1]>'Z' || dep[2] < 'A' || dep[2]>'Z' || dep[3] != '\0')
	{
		std::cout << "Please input 3 capital characters.\n";
		std::cin >> dep;
	}
	std::cout << "Input the arrival IATA code:\n";
	std::cin >> arr;
	while (arr[0] < 'A' || arr[0]>'Z' || arr[1] < 'A' || arr[1]>'Z' || arr[2] < 'A' || arr[2]>'Z' || arr[3] != '\0')
	{
		std::cout << "Please input 3 capital characters.\n";
		std::cin >> arr;
	}
	std::cout << "Set the ticket price:\n";
	std::cin >> price;
	std::cout << "Set the date of the flight:(day of the year)\n"; 
	std::cin >> date; 
	while (date > 366 || date < 1)
	{
		std::cout << "Please input a number between 1 and 365.\n"; 
		std::cin >> date;
	}
}

void Flight::printFlight()
{
	std::cout << "Serial number: " << serial << "\tDeparture: " << dep << "\tArrival: " << arr << "\tPrice: $" << price << "\tdate: " << date << std::endl; // A simple function used to show the information of one flight.
}

int Flight::checkExistence(int a)// Check the existence of a certain serial number. Vitally important for the safety of database.
{
	std::fstream myFile("C:\\Users\\ALIENWARE\\Desktop\\Flight.dat", std::ios::in | std::ios::binary);
	myFile.seekg(0);
	while (!myFile.eof())//Read the database from beginning to the end.
	{
		myFile.read((char*)&tempFlight, sizeof(tempFlight));
		if (tempFlight.serial == a)
		{ 
			myFile.close();
			return 1; 
		} //If the serial already exists, return 1.
	}
	return 0;
	myFile.close();

}

void addFlight()//The function used to add a flight into database.
{
	std::string ans = "yes";
	while (ans == "yes" || ans == "Yes" || ans == "YES")//Used for checking that whether user wants to enter multiple information.
	{
		myFlight.inputFlight();
		std::fstream myFile("C:\\Users\\ALIENWARE\\Desktop\\Flight.dat", std::ios::app | std::ios::binary);//Using ios::app to add information to the end of the program.
		myFile.write((char*)&myFlight, sizeof(myFlight));
		myFile.close();
		std::cout << "Need to add more? Input \"yes\" to continue, or any other character to exit:\n";
		std::cin >> ans;
	}
}

void showFlight()//The function used to show all information in the database.
{
	std::fstream myFile("C:\\Users\\ALIENWARE\\Desktop\\Flight.dat", std::ios::in | std::ios::binary);
	myFile.seekg(0);//Make sure we start from the beginning of the database.
	while (!myFile.eof())
	{
		myFile.read((char*)&tempFlight, sizeof(tempFlight));//Read the first, second, .....the last flight.
		if (myFile.eof()) break;
		tempFlight.printFlight();//Print the information of one flight.
	}
	myFile.close();
}

void deleteFlight()//The function used to delete a certain flight from database.
{
	int a;
	std::cout << "Input the serial number of the flight that you want to delete:\n"; 
	std::cin >> a;// Acquire the serial number from user. Knowing which one to delete.
	while (myFlight.checkExistence(a) == 0)
	{
		std::cout << "Serial does not exist. Please try again...\n";
		std::cin >> a;
	}
	std::fstream tempFile("C:\\Users\\ALIENWARE\\Desktop\\Temporary.dat", std::ios::binary | std::ios::out | std::ios::trunc);
	std::fstream myFile("C:\\Users\\ALIENWARE\\Desktop\\Flight.dat", std::ios::binary | std::ios::in);//Opening two different files. One for reading and one for writing.
	while (!myFile.eof())
	{
		myFile.read((char*)&tempFlight, sizeof(tempFlight));
		if (myFile.eof()) break;
		if (tempFlight.returnSerial() != a) tempFile.write((char*)&tempFlight, sizeof(tempFlight));// Writing all the data from original file to the temporary file, except the one chosen by the user.
	}
	myFile.close();
	tempFile.close();
	std::cout << "Rewrite done.\n";
	remove("C:\\Users\\ALIENWARE\\Desktop\\Flight.dat");
	rename("C:\\Users\\ALIENWARE\\Desktop\\Temporary.dat", "C:\\Users\\ALIENWARE\\Desktop\\Flight.dat");// Remove the original file and rename the Temporary file.

}

void backupData()
{
	std::fstream tempFile("C:\\Users\\ALIENWARE\\Desktop\\Backup.dat", std::ios::binary | std::ios::out | std::ios::trunc);
	std::fstream myFile("C:\\Users\\ALIENWARE\\Desktop\\Flight.dat", std::ios::binary | std::ios::in);
	myFile.seekg(0);
	tempFile.seekp(0);
	while (!myFile.eof())
	{
		myFile.read((char*)&tempFlight, sizeof(tempFlight));
		if (myFile.eof()) break;
		tempFile.write((char*)&tempFlight, sizeof(tempFlight));
	}
	myFile.close();
	tempFile.close();
	std::cout << "Backup done.";// Well, this is not actually necessary. We can simply use "copy" function to back up our database, but this is the original shape of the "delete" function. Without writing this function first, it would be extremely eifficult to finish the "deleteFlight" function.

}

void fileCheck()
{
	std::fstream myFile;
	myFile.open("C:\\Users\\ALIENWARE\\Desktop\\Flight.dat", std::ios::in | std::ios::binary);
	if (!myFile)
	{ 
		std::cout << "Data file does not exist! Please check whether the file Flight.dat exists!";
		system("pause");
		exit(0);
	}
}//Check whether the database exists. Will be called at the beginning of the program.

void editFlight()//Used to edit a certain flight.
{
	int a;
	std::cout << "Input the serial number of the flight that you want to edit:\n"; 
	std::cin >> a; // Get the serial number of the flight which user wants to edit.
	while (myFlight.checkExistence(a) == 0)
	{
		std::cout << "Serial does not exist. Please try again...\n";
		std::cin >> a;//Check whether it exists.
	}
	std::fstream myFile("C:\\Users\\ALIENWARE\\Desktop\\Flight.dat", std::ios::in | std::ios::out | std::ios::binary);
	std::ios::pos_type pos;
	while (!myFile.eof())//Read the file from beginning to the end.
	{
		int tempSerial;
		pos = myFile.tellg();//Setting a variable to save the position of the pointer in the file.
		myFile.read((char*)&tempFlight, sizeof(tempFlight));

		if (tempFlight.returnSerial() == a)//If there is a serial number in database that matches user's choice, ...
		{
			std::cout << "Flight found. Now enter the new information of this flight.\n";//Tell the user we've found it.
			std::cout << "Set a new serial number for the flight:\n";
			std::cin >> tempSerial;
			myFlight.setSerial(tempSerial);
			while (myFlight.checkExistence(tempSerial) && (tempSerial != a))
			{
				std::cout << "This serial is occupied. Please use another one:\n";
				std::cin >> tempSerial;
				myFlight.setSerial(tempSerial);
			}

			myFlight.inputWithoutSettingSerial();//As you can see, we must not use "inputFlight()" here, because that function will check whether the serial number exists. If we want to edit a flight but does not change it serial number, we have to do it step by step.

			myFile.seekp(pos);
			myFile.write((char*)&myFlight, sizeof(myFlight));//Go find the position where we acquire the flight, re-write it.
			std::cout << "Information edited.\n";
			break;
		}

	}
	myFile.close();

}

int countFlight()//A simple function used to acquire the total number of flights in the database. Not used in the main program, but very useful if we want to do some advanced programming. For example, sorting the flights.
{
	std::fstream myFile("C:\\Users\\ALIENWARE\\Desktop\\Flight.dat", std::ios::in | std::ios::binary);
	int i = 0;
	while (!myFile.eof())
	{
		myFile.read((char*)&myFlight, sizeof(myFlight));
		if (myFile.eof()) break;
		i++;
	}
	return i;
}

void admin()//The function that provides an administrator's interface.
{
	std::cout << "Input your admin password:\n";
	std::cin >> password;
	while (password != "defaultpassword") 
	{ 
		std::cout << "Wrong password. Try again..\n";
		std::cin >> password; 
	}//Ask and verify the password.
	system("cls");//Clear the screen.
	while (true) 
	{
		auto choice = 0;

		system("cls");//Clear it again. For loops.
		std::cout << "\t***************************************\n";
		std::cout << "\t*                                     *\n";
		std::cout << "\t*          1.See all flights          *\n";
		std::cout << "\t*      2.Add flight into database     *\n";
		std::cout << "\t*    3.Delete flight from database    *\n";
		std::cout << "\t*     4.Edit a flight information     *\n";
		std::cout << "\t*          5.Backup database          *\n";
		std::cout << "\t*              6.Exit                 *\n";
		std::cout << "\t*                                     *\n";
		std::cout << "\t***************************************\n";
		std::cin >> choice;
		while (choice > 6 || choice < 1)
		{ 
			std::cout << "Please input the number from 1 to 6. Try again..\n"; 
			std::cin >> choice;
		}
		switch (choice)
		{
		case 1:
		{
			showFlight();
			system("pause");
			break;
		}
		case 2:
		{
			addFlight();
			std::cout << "Printing the new flight list:\n";
			showFlight();
			system("pause");
			break;
		}
		case 3:
		{
			deleteFlight();
			std::cout << "Printing the new flight list:\n";
			showFlight();
			system("pause");
			break;
		}
		case 4://After adding/deleting/editing flights, show the flights again.
		{
			editFlight();
			std::cout << "Printing the new flight list:\n";
			showFlight();
			system("pause");
			break;
		}
		case 5:
		{
			backupData();
			system("pause");
			break;
		}
		case 6:// Pause after executing each feature, because we want the user to see the printed information, instead of returning to the menu immediately.
		{
			std::cout << "Returning to last menu..\n"; 
			system("pause");
			return; }
		}
	}
}

void guest()//The user interface for guests. Only seeing the flights is available. No password needed.
{
	while (true) 
	{
		auto choice = 0;

		system("cls");
		std::cout << "\t***************************************\n";
		std::cout << "\t*                                     *\n";
		std::cout << "\t*          1.See all flights          *\n";
		std::cout << "\t*              2.Exit                 *\n";
		std::cout << "\t*                                     *\n";
		std::cout << "\t***************************************\n";
		std::cin >> choice;
		while (choice > 2 || choice < 1)
		{
			std::cout << "Please input the number from 1 to 6. Try again..\n";
			std::cin >> choice; 
		}
		switch (choice)
		{
			case 1: 
			{
				showFlight(); system("pause"); break; }
			case 2: 
			{
				std::cout << "Returning to last menu..\n";
				system("pause");
				return;
			}
		}
	}
}

int main()//Main function
{
	int id;
	fileCheck();//Check whether the database exists. Exit if not.
	while (true)
	{
		system("cls");//Clear the screen.
		std::cout << "\t***************************************\n";
		std::cout << "\t*                                     *\n";
		std::cout << "\t*          Welcome to ezFligt         *\n";
		std::cout << "\t*        Select your identity:        *\n";
		std::cout << "\t*           1.Administrator           *\n";
		std::cout << "\t*               2.Guest               *\n";
		std::cout << "\t*               3.Exit                *\n";
		std::cout << "\t*                                     *\n";
		std::cout << "\t***************************************\n";
		std::cin >> id;
		while (id != 1 && id != 2 && id != 3)
		{
			std::cout << "Please input the number 1 or 2. Try again..\n";
			std::cin >> id;
		}// Checking if the user is making meaningful choice.
		system("cls");//Clear the screen for loop.
		switch (id)
		{
		case 1: 
			admin();
			break;
		case 2:
			guest();
			break;
		case 3: 
		{
			std::cout << "Exiting...\n"; exit(0);
		}
		default: exit(0);
		}
	}
}
