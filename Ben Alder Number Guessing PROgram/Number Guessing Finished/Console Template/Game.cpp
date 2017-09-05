////////////////////////////////////////////////////////////////////////////////////////////////////////////
////																									////
////		Name:		Number Guessing Game															////
////																									////
////		Purpose:	All the game functions															////
////																									////
////		Author:		Ben Alder	 																	////
////																									////
////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "window.h"
#include "main.h"
#include <time.h>
#include "Game.h"

using std::cin;

void Game::drawMenuChoices(int a_lineNum)
{
	eColor lineColor;

	lineColor = (mGameType == 'a') ? GREEN : WHITE;
	DrawTextLine(1, a_lineNum, lineColor, 
		"a) The computer guesses the number", 100);

	lineColor = (mGameType == 'b') ? GREEN : WHITE;
	DrawTextLine(1, a_lineNum + 2, lineColor, 
		"b) I guess the number", 100);

	lineColor = (mGameType == 'c') ? GREEN : WHITE;
	DrawTextLine(1, a_lineNum + 4, lineColor, 
		"c) Put system on auto", 100);

}

void Game::setUpGame(int a_width, int a_height)
{
	char tempStr[256];

	Rect pLocation = { 0, 0, a_width, a_height };
	DrawBorder(pLocation, BLUE);

	// initialize input lines
	for (int i = 0; i < MAX_LINE_CHAR; ++i) 
	{
		strcpy_s(mLines[i], " ");
	}

	mCurrentLineNumber	= 0;
	mLinesX				= 80;
	mAdviceX			= 100;
	guessNumber			= 0;
	gQuitGame			= false;
	mGameOver			= false;

	// input the maximum number
	bool inputNumber = true;
	int lineNum = 2;
	char ch;
	while (inputNumber) 
	{
		DrawTextLine(1, lineNum + 1, WHITE, "Enter the maximum number (10 - 30000) = ", 100);
		cin >> mMaxNum;
		// this flushes the buffer
		while ((ch = getchar()) != '\n' && ch != EOF);

		//switch (mMaxNum)
		//{
			
			if (mMaxNum < 10 || mMaxNum > 30000)
			{
				mMaxNum = 0;
				DrawTextLine(1, lineNum, RED, "Enter a correct number", 100);
				DrawTextLine(1, lineNum + 1, WHITE, "                                                            ", 100);
			}
			else
			{
				DrawTextLine(1, lineNum, RED, "                             ", 100);
				inputNumber = false;
			}
		//}
	}

	bool inputGameType = true;
	lineNum = 8;
	while (inputGameType)
	{
		drawMenuChoices(lineNum);
		DrawTextLine(1, lineNum + 7, WHITE, "Enter the maximum number (a, b or c) = ", 100);
		cin >> mGameType;
		// this flushes the buffer
		while ((ch = getchar()) != '\n' && ch != EOF);

		// bring up a web browser
		//if (mGameType == 'w') 
		//{
		//	ShowWindow(GetConsoleWindow(), SW_MINIMIZE);

		//	ShellExecute(0, 0, L"C:\Users\s163112\Documents\Snakes and Ladders", 0, 0, SW_SHOW);
		//}

		if (mGameType < 'a' || mGameType > 'c') 
		{
			mGameType = 0;
			DrawTextLine(1, lineNum + 6, RED, "Enter a, b or c", 100);
			DrawTextLine(1, lineNum + 7, WHITE, "                                                            ", 100);
		}
		else 
		{
			DrawTextLine(1, lineNum + 6, RED, "                             ", 100);
			inputGameType = false;
			drawMenuChoices(lineNum);
		}
	}

	if (mGameType == 'a') 
	{
		bool inputNumber = true;
		lineNum = 18;
		while (inputNumber)
		{
			DrawTextLine(1, lineNum + 1, WHITE, "Enter a number to guess = ", 100);
			cin >> mGuessNum;
			// this flushes the buffer
			while ((ch = getchar()) != '\n' && ch != EOF);

			if (mGuessNum < 1 || mGuessNum > mMaxNum) 
			{
				mGuessNum = 0;
				DrawTextLine(1, lineNum, RED, "Enter a correct number", 100);
				DrawTextLine(1, lineNum + 1, WHITE, "                                                            ", 100);
			}
			else
			{
				DrawTextLine(1, lineNum, RED, "                             ", 100);
				inputNumber = false;
			}
		}
	}
	else if (mGameType == 'b') 
	{
		mGuessNum = rand() % mMaxNum + 1;
	}
	else if (mGameType == 'c') 
	{
		lineNum = 18;
		mGuessNum = rand() % mMaxNum + 1;
		sprintf_s(tempStr, "The number to guess is = %d", mGuessNum);
		DrawTextLine(1, lineNum + 1, WHITE, tempStr, 100);
	}

	// set the maximum and minimum number for guesses
	mMaxGuess = mMaxNum;
	mMinGuess = 1;;
}

void Game::printAllLines()
{
	// write all the current lines, up to mCurrentLineNumber
	for (int y = 0; y <mCurrentLineNumber + 1; ++y) 
	{
		DrawTextLine(mLinesX, y + 1, GREEN, mLines[y], 100);
	}
}

void Game::pauseTillEscapeHit()
{
	// wait until the ESC key is hit, system("pause") would disrupt the screen to much
	while (GetKeyState(VK_ESCAPE) >= 0) 
	{
	}
}

bool Game::mainGameLoop()
{
	int a_lineNum;
	char playChoice;
	bool play;
//	eColor lineColor;

	a_lineNum = 8;
	play = true;

	while (play)
	{
		// this is the important bit
		while (!gQuitGame)
		{
			if (mCurrentLineNumber == MAX_LINE_CHAR)
			{
				for (int i = 0; i < MAX_LINE_CHAR; ++i)
				{
					strcpy_s(mLines[i], "                          ");
				}
				printAllLines();
				mCurrentLineNumber = 0;
			}

			// is the game over
			if (mGameOver)
			{
				// this has no meaning .... yet
				pauseTillEscapeHit();
				return false;
			}

			//char tempStr[256];
			int trial;
			char ch, guessHigh;
			bool inputInProgress = true;
			switch (mGameType)
			{
			case'a':
			case'c':
				trial = (mMaxGuess - mMinGuess) / 2 + mMinGuess;
				sprintf_s(mLines[mCurrentLineNumber],"%3d:  %5d", ++guessNumber, trial);
				break;
			case'b':
				while (inputInProgress)
				{
					SetXY(mLinesX + 1, mCurrentLineNumber + 1);
					cin >> trial;
					//Flushing the buffer
					while ((ch = getchar()) != '\n' && ch != EOF);

					if (trial >= mMinGuess && trial <= mMaxGuess)
					{
						sprintf_s(mLines[mCurrentLineNumber], "%3d: %5d", ++guessNumber, trial);
						inputInProgress = false;
					}
				}
				break;
			}

			printAllLines();

			if (trial == mGuessNum) {
				// yeh, got it
				SetXY(mLinesX, mCurrentLineNumber + 1);
				SetTextColor(GREEN);
				cout << "Got it .. " << trial << endl; 
				//SetXY(1, 34);
				//cout << "" << endl;
				
				int lineNum = 1;
				DrawTextLine(1, lineNum + 20, GREEN, "Please enter (Y) to continue with other operations ", 100);
				cin >> playChoice;

				if (playChoice == 'y' || playChoice == 'Y')
				{
					play = true;
					mGameType = 0;
					system("cls");
					return true;
				}
				else
				{
					play = false;
					SetXY(40, 25);
					system("pause");
					system("cls");
					return false;
				}
								
				//pauseTillEscapeHit();
				
			}
			// work out what sort of game it is
			switch (mGameType) 
			{
			case'a':
		
				while (inputInProgress)
				{
					SetXY(mAdviceX, mCurrentLineNumber + 1);
					cin >> guessHigh;
					// this flushes the buffer
					while ((ch = getchar()) != '\n' && ch != EOF);

					if (guessHigh == 'l') mMaxGuess = trial, inputInProgress = false;
					else if (guessHigh == 'h') mMinGuess = trial, inputInProgress = false;
				}
				mCurrentLineNumber++;
				break;
			case'b':

			case'c':

				if (trial < mGuessNum)
				{
					// higher
					mMinGuess = trial;
					strcat_s(mLines[mCurrentLineNumber], " low");
				}
				else  if (trial > mGuessNum)
				{
					// lower
					mMaxGuess = trial;
					strcat_s(mLines[mCurrentLineNumber], " high");
				}
				mCurrentLineNumber++;
				// print lines again as they have been modified a little
				printAllLines();
				break;
			}
		}
		
		//cout << "please enter (Y) to continue with other operations" << endl;
		
	}
	return false;
}
