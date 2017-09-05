////////////////////////////////////////////////////////////////////////////////////////////////////////////
////																									////
////		Name:		Tic Tac Toe template															////
////																									////
////		Purpose:	Main program																	////
////																									////
////		Author:		Ben Alder	27/2/2017 															////		
////																									////
////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>

#include "Board.h"
#include "window.h"
#include <time.h>
#include "../ScoreTracker.h"



int main()
{
	Board board;

	// randomize the guessing
	srand((unsigned int)time(NULL));

	// initalize the window
	// (140, 80) is a the maximum
	int width = 120;
	int height = 40;
	// get player play style choice

	//start up game board
	bool result = board.Initialise(width, height, "Tic Tac Toe - 2016 edition");

	if (result == EXIT_FAILURE)	return EXIT_FAILURE;

	ScoreTracker score("score.dat");

	do
	{
		board.setUp(&score);
	} while (board.mainLoop(width, height));

	//system("pause");
	//return 0;
}
