/*********************************************************************
** Program name: Langton's Ant
** Author: Anthony Clemente
** Date: 4/6/17
** Description: This file contains the definition for the Ant class
**				as well as a Direction enum which this class uses. 
*********************************************************************/



#ifndef LANGTONS_ANT_HPP
#define LANGTONS_ANT_HPP

#include <iostream>

//Direction enum that is used to keep track of
//which way the ant is currently facing.
enum Direction
{
	NORTH,
	EAST,
	SOUTH,
	WEST
};

class Ant
{

private:

	//Declare the necessary integers this class needs.
	//All but currentSteps are initialized via the constructor
	int boardRows;
	int boardColumns;
	int maxSteps;
	int currentSteps;
	int antCurrentRow;
	int antCurrentColumn;

	//An array of chars that keeps track of the possible values
	//in the board. ' ' is a white square, '#' is a black square,
	//and '@' is the ant. Another char holds the value for whatever
	//square the ant is currently on (since it must be erased for '@' to be drawn there)
	char charList[3] = { ' ', '#', '@' };
	char antCurrentSpotColor;

	//A char double pointer that is used to allocate
	//a 2D array of chars which represents the board
	//the ant will move in
	char** antBoard;

	//A direction enum which will be used to keep track of how the ant
	//is facing at any point
	Direction antCurrentDirection;

public:

	//One constructor which take the necessary integers
	Ant(int boardRows, int boardColumns, int maxSteps, int antCurrentRow, int antCurrentColumn);

	//A destructor which will deallocate the memory allocated for the 2D array. Will prevent memory leaks. 
	~Ant();

	//Member functions for the Ant class
	//These will control updating the board
	//and displaying reuslts to the screen
	bool takeStep();

	void moveNorth();
	void moveEast();
	void moveSouth();
	void moveWest();

	void printAntBoard();


};

#endif