/****************************************************************************
** Program name: User Input Validation
** Author: Anthony Clemente
** Date: 3/26/17 ---- Updated: 4/6/17
** Description: This file contains the function definitions for separate 
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


#ifndef USER_INPUT_VALIDATION_HPP
#define USER_INPUT_VALIDATION_HPP

#include <string>

int getInt(std::string promptForUser = "Enter an integer:");
bool getInt(int &userInt, std::string promptForUser = "Enter an integer:");


#endif
