////////////////////////////////////////////////////////////////////////////////////////////////////////////
////																									////
////		Name:		game.h																			////
////																									////
////		Purpose:	establishing the game class														////
////																									////
////		Author:		Roger Keating 																	////
////																									////
////////////////////////////////////////////////////////////////////////////////////////////////////////////

// the new way of making sure this is accessed only once
#pragma once

#define MAX_LINE_CHAR  37		// there will be 37 lines set aside for guessing the real number
#define MAX_LINE_WIDTH 50		// 50 characters are allocated per line

// like a struct only different, more on this later
class Game : public Window {
public:
	// game functions
	void setUpGame(int a_width, int a_height);		// initialize the variables
	bool mainGameLoop();							// this is the game
	void drawMenuChoices(int a_lineNum);			// draw the 'a' to 'c' choices in white or green
	void printAllLines();							// print all the lines with guesses in them
	void pauseTillEscapeHit();						// wait ...
private:
	// game data
	int mMaxGuess;									// current high guess
	int mMinGuess;									// current low guess

	bool mGameOver;									// is game over
	bool gQuitGame;									// quit the game
	int mLinesX;									// x location where the numbers are entered
	int mAdviceX;									// x location where the high or low is mentioned
	int mMaxNum;									// maximum number
	int mGuessNum;									// current guess
	char mGameType;									// game type 'a' 'b' or 'c'
	char mLines[MAX_LINE_CHAR][MAX_LINE_WIDTH];		// lines for the entries
	int mCurrentLineNumber;							// current line you are up to
	int guessNumber;								// current number of guesses
};

