/*********************************************************************
** Program name: Langton's Ant
** Author: Anthony Clemente
** Date: 4/6/17
** Description: This file contains the implementation for the Ant class
*********************************************************************/


#include "LangtonsAnt.hpp"

//The only constructor for this class which takes five integer parameters
Ant::Ant(int boardRows, int boardColumns, int maxSteps, int antCurrentRow, int antCurrentColumn)
{
	//Using the this pointer, sets the member variable of the class appropriately
	this->boardRows = boardRows;
	this->boardColumns = boardColumns;
	this->maxSteps = maxSteps;
	this->antCurrentRow = antCurrentRow;
	this->antCurrentColumn = antCurrentColumn;

	//At the start of a simulation the steps will always be zero
	//The starting square will be white
	//The ant will face north to begin
	currentSteps = 0;
	antCurrentSpotColor = charList[0];
	antCurrentDirection = NORTH;

	//Allocate an array of char pointers for the double pointer member variable
	//The number is equal to the number of rows the user desired
	antBoard = new char*[boardRows];

	//For each of the pointers in this array, allocate an array of chars
	//The number is equal to the number of columns the user desired
	for (int i = 0; i < boardRows; i++)
	{
		//The [] dereferences the double pointer giving a single pointer
		//This single pointer can then be givin the address of an array to point at
		antBoard[i] = new char[boardColumns];
	}

	//Use a nested for loop to set each char in the 2D array to the
	//space character which represents the white square
	for (int i = 0; i < boardRows; i++)
	{
		for (int j = 0; j < boardColumns; j++)
		{
			//the [][] dereferences the double pointer giving the memory
			//location of a char which can be set using the list of chars
			//member variable
			antBoard[i][j] = charList[0];
		}
	}

	//Whatever location the user picked for the ant (or if it was random), these
	//values are used to place the '@' at the appropriate location
	antBoard[antCurrentRow][antCurrentColumn] = charList[2];
}


//The Ant class deconstructor is responsible for deallocating the memory used
//by the constructor. This will prevent memory leaks in the program.
Ant::~Ant()
{
	//Deallocate the memory taken by the char arrays for each
	//of the single pointers
	for (int i = 0; i < boardRows; i++)
	{
		delete[] antBoard[i];
	}

	//Deallocate the memory taken by the array of char pointers
	delete[] antBoard;
}

//The following four functions are all very similar and might be able to be combined
//into one function if a better algorithm could be developed. These "sub functions"
//were created to make the takeStep() function less "crowded". Each function takes no
//parameters and has no return type. Based upon the direction they represent, the function
//sets the direction accordingly and updates the ant's position. Here array bound checking
//occurs and the ant is "wrapped around" to the other side of the board if it would ever attempt
//to step out.
void Ant::moveNorth()
{
	//Set enum accordingly
	antCurrentDirection = NORTH;
	//If the ant needs to move north but its current row index is 0,
	//this means it will attempt to step out of bounds
	if (antCurrentRow == 0)
	{
		//boardRows - 1 will equal the highest valid index for the rows of the board
		//The spot color the ant is about to move into is recorded
		antCurrentSpotColor = antBoard[boardRows - 1][antCurrentColumn];

		//The '@' character is set in the appropriate location
		antBoard[boardRows - 1][antCurrentColumn] = charList[2];

		//The new position for the ant (in this case the rows, is recorded)
		antCurrentRow = boardRows - 1;
	}
	else
	{
		//The else condition will run if the ant is not about to step out of
		//bounds. The concept is the same but instead the new row for the ant
		//will just be its current row - 1
		antCurrentSpotColor = antBoard[antCurrentRow - 1][antCurrentColumn];
		antBoard[antCurrentRow - 1][antCurrentColumn] = charList[2];
		antCurrentRow -= 1;
	}
}

void Ant::moveEast()
{
	antCurrentDirection = EAST;
	//If the ant is in a column where the index + 1 is equal to or greater than
	//the max number of columns, than the ant will try to step out of bounds to the right.
	//To wrap the ant around to the other side, the column is set to 0 index which will be the
	//leftmost point on the board
	if (antCurrentColumn + 1 >= boardColumns)
	{
		antCurrentSpotColor = antBoard[antCurrentRow][0];
		antBoard[antCurrentRow][0] = charList[2];
		antCurrentColumn = 0;
	}
	else
	{
		antCurrentSpotColor = antBoard[antCurrentRow][antCurrentColumn + 1];
		antBoard[antCurrentRow][antCurrentColumn + 1] = charList[2];
		antCurrentColumn += 1;
	}
}

void Ant::moveSouth()
{
	antCurrentDirection = SOUTH;
	//If the ant is in a row where the index + 1 is equal to or greater than
	//the max number of row, than the ant will try to step out of bounds through the bottom.
	//To wrap the ant around to the other side, the row is set to 0 index which will be the
	//top point on the board
	if (antCurrentRow + 1 >= boardRows)
	{
		antCurrentSpotColor = antBoard[0][antCurrentColumn];
		antBoard[0][antCurrentColumn] = charList[2];
		antCurrentRow = 0;
	}
	else
	{
		antCurrentSpotColor = antBoard[antCurrentRow + 1][antCurrentColumn];
		antBoard[antCurrentRow + 1][antCurrentColumn] = charList[2];
		antCurrentRow += 1;
	}
}

void Ant::moveWest()
{
	antCurrentDirection = WEST;
	//If the ant is in the leftmost column and is trying to move west,
	//the new column index must be the total board columns - 1
	if (antCurrentColumn == 0)
	{
		antCurrentSpotColor = antBoard[antCurrentRow][boardColumns - 1];
		antBoard[antCurrentRow][boardColumns - 1] = charList[2];
		antCurrentColumn = boardColumns - 1;
	}
	else
	{
		antCurrentSpotColor = antBoard[antCurrentRow][antCurrentColumn - 1];
		antBoard[antCurrentRow][antCurrentColumn - 1] = charList[2];
		antCurrentColumn -= 1;
	}
}



//This function is the main function that runs the simulation. It relies on the
//other move functions once it determines which is appropriate for the given
//situation. The function takes no parameters but returns a boolean if a step was completed
bool Ant::takeStep()
{
	//If the number of steps that have already been completed is
	//greater than or equal to the number of steps the user
	//requested then the step should not be carried out
	if (currentSteps >= maxSteps)
	{
		return false;
	}

	//Display to the user which step is being shown
	std::cout << "Step " << currentSteps + 1 << ":" << std::endl;

	//Use a switch statement that checks which direction the ant is facing
	switch (antCurrentDirection)
	{

		//For each direction the ant is facing, check if the ant is on a 
		//white or black square. Based upon these results set the color of
		//that square accordingly and call the appropriate move function

	case NORTH:
		//For example, tf the ant is on a white square and facing north
		if (antCurrentSpotColor == charList[0])
		{
			//Change that square to black
			antBoard[antCurrentRow][antCurrentColumn] = charList[1];

			//Move the ant east
			moveEast();
		}
		else if (antCurrentSpotColor == charList[1])
		{
			antBoard[antCurrentRow][antCurrentColumn] = charList[0];
			moveWest();
		}
		break;

	case EAST:
		if (antCurrentSpotColor == charList[0])
		{
			antBoard[antCurrentRow][antCurrentColumn] = charList[1];
			moveSouth();
		}
		else if (antCurrentSpotColor == charList[1])
		{
			antBoard[antCurrentRow][antCurrentColumn] = charList[0];
			moveNorth();
			
		}
		break;

	case SOUTH:

		if (antCurrentSpotColor == charList[0])
		{
			antBoard[antCurrentRow][antCurrentColumn] = charList[1];
			moveWest();
			
		}
		else if (antCurrentSpotColor == charList[1])
		{
			antBoard[antCurrentRow][antCurrentColumn] = charList[0];
			moveEast();
		}

		break;

	case WEST:

		if (antCurrentSpotColor == charList[0])
		{
			antBoard[antCurrentRow][antCurrentColumn] = charList[1];
			moveNorth();
		}
		else if (antCurrentSpotColor == charList[1])
		{
			antBoard[antCurrentRow][antCurrentColumn] = charList[0];
			moveSouth();
		}
		break;

	default:
		break;
	}

	//Increment the number of steps before returning true
	currentSteps += 1;
	return true;

}

//Printing out the board uses its own function that takes no parameters
//and returns nothing. It uses a nested for loop to dereference each pointer
//in the array and print out the character at that index
void Ant::printAntBoard()
{
	for (int i = 0; i < boardRows; i++)
	{
		for (int j = 0; j < boardColumns; j++)
		{
			std::cout << antBoard[i][j];
		}
		std::cout << std::endl;
	}
}

