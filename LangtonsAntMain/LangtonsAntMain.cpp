/*********************************************************************
** Program name: Langton's Ant
** Author: Anthony Clemente
** Date: 4/6/17
** Description: This program simulates Langton's ant. It allows the
**				user to set the size of the board and either explicitly
**				choose an ant starting point or let it be random.
**				Due to the board not having infinite space, if the
**				ant ever would need to step outside the board, it is
**				designed to "wrap around" to the other side of the board.
*********************************************************************/

#include "LangtonsAnt.hpp"
#include "UserInputValidation.hpp"
#include "Menu.hpp"
#include <time.h>  //for using the time function to seed the random num generator

//Function prototype for function that run through the simulation
void playGame(bool playRandom);

int main()
{
	//Seed the random number with the time which
	//will result in different numbers each time
	//the program is run
	srand(time(0));


	//Welcome the user
	std::cout << "Welcome to the Langton's Ant Simulator!" << std::endl
		<< "Select the type of simulation you would like to run:" << std::endl << std::endl;

	//Declare a gameMenu object
	Menu gameMenu;

	//Use member functions to add options to the menu in the order they will be displayed
	gameMenu.addOption("Choose ant starting position");
	gameMenu.addOption("Random ant starting position");
	gameMenu.addOption("Quit program");

	//Declare an int variable to hold the users choice for this menu
	int userMenuChoice;

	//Declare a bool to indicate whether the user wants to terminate the program
	bool programExit = false;

	//Program will run in loop until the user decides to terminate
	//Allowing for as many simulation runs as desired
	while (!programExit)
	{
		//Show the menu to the user, through the help of a member function
		gameMenu.printMenu();

		//Prompt the user and use an input validation function to
		//get the user to enter an int.
		userMenuChoice = getInt("Select an option: ");

		//Using a member function to check if the integer was a valid choice,
		//the program will re-prompt the user if they need to pick again
		while (!gameMenu.validUserChoice(userMenuChoice))
		{
			userMenuChoice = getInt("Please select a valid option: ");
		}

		//Use a switch statement to act upon the users choice.
		//If this statment is reached, the user's choice is an int and
		//it is a valid menu option
		switch (userMenuChoice)
		{
		case 1:
			//Calls the playGame function, passing in false
			playGame(false);
			break;
		case 2:
			//Calls the playGame function, passing in true
			playGame(true);
			break;
		case 3:
			//Set the boolean to allow loop to end which will cause program
			//to come to the end of main
			programExit = true;
			break;
		default:
			break;
		}
	}

	return 0;
}


//This function sets up the simulation per the user's specifications and then
//creates an Ant object which runs the simulation. This function does not need to
//return a value. The parameter it takes is a boolean which will indicate if the
//ant starting position should be random or not. True means position will be random,
//and false means the user will choose
void playGame(bool playRandom)
{
	//Establish all necessarily variables to set up the simualtion properly
	int boardRows;
	int boardColumns;
	int desiredSteps;
	int antStartRow;
	int antStartCol;

	//Prompt the user for the size of the board in rows and columns and the number of steps the
	//ant should take. At each point the input validation function guarentees the user enters an
	//integer before proceeding. Note that initially the user is warned about making the board too large.
	//All values are also checked for a range that makes sense and will not cause errors.
	std::cout << "You must decide the size of the board." << std::endl 
		<< "Please note that choosing a board size too large will cause" << std::endl
		<< "the program to take more time to print to the screen." << std::endl 
		<< "Try to choose a number lower than 80 for columns as this is" << std::endl
		<< "the default width of the window " << std::endl << std::endl

		<< "First, how many rows would you like? ";

	boardRows = getInt("");

	while (boardRows <= 0)
	{
		std::cout << "Please choose a number greater than 0: ";
		boardRows = getInt("");
	}


	std::cout << "And how many columns? ";

	boardColumns = getInt("");

	while (boardColumns <= 0)
	{
		std::cout << "Please choose a number greater than 0: ";
		boardColumns = getInt("");
	}


	std::cout << "How many steps should the ant take? ";

	desiredSteps = getInt("");

	while (desiredSteps < 0)
	{
		std::cout << "Please enter a non negative number: ";
		desiredSteps = getInt("");
	}

	//If the function argument is false allow the user to choose the ant starting positon
	//via its row and column. This uses the same procedure as above. It also makes sure the
	//user does not try to place the ant outside the array
	if (!playRandom)
	{
		std::cout << "Now you will choose the starting position for the ant" << std::endl
			<< "What row should the ant start in? ";

		antStartRow = getInt("");

		while (antStartRow >= boardRows || antStartRow < 0)
		{
			std::cout << "That is outside of the board! Please choose again: ";
			antStartRow = getInt("");
		}


		std::cout << "Now what column should the ant start in? ";

		antStartCol = getInt("");

		while (antStartCol >= boardColumns || antStartCol < 0)
		{
			std::cout << "That is outside of the board! Please choose again: ";
			antStartCol = getInt("");
		}

	}
	//If the user has expressed they want the position to be random the else if statement triggers
	else if (playRandom)
	{
		//Take the ant starting row and column and set it equal to the
		//result of the rand() function modulo the number of rows and columns the user has requested
		//This will result in a value that is within the array index since the modulo will result in a
		//value anywhere from 0 to boardRows/columns - 1
		antStartRow = rand() % boardRows;
		antStartCol = rand() % boardColumns;
	}

	//Create an ant object with the integers needed for its constructor
	Ant currentAnt(boardRows, boardColumns, desiredSteps, antStartRow, antStartCol);

	//Based upon the user's specifications, the starting state of the board
	//is printed out. Only the ant will be visible though
	std::cout << "Start:" << std::endl;
	currentAnt.printAntBoard();
	std::cout << std::endl;

	//The takeStep function returns a boolean if a step is taken.
	//While this function is returning true, it means the ant has
	//taken another step on the board. This board is then printed out
	while (currentAnt.takeStep())
	{
		currentAnt.printAntBoard();
		std::cout << std::endl;
	}
}