/****************************************************************************
** Program name: User Input Validation
** Author: Anthony Clemente
** Date: 3/26/17 ---- Updated: 4/6/17
** Description: This file contains the function implementations for separate
**				functions designed to get and validate user input for ints.
**				doubles, chars, and strings. Both functions take a prompt that
**				is displayed to the user, which has a default value.
**
**				One allows for a value to be returned from
**				the function (note it will not exit until the user enters
**				an appropriate value), and another version that modifies a
**				reference variable and returns a boolean to indicate success
**				or failure. Two versions for now since I'm not sure what is
**				better necessarily. Functions will likely continue to be
**				updated.
*****************************************************************************/


#include "UserInputValidation.hpp"
#include <iostream>
#include <sstream> //For using a stringstream object

int getInt(std::string promptForUser)
{
	//Declare an int that will hold the user's integer choice after
	//validation. This will be returned by the function.
	int userInt;

	//Boolean for loop control. Keeps track of whether or not the user
	//has succesfully entered an integer
	bool userEnteredInteger = true;

	//String variable to hold the user's raw input
	std::string userInt_Str;

	//Declare two integer varaibles for use with the string.substr() function.
	//This will be used to trim white space from the beginning and end of the string
	int startPos;
	int length;

	//Creates a string stream object that will give the userInt variable the
	//modified user input
	std::stringstream convertedUserInput;

	//Start a do while loop since this action will need to be completed at least once
	do
	{
		//Must set the boolean to true at the start everytime (note this is redundant for the first loop
		//since the bool is already true)
		userEnteredInteger = true;

		//Displays the prompt given to the function and puts a space after it
		std::cout << promptForUser << " ";

		//Gets the user input and stores it as a string
		std::getline(std::cin, userInt_Str);

		//Using two string functions the first non-whitespace character of the input,
		//and the last non-whitespace character is found.
		startPos = userInt_Str.find_first_not_of(' ');

		//The number of characters from the starting point is determined
		//by subtracting the index of the first non-whitespace character found
		//from the index of the last non-whitespace character found and adding 1
		length = userInt_Str.find_last_not_of(' ') - startPos + 1;
		
		//If the character is not found for either of the previous formula, the
		//"npos" constant will be returned (equal to -1). To prevent an error (out of bounds),
		//1 must be added to the startPos so it will be zero and the program will not crash.
		//Note that if the character is not found, length will already be greater than 0 so there is no
		//reason to increment this value as well
		if (startPos == std::string::npos )
		{
			startPos++;
		}

		//Returns the "sub string" that starts at index startPos and takes in "length"
		//number of characters (including the character at the start position). The user's
		//input string is set as this substring. At this point the user's input has been "trimmed"
		//of leading and trailing whitespace
		userInt_Str = userInt_Str.substr(startPos, length);

		//The "trimmed" string is set as the contents to the "convertedUserInput" string stream object
		convertedUserInput.str(userInt_Str);

		//String stream object is streamed to the userInt variable
		convertedUserInput >> userInt;

		//Check if the extraction failed or the extraction succeeded but there 
		//are ASCII characters left in the stream
		if (convertedUserInput.fail() || convertedUserInput.get() >= 0)
		{
			//Sets the control bool to false
			userEnteredInteger = false;

			//Clear any potential errors with the clear() function
			convertedUserInput.clear();
		}

	} while (!userEnteredInteger); //Loop will run if the user's input was not successfully validated
	
	//Returns validated integer
	return userInt;
}



bool getInt(int &userInt, std::string promptForUser)
{

	//String variable to hold the user's raw input
	std::string userInt_Str;

	//Declare two integer varaibles for use with the string.substr() function.
	//This will be used to trim white space from the beginning and end of the string
	int startPos;
	int length;

	//Creates a string stream object that will give the userInt variable the
	//modified user input
	std::stringstream convertedUserInput;
	
	//Displays the prompt given to the function and puts a space after it
	std::cout << promptForUser << " ";

	//Gets the user input and stores it as a string
	std::getline(std::cin, userInt_Str);

	//Using two string functions the first non-whitespace character of the input,
	//and the last non-whitespace character is found.
	startPos = userInt_Str.find_first_not_of(' ');

	//The number of characters from the starting point is determined
	//by subtracting the index of the first non-whitespace character found
	//from the index of the last non-whitespace character found and adding 1
	length = userInt_Str.find_last_not_of(' ') - startPos + 1;

	//If the character is not found for either of the previous formula, the
	//"npos" constant will be returned (equal to -1). To prevent an error (out of bounds),
	//1 must be added to the startPos so it will be zero and the program will not crash.
	//Note that if the character is not found, length will already be greater than 0 so there is no
	//reason to increment this value as well
	if (startPos == std::string::npos)
	{
		startPos++;
	}

	//Returns the "sub string" that starts at index startPos and takes in "length"
	//number of characters (including the character at the start position). The user's
	//input string is set as this substring. At this point the user's input has been "trimmed"
	//of leading and trailing whitespace
	userInt_Str = userInt_Str.substr(startPos, length);

	//The "trimmed" string is set as the contents to the "convertedUserInput" string stream object
	convertedUserInput.str(userInt_Str);

	//String stream object is streamed to the userInt variable
	convertedUserInput >> userInt;

	//Check if the extraction failed or the extraction succeeded but there 
	//are ASCII characters left in the stream
	if (convertedUserInput.fail() || convertedUserInput.get() >= 0)
	{
		//Tell the caller that the user did not enter an int
		//and let the caller decide what to do
		return false;
	}

	//If this line is reached then the user entered a valid int
	return true;
}
