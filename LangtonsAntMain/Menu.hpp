/****************************************************************************
** Program name: Menu
** Author: Anthony Clemente
** Date: 3/26/17
** Description: This file contains the definition of the Menu class. This class
**				has two contructors, a default constructor and a constructor
**				that takes a vector of strings as a parameter. There are
**				member functions for displaying the menu options as well as
**				adding and removing options. There is also a function that 
**				validates a user choice by checking to see if it is in a 
**				valid range for the menu.
*****************************************************************************/


#ifndef MENU_HPP
#define MENU_HPP

#include <string>
#include <vector>


class Menu
{
private:

	//A single member variable, a vector of strings,
	//that holds the menu options
	std::vector<std::string> menuOptions;

public:

	//Two contructors
	Menu();
	Menu(std::vector<std::string>);

	//Member functions
	void addOption(std::string);
	void removeOption(int);
	void printMenu();
	bool validUserChoice(int);
};


#endif