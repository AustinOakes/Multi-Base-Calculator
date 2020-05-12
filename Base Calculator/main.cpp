/*************************************************************************

PROGRAMMER:		Austin Oakes

PROGRAM NAME:	Multi-Base Calculator

DESCRIPTION:

	A calculator that is able to perform basic operations on
	numbers between the bases of 2 - 36. The user will be able to 
	issue multiple different types of commands. There will be 26
	memory locations for storing the results of calculations for
	future use. These results are stored using a map. There will 
	be a 27th pair in the map to represent the accumulator, which
	will be used in current operations. The user may end the program
	by using the OFF command.

	***CURRENTLY ASSUMES PROPER USER INPUT***

*************************************************************************/

#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <cctype>
	using namespace std;

void InitMap(map<string, string>& mapToInit);
//Narrative:		Takes a reference to a map and initializes it for the program.
//Preconditions:	Map must be Empty before initializing.
//Postconditions:	Map will contain the proper memory spaces needed for 
//					program calculations.

void Reset(map<string, string>& mapToInit, int &base);
//Narrative:		Resets the calculator
//Preconditions:	The map of memory locations and current base
//Postconditions:	Memory locations will be reinitialized and base set to 10

int AsciiToInt(char temp);
//Narrative:		Converts a char into its integer representation.
//Preconditions:	A char must be passed in.
//Postconditions:	Char whill be returned in its Integer representation.

char IntToAscii(int temp);
//Narrative:		Converts an integer into its ASCII representation.
//Preconditions:	An integer must be passed in.
//Postconditions:	Integer will be returned in its ASCII representation.

void PrintMap(map<string, string>& myMap, int currBase);
//Narrative:		Print the contents of myMap using an iterator.	
//Preconditions:	myMap should not be empty.
//Postconditions:	myMap contents will be displayed to the user on screen.

void PrintAccumulator(map<string, string>& myMap, int currBase);
//Narrative:		Prints the current value of the accumulator.
//Preconditions:	Map holding the accumulator and the current base.
//Postconditions:	Memory location $0 will be printed.

void GetCommand(string &command);
//Narrative:		Gets the next command from the user.
//Preconditions:	A variable for storing the command.
//Postconditions:	The command is stored.

void PrintError();
//Narrative:		Prints an error message when an invalid command is entered.	
//Preconditions:	User enter an unrecognizable command.
//Postconditions:	Message is displayed on screen, user is again asked for input.

void ValidateCommand(string command, bool& valid);
//Narrative:		Checks if the command provided is valid.
//Preconditions:	Command provided by user, bool to represent validity.
//Postconditions:	valid will reflect whether the command is valid or not.

void Uppercase(string& command);
//Narrative:		Sets the input string to all uppercase.
//Preconditions:	A string to uppercase.
//Postconditions:	Each character in the string will be uppercase.

void HelpMenu();
//Narrative:		Prints the help menu.
//Preconditions:	None
//Postconditions:	Help menu will be displayed to the user.

void GetValues(string& val1, string& val2);
//Narrative:		Asks user for two numbers for an operation
//Preconditions:	Two strings to hold the values.
//Postconditions:	Each string will contain a number in the format num@base

void ProcessVal(string& input, bool& validValue, string& numValue, string& delimeter, char& memLocation, string& numBase);
//Narrative:		Breaks up the number input from the user to be used more easily.
//Preconditions:	The number input to be parsed,
//					A bool to represent validity,
//					A string to hold the number representation,
//					A string to hold the delimeter of number and base,
//					A char respresenting the memory location,
//					A string for the base of the input number
//Postconditions:	Based on the input, each argument will be filled accordingly,
//					Some may be empty based on if memory location or new number.

string ConvertBase(string &sValue, string &sBase, int currBase);
//Narrative:		Converts a number to 
//Preconditions:	A string conatining the value of the number,
//					A string holding the base of the value,
//					An int with the calculator current base
//Postconditions:

string toDecimal(string num, int base);
//Narrative:		Converts a number to decimal.
//Preconditions:	A string containing the number to convert,
//					An int containing its base.
//Postconditions:	String will be returned containing the new converted decimal number.

string fromDecimal(int base, string num);
//Narrative:		Converts a number to any base between 2-36 from base 10.
//Preconditions:	The base to convert to & num to convert.
//Postconditions:	A string will be returned containing the newly converted value.

int CharToInt(char c);
//Narrative:		Converts a char to its integer representation.
//Preconditions:	A non-empty char.
//Postconditions:	The integer returned will be representative of c.

char IntToChar(int c);
//Narrative:		Converts an int to a char.
//Preconditions:	A single digit int to convert to char.
//Postconditions:	The char returned will contain the representation of c.

void Store(map<string, string> &myMap);
//Narrative:		Stores the value of the accumulator into a storage locations.
//Preconditions:	The map containing the current storage locations.
//Postconditions:	The accumulator value will be stored in the specified location.

void Add(map<string, string>& myMap, int currBase);
//Narrative:		Asks the user for two values to add together.
//Preconditions:	The map of memory locations and the calculators current base.
//Postconditions:	The two values will be added together and stored in the accumulator.

void Subtract(map<string, string>& myMap, int currBase);
//Narrative:		Asks the user for two values to subtract.
//Preconditions:	The map of memory locations and the calculators current base.
//Postconditions:	The two values will be subtracted and stored in the accumulator.

string PrepValForOp(map<string, string> myMap, string value, string numBase, int currBase, char memLocation, string delimeter);
//Narrative:		Preps a vaue for a mathematical operation, called after ProcessVal()
//Preconditions:	The map containing the storage locations,
//					String containing the number value,
//					String containing the base of the number,
//					Char representing the memory location,
//					The delimeter used at input.
//Postconditions:	A string will be returned containing with a number ready for the operation,
//					sets to base 10.

void SetAccumulator(map<string, string> &myMap, int currBase);
//Narrative:		Asks the user for a new value for the accumulator.
//Preconditions:	Map of storage locations,
//					Current base of the calculator.
//Postconditions:	The users entered value will be stored in the accumulator in the
//					calculators current base.

void LoadIntoAccumulator(map<string, string>& myMap);
//Narrative:		Loads a storage location into the accumulator.	
//Preconditions:	The map containing the storage locations.
//Postconditions:	The accumulator will contain the value of the specified location.

void SetBase(map<string, string>& myMap, int& currBase);
//Narrative:		Sets the current base of the calculator.
//Preconditions:	The map contianing contents of all current storage locations,
//					The current base of the calculator.
//Postconditions:	The base will be set to the users entered new base,
//					All storage locations will also be converted.

int main() {

	int base = 10;
	double opResult = 0;
	string input = "";
	string command = "";
	string newBase = "";
	string delimeter = "";
	string numBase = "";
	string numValue = "";
	string temp = "";
	string result = "";
	char memLocation;
	bool validValue = false;
	bool valid = false;

	map<string, string> storageLocations;
	InitMap(storageLocations);

	while (command != "OFF") {	//OFF indicates program end

		command = "";
		valid = false;
		validValue = false;
		delimeter = "";
		numBase = "";
		numValue = "";
		memLocation = '\0';
		temp = "";
		result = "";

		while (valid == false) {	//While the command is invalid
			
			GetCommand(command);
			Uppercase(command);
			ValidateCommand(command, valid);
		}

		if (command != "OFF") {	
		
			if (command == "DUMP") {	//Dump memory locations
			
				PrintMap(storageLocations, base);
			}
			else if(command == "PRINT") {	//Print the accumulator
			
				PrintAccumulator(storageLocations, base);
			}
			else if (command == "SET") {	//Set the accumulator value
			
				SetAccumulator(storageLocations, base);
			}
			else if (command == "RESET") {	//Reset the calculator
				
				Reset(storageLocations, base);
			}
			else if (command == "LOAD") {	//Load a storage location into the accumulator
			
				LoadIntoAccumulator(storageLocations);
			}
			else if (command == "BASE") {	//Set the calculator base
			
				SetBase(storageLocations, base);
			}
			else if (command == "H") {	//Open the help menu

				HelpMenu();
			}
			else if (command == "STORE") {	//Store the value of the accumulator
			
				Store(storageLocations);
			}
			else if (command == "ADD") {	//Add two values

				Add(storageLocations, base);
			}
			else if (command == "SUBTRACT") {	//Subtract two values
			
				Subtract(storageLocations, base);
			}
		}
	}

	cout << endl;
	cout << "Exiting..." << endl;
	
	return 0;
}

//Initializes the map of memory locations to 0
void InitMap(map<string, string>& mapToInit) {

	string result;
	int charCounter = 65; //int representation of 'A', increment for 'B', so forth...
	char rep;

	mapToInit.insert(pair<string, string>("$0", "0"));	//Accumulator

	for(int i = 0; i < 26; i++) {	//For all storage locations
		
		rep = IntToAscii(charCounter);	//Get the letter for the key
		result = "";
		result = result + "$" + rep;

		mapToInit.insert(pair<string, string>(result, "0"));	//Insert the storage location
		charCounter++;
	}	

	return;
}

//Returns the integer representation of an Ascii character
int AsciiToInt(char temp) {

	return (int) temp;
}

//Returns the Ascii representation of an integer
char IntToAscii(int temp) {

	return (char) temp;
}

//Prints all of the memory location contents, 
void PrintMap(map<string, string>& myMap, int currBase) {

	cout << endl;

	//until the end of the map
	for (auto iterator = myMap.cbegin(); iterator != myMap.cend(); ++iterator) {

		cout << iterator->first << " " << iterator->second << "@" << currBase << endl;
	}

	cout << endl;

	return;
}

//Prints the current value stored in the accumulator, map key $0
void PrintAccumulator(map<string, string>& myMap, int currBase) {

	cout << "$0 " << myMap.find("$0")->second << "@" << currBase << endl << endl;

	return;
}

//Gets a command from the user
void GetCommand(string &command) {

	cout << "Please enter a command..." << endl;
	cout << "(Need Help? Enter H)" << endl << endl;
	cout << "% ";
	cin >> command;

	return;
}

//Checks if the user entered a proper command, otherwise print error
void ValidateCommand(string command, bool &valid) {

	if (command == "OFF") {
		valid = true;
	}
	else if (command == "RESET") {
		valid = true;
	}
	else if (command == "SET") {
		valid = true;
	}
	else if (command == "DUMP") {
		valid = true;
	}
	else if (command == "BASE") {
		valid = true;
	}
	else if (command == "LOAD") {
		valid = true;
	}
	else if (command == "STORE") {
		valid = true;
	}
	else if (command == "PRINT") {
		valid = true;
	}
	else if (command == "ADD") {
		valid = true;
	}
	else if (command == "SUBTRACT") {
		valid = true;
	}
	else if (command == "MULTIPLY") {
		valid = true;
	}
	else if (command == "DIVIDE") {
		valid = true;
	}
	else if (command == "H") {
		valid = true;
	}
	else {
		PrintError();
	}

	return;
}

//Makes the command entered all uppercase letters
void Uppercase(string &command) {

	for (int i = 0; i < command.size(); i++) {
	
		command[i] = toupper(command[i]);
	}

	return;
}

//Prints an error regarding the users input
void PrintError() {

	cout << endl << "Invalid input, please try again..." << endl << endl;

	return;
}

//Prints a help menu with a list of commands
void HelpMenu() {

	cout << endl;
	cout << "COMMANDS:" << endl << endl;
	cout << "OFF - Terminates the program." << endl;
	cout << "RESET - Resets the current base and memory locations." << endl;
	cout << "SET - Sets the value of the accumulator." << endl;
	cout << "DUMP - Print the contents of each memory location." << endl;
	cout << "BASE - Set the current base of the calculator." << endl;
	cout << "LOAD - Loads a memory loacation into the accumulator." << endl;
	cout << "STORE - Stores the accumulator value to a memory location." << endl;
	cout << "PRINT - Prints the value of the accumulator in the current base." << endl;
	cout << "ADD - Adds two values and stores in the accumulator." << endl;
	cout << "SUBTRACT - Subtracts two values and stores in the accumulator." << endl;
	cout << endl;

	return;
}

//Reset the calculator, base 10 & memory locations reinitialized
void Reset(map<string, string>& map, int& base) {

	base = 10;
	map.clear();
	InitMap(map);

	cout << endl << "Memory locations & base have been reset!" << endl << endl;

	return;
}

//Gets values from the user for addition & subtraction
void GetValues(string& val1, string& val2) {

	cout << "Enter two value to operate on..." << endl << endl;
	cout << "ex. Formats:" << endl;
	cout << "\tMemory Location: $A" << endl;
	cout << "or..." << endl;
	cout << "\tNew Value: num@base" << endl << endl;

	cout << "Value 1 = ";
	cin >> val1;
	cout << "Value 2 = ";
	cin >> val2;
	cout << endl;

	return;
}

//Parses/breaks up the user input so that it can be used properly
void ProcessVal(string &input, bool &validValue, string &numValue, string &delimeter, char &memLocation, string &numBase) {

	int position = 0;

	for (int i = 0; i < input.size(); i++) {	//Parse for delimeter
	
		if (input[i] == '$' || input[i] == '@') {	//if location i is a valid delimeter
		
			delimeter = input[i];

			if (delimeter == "$" && i == 0) {	//If memory location
			
				memLocation = input[i + 1];
				validValue = true;
			}
			else if (delimeter == "@") {	//If new value
			
				numValue = input.substr(0, i);
				numBase = input.substr(i+1, input.size());
				validValue = true;
			}
		}
	}

	return;
}

//Converts the base of sValue to the new base, sBase
string ConvertBase(string &sValue, string &sBase, int currBase) {

	int base = stoi(sBase);
	string sResult = "";

	if (base != currBase) {	//If the new base is not the same as the current

		sResult = toDecimal(sValue, base);
		sResult = fromDecimal(stoi(sBase), sResult);
	}

	return sResult;
}

//Converts any base between 2-36 to base 10
string toDecimal(string num, int base) {

	int result = 0;
	int power = 1;
	bool neg = false;

	if (num[0] == '-') {	//Check if negative
	
		num = num.substr(1, num.length());
		neg = true;
	}

	for (int i = num.length() - 1; i >= 0; i--) {	//Perform ops to convert

		result += CharToInt(num[i]) * power;
		power = power * base;
	}

	if (neg == true) {	//If negative, multiply by -1
	
		result = result * -1;
	}

	return to_string(result);	//Return as a string
}

//Converts a base 10 number to any other base between 2-36
string fromDecimal(int base, string num) {

	string result = "";
	string remainder = "";
	bool neg = false;

	if (num[0] == '-') {	//Check if negative
	
		num = num = num.substr(1, num.length());
		neg = true;
	}

	if (stoi(num) == 0) {	//If num is 0

		result = "0";
	}

	while (stoi(num) > 0) {	//Perform ops to convert

		result = result + IntToChar(stoi(num) % base);
		num = to_string(stoi(num) / base);
	}

	reverse(result.begin(), result.end());	//reverse the result

	if (neg == true) {	//if neg, add neg symbol
	
		result = '-' + result;
	}

	return result;
}

//Converts a char to int
int CharToInt(char c){

	if (c >= '0' && c <= '9'){

		return (int)c - '0';
	}
	else {
	
		return (int)c - 'A' + 10;
	}
}

//Converts an int to char
char IntToChar(int c) {

	if (c >= 0 && c <= 9) {

		return (char)(c + '0');
	}
	else {

		return (char)(c - 10 + 'A');
	}
}

//Stores the accumulator value to a memory location
void Store(map<string, string> &myMap) {

	string memLoc = "";
	bool valid = false;

	while (valid == false) {	//While the user hasnt entered a valid location

		//Prompt for location
		cout << "Please enter a memory location to store in: ";
		cin >> memLoc;

		if (memLoc[0] != '$' || memLoc.size() != 2) {	//Check if valid format

			cout << "Invalid location, try between $A - $Z" << endl;
		}
		else {	//format is valid

			if (memLoc[1] >= 'A' && memLoc[1] <= 'Z') {	//Check if valid letter
			
				cout << "Accumulator value stored in "<< memLoc << endl;
				
				//Store the value into the valid location
				myMap.find(memLoc)->second = myMap.find("$0")->second;

				valid = true;
			}
			else {	//if letter invalid
			
				cout << "Invalid location, try between $A - $Z" << endl;
			}
		}
	}

	return;
}

//Adds two values together and stores the result in the accumulator
void Add(map<string, string>& myMap, int currBase) {

	string val1 = "";
	string val2 = "";
	string delimeter = "";
	string numValue = "";
	string numBase = "";
	char memLocation = '\0';
	int opResult = 0;
	bool validValue = false;

	//Get Values
	GetValues(val1, val2);

	//Convert them to decimal
	ProcessVal(val1, validValue, numValue, delimeter, memLocation, numBase);
	val1 = PrepValForOp(myMap, numValue, numBase, currBase, memLocation, delimeter);

	ProcessVal(val2, validValue, numValue, delimeter, memLocation, numBase);
	val2 = PrepValForOp(myMap, numValue, numBase, currBase, memLocation, delimeter);

	//Add them
	opResult = stod(val1) + stod(val2);

	//Convert to calculator base / Put into accumulator
	if (currBase != 10) {

		myMap.find("$0")->second = fromDecimal(currBase, to_string(opResult));
	}
	else {

		myMap.find("$0")->second = to_string(opResult);
	}

	//Print Accumulator
	PrintAccumulator(myMap, currBase);

	return;
}

//Subtracts two values and stores the result in the accumulator
void Subtract(map<string, string>& myMap, int currBase) {
	
	string val1 = "";
	string val2 = "";
	string delimeter = "";
	string numValue = "";
	string numBase = "";
	char memLocation = '\0';
	double opResult = 0;
	bool validValue = false;

	//Get Values
	GetValues(val1, val2);

	//Convert them to decimal
	ProcessVal(val1, validValue, numValue, delimeter, memLocation, numBase);
	val1 = PrepValForOp(myMap, numValue, numBase, currBase, memLocation, delimeter);

	ProcessVal(val2, validValue, numValue, delimeter, memLocation, numBase);
	val2 = PrepValForOp(myMap, numValue, numBase, currBase, memLocation, delimeter);

	//Subtract them

	opResult = stod(val1) - stod(val2);

	//Convert to calculator base / Put into accumulator
	if (currBase != 10) {

		myMap.find("$0")->second = fromDecimal(currBase, to_string(opResult));
	}
	else {

		myMap.find("$0")->second = to_string(opResult);
	}
	//Print Accumulator

	PrintAccumulator(myMap, currBase);

	return;
}

//Preps a value for a math operation, sets the value to base 10.
string PrepValForOp(map<string, string> myMap, string value, string numBase, int currBase, char memLocation, string delimeter) {

	string temp = "";

	if (delimeter == "@") {	//If value is new

		value = toDecimal(value, stoi(numBase));
	}
	else if (delimeter == "$") {	//If value is from a memory location

		temp = delimeter + memLocation;
		value = myMap.find(temp)->second;
		value = toDecimal(value, currBase);
	}

	return value;
}

//Set the accumulator value
void SetAccumulator(map<string, string>& myMap, int currBase) {

	string input = "";
	string numValue = "";
	string delimeter = "";
	char memLocation = '\0';
	string numBase = "";
	string result = "";
	bool validValue = false;
	
	//Ask user for value to set the accumulator to
	cout << "Please enter a value the accumulator: ";
	cin >> input;
	
	//Process the input & convert to the calculator base
	ProcessVal(input, validValue, numValue, delimeter, memLocation, numBase);
	result = ConvertBase(numValue, numBase, currBase);

	//Store converted value into the accumulator
	myMap.find("$0")->second = result;

	return;
}

//Loads a memory location value into the accumulator
void LoadIntoAccumulator(map<string, string>& myMap) {

	string memLoc = "";

	//Prompt for memory Location
	cout << "Please enter a memory location to load: ";
	cin >> memLoc;

	//Set accumulator to contents of specified location
	myMap.find("$0")->second = myMap.find(memLoc)->second;

	return;
}

//Sets the current base of the calculator, sets all memory locations to that base 
void SetBase(map<string, string>& myMap, int& currBase) {

	string result = "";
	string newBase = "";
	string prevBase = to_string(currBase);
	int charCounter = 65;	//int representation of 'A', increment for 'B', so forth...
	char rep = '\0';

	cout << "Please enter a new base for the calculator: ";	//Get new base
	cin >> newBase;

	myMap.find("$0")->second = ConvertBase(myMap.find("$0")->second, newBase, currBase);
	
	for (int i = 0; i < 26; i++) {	//for all Storage locations

		//Generate the next key to look up
		rep = IntToAscii(charCounter);
		result = "";
		result = result + "$" + rep;

		//Convert contents of memorylocation
		myMap.find(result)->second = ConvertBase(myMap.find(result)->second, newBase, currBase);

		charCounter++;		
	}

	currBase = stoi(newBase);	//Set the current base

	return;
}

