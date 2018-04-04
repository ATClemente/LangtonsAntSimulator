/****************************************************************************
** Program name: Menu
** Author: Anthony Clemente
** Date: 3/26/17
** Description: This file contains the implementation of the Menu class. 
**				Functions are all relatively simple, and rely on functions from
**				the vector class that this class uses.
*****************************************************************************/


#include "Menu.hpp"
#include <iostream>

Menu::Menu()
{
	//The default contructor does nothing.
	//If creating an object this way the addOption()
	//function will be used to add items to the menu
}


Menu::Menu(std::vector<std::string> menuOptions)
{
	//Sets the class's vector to the vector passed as an argument
	this->menuOptions = menuOptions;
}

void Menu::addOption(std::string option)
{
	//Uses the vector push_back function to add
	//an option to the menu
	menuOptions.push_back(option);
}

void Menu::removeOption(int option)
{
	//Removes the menu option specified by the argument
	//Note it takes the option and subtracts 1 to find the right index in the vector
	menuOptions.erase(menuOptions.begin() + (option - 1));
}

void Menu::printMenu()
{
	//Sets up a for loop
	for (unsigned int currentIndex = 0; currentIndex < menuOptions.size(); currentIndex++)
	{
		//For each element in the vector, prints out a number for the position (this will be the index plus 1),
		//and prints out the menu option at the current index
		std::cout << currentIndex + 1 << ". " << menuOptions.at(currentIndex) << std::endl;
	}

	std::cout << std::endl;
}

bool Menu::validUserChoice(int userChoice)
{
	//User's choice can not be less than 1 (since menus will start at 1)
	//Choice can also not be greater than the total number of elements in the vector
	//which is givin by the size function
	if (userChoice < 1 || userChoice > menuOptions.size())
	{
		//Return false to the caller if the choice is not valid
		return false;
	}
	
	//If the previous if statement does not run, then the choice was in a valid range
	return true;
}