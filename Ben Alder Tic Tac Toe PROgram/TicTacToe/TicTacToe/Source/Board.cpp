////////////////////////////////////////////////////////////////////////////////////////////////////////////
////																									////
////		Name:		board.cpp																		////
////																									////
////		Purpose:	all game board events															////
////		Uses:		http://code.runnable.com/Vnjjxm6IJit89Bpu/tic-tac-toe-unbeatable-ai-for-c%2B%2B	////
////					to show how to run a simple recusive board routine								////												
////																									////
////		Authors:	Ben Alder	27/2/2017															////
////																									////
////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <stdlib.h>
#include "Board.h"
#include "window.h"

using std::cin;
using std::endl;
using std::string;

// constructor
Board::Board()
{
	mScore = nullptr;
	setUp(nullptr);
}

void Board::setUp(ScoreTracker *a_score)
{
	if (a_score != nullptr) 
	{
		mScore = a_score;
	}
	firstPlayerIsHuman = true;

	for (int x = 0; x<3; ++x)
		for (int y = 0; y<3; ++y)
			m_grid[x][y] = ' ';

	mTopX = 31;
	mTopY = 6;
	mBoardWidth = 57;
	mBoardHeight = 27;
}

// Why is there no destuctor????

// the main game loop
bool Board::mainLoop(int a_width, int a_height)
{
	Rect pLocation = { 0, 0, a_width, a_height };
	DrawBorder(pLocation, DARKCYAN);

	if (mScore != nullptr) {
		string currentScore = "The score is Human = " + std::to_string(mScore->GetScore(0)) +
			" - Computer = " + std::to_string(mScore->GetScore(1));
		SetXY((a_width - (int)currentScore.size()) / 2, 2);
		cout << currentScore;
	}


	// make the playing platform
	int yRow[] = { mTopY + mBoardHeight / 3, mTopY + 2 * mBoardHeight / 3 };
	int xRow[] = { mTopX + mBoardWidth / 3, mTopX + 2 * mBoardWidth / 3 };

	char playChoice;
	bool PlayAgain;

	static int humWin = 0;
	static int comWin = 0;


	// lines across
	for (int i = 0; i < 2; ++i)
		for (int x = mTopX; x < mTopX + mBoardWidth; ++x)
			DrawChar(x, yRow[i], char(205));
	// lines down
	for (int i = 0; i < 2; ++i)
		for (int y = mTopY; y < mTopY + mBoardHeight; ++y)
			DrawChar(xRow[i], y, char(186));

	bool mouseIsDown = false;
	int count = 0;
	while (true) {
		COORD pt = getMousePos();
		if (pt.X == -1) continue;

		if (!mouseIsDown && (GetKeyState(VK_LBUTTON) & 0x100)) {
			// mouse is down..
			mouseIsDown = true;
			checkMouseHit(pt);
			count++;
		}
		else if (!(GetKeyState(VK_LBUTTON) & 0x100)) {
			mouseIsDown = false;
		}

		// is there a winner
		int winner;
		if (IsWinner(winner)) {
			SetTextColor(WHITE);
			SetXY(2, a_height - 5);
			if (winner == 1)
				++comWin;
			else
				++humWin;

			cout << "Winner is - " << ((winner == 1) ? "Computer" : "Human") << endl;
			SetXY(86, a_height - 3);
			cout << "Human Wins = " << humWin << "  " << "Computer Wins = " << comWin << endl;
			SetXY(2, a_height - 4);
			cout << "Please enter (Y) to continue with other operations " ;
			cin >> playChoice;

			if (playChoice == 'y' || playChoice == 'Y')
			{
				PlayAgain = true;
				SetXY(2, a_height - 3);
				system("cls");
				return true;
			}
			else
			{
				PlayAgain = false;
				SetXY(2, a_height - 3);
				system("cls");
				return false;
			}
			break;

			mScore->Increase(winner, 1);
		}
		//draw
		if (IsDraw()) {
			SetTextColor(WHITE);
			SetXY(2, a_height - 5);
			cout << "It is a draw!" << endl;
			SetXY(86, a_height - 3);
			cout << "Human Wins = " << humWin << "  " << "Computer Wins = " << comWin << endl;
			SetXY(2, a_height - 4);
			cout << "Please enter (Y) to continue with other operations " ;
			cin >> playChoice;

			if (playChoice == 'y' || playChoice == 'Y')
			{
				PlayAgain = true;
				SetXY(2, a_height - 3);
				system("cls");
				return true;
			}
			else
			{
				PlayAgain = false;
				SetXY(2, a_height - 3);
				system("cls");
				return false;
			}
			break;
		}

	}
}

// print the board
	void Board::Print()
{
	short ptX[] = { mTopX + 5, mTopX + 25, mTopX + 45 };
	short ptY[] = { mTopY + 1, mTopY + 11, mTopY + 20 };
	eColor oColor = GREEN;
	char oValue[][20] = {
		"OOOOOOO",
		"O     O",
		"O     O",
		"O     O",
		"O     O",
		"OOOOOOO"
	};
	eColor xColor = CYAN;
	char xValue[][20] = {
		"       ",
		" x   x ",
		"  x x  ",
		"   x   ",
		"  x x  ",
		" x   x "
	};

	for (int x = 0; x<3; ++x)
		for (int y = 0; y < 3; ++y) {
			if (m_grid[x][y] == ' ') continue;

			for (int i = 0; i < 6; ++i) {
				SetXY(ptX[x], ptY[y] + i);
				SetTextColor((m_grid[x][y] == 'x' ? xColor : oColor));
				cout << (m_grid[x][y] == 'x' ? xValue[i] : oValue[i]) << endl;
			}
	}
}

// is there a winner
bool Board::IsWinner(int& a_outWinner) const
{
	// check rows
	for (int i = 0; i < 3; ++i)
	{
		// same across row
		if (m_grid[i][0] != ' ' && m_grid[i][0] == m_grid[i][1] && m_grid[i][1] == m_grid[i][2])
		{
			a_outWinner = m_grid[i][0] == 'x' ? 0 : 1;
			return true;
		}
	}

	// check columns
	for (int i = 0; i < 3; ++i)
	{
		// same down column
		if (m_grid[0][i] != ' ' && m_grid[0][i] == m_grid[1][i] && m_grid[1][i] == m_grid[2][i])
		{
			a_outWinner = m_grid[0][i] == 'x' ? 0 : 1;
			return true;
		}
	}

	// check diagonal (top left)
	if (m_grid[0][0] != ' ' && m_grid[0][0] == m_grid[1][1] && m_grid[1][1] == m_grid[2][2])
	{
		a_outWinner = m_grid[0][0] == 'x' ? 0 : 1;
		return true;
	}

	// check diagonal (top right)
	if (m_grid[2][0] != ' ' && m_grid[2][0] == m_grid[1][1] && m_grid[1][1] == m_grid[0][2])
	{
		a_outWinner = m_grid[2][0] == 'x' ? 0 : 1;
		return true;
	}

	// no winner found
	a_outWinner = -1;
	return false;
}

// is it a draw
bool Board::IsDraw() const
{
	// no winner means it might be a draw
	int winnerIdx;
	if (!IsWinner(winnerIdx))
	{
		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				// we still have a cell in the grid without a choice
				if (m_grid[i][j] != 'x' &&
					m_grid[i][j] != 'o')
				{
					return false;
				}
			}
		}
	}

	return true;
}

bool Board::ResolveIndex(int a_index1D, int& a_outX, int& a_outY) const
{
	a_outY = a_index1D % 3;
	a_outX = a_index1D / 3;

	// was the given index even on the grid?
	return a_index1D >= 0 && a_index1D < 9;
}

// AI steps - this is the 'imported' code
char Board::check_win(char board[3][3]) {

	// Check horizontal, vertical & diagonal through [0][0]
	if (board[0][0] != '.' && (board[0][0] == board[0][1] && board[0][0] == board[0][2] ||
		board[0][0] == board[1][0] && board[0][0] == board[2][0] ||
		board[0][0] == board[1][1] && board[0][0] == board[2][2]))

		return board[0][0];

	// Check horizontal, vertical & diagonal through [1][1]
	if (board[1][1] != '.' && (board[1][1] == board[1][0] && board[1][1] == board[1][2] ||
		board[1][1] == board[0][1] && board[1][1] == board[2][1] ||
		board[1][1] == board[2][0] && board[1][1] == board[0][2]))

		return board[1][1];

	// Check horizontal, vertical & diagonal through [2][2]
	if (board[2][2] != '.' && (board[2][2] == board[0][2] && board[2][2] == board[1][2] ||
		board[2][2] == board[2][0] && board[2][2] == board[2][1]))

		return board[2][2];

	return 0;
}

// AI steps 
int Board::pick_best_move(char board[3][3], char player1, char player2)
{
	int best_move_score = -9999;
	int best_move_row = -9999;
	int best_move_col = -9999;
	int score_for_this_move = 0;

	for (int r = 0; r < 3; r++) {
		for (int c = 0; c < 3; c++) {
			if (board[r][c] == ' ') {
				board[r][c] = player1; //Try test move.
				score_for_this_move = -(negamax(board, player2, player1));
				board[r][c] = ' '; //Put back test move.
				if (score_for_this_move >= best_move_score) {
					best_move_score = score_for_this_move;
					best_move_row = r;
					best_move_col = c;
				}
			}
		}
	}
	return (10 * best_move_row + best_move_col);
}

/*********************************************************************
** Function: negamax
** Description: Recursively calls itself to play out every possible
** position.
** Parameters: char[3][3], char, char
** Pre-Conditions: pick_best_move has been called.
** Post-Conditions: Returns best_score_move to pick_best_move
*********************************************************************/
int Board::negamax(char board[3][3], char player1, char player2) {

	int best_move_score = -9999;
	int score_for_this_move = 0;

	//If player 1 wins, then the score is high (good for player1)
	if (check_win(board) == player1) return 1000;

	//If player 2 loses, then the score is low (bad for player1)
	else if (check_win(board) == player2) return -1000;

	for (int r = 0; r < 3; r++) {
		for (int c = 0; c < 3; c++) {
			if (board[r][c] == '.') {
				board[r][c] = player1; //Try test move.
				score_for_this_move = -(negamax(board, player2, player1));
				board[r][c] = '.'; //Put back test move.
				if (score_for_this_move >= best_move_score) {
					best_move_score = score_for_this_move;
				}
			}
		}
	}

	if (best_move_score == -9999 || best_move_score == 0) return 0;

	else if (best_move_score < 0) return best_move_score + 1;

	else if (best_move_score > 0)
		return best_move_score - 1; //As the game goes longer, and the recursion goes deeper, the moves near the end are less favorable than in the beginning.

	return 0;
}

void Board::get_computer_move() //AI move input
{
#if 0 // one easy way
	int i, j;
	for (i = 0; i<3; i++) {
		for (j = 0; j<3; j++)
			if (m_grid[i][j] == ' ') break;
		if (m_grid[i][j] == ' ') break;
	}

	if (i*j == 9) {
		return;
	} else
		m_grid[i][j] = 'o';
#else // second easy way
	//If the space is empty
	if (m_grid[0][0] == ' ')
	{
		//Fill the space with the CPU's character
		m_grid[0][0] = 'o';
	}
	else if (m_grid[1][0] == ' ')
	{
		//Fill the space with the CPU's character
		m_grid[1][0] = 'o';
	}
	else if (m_grid[2][0] == ' ')
	{
		//Fill the space with the CPU's character
		m_grid[2][0] = 'o';
	}
	else if (m_grid[0][1] == ' ')
	{
		//Fill the space with the CPU's character
		m_grid[0][1] = 'o';
	}
	else if (m_grid[1][1] == ' ')
	{
		//Fill the space with the CPU's character
		m_grid[1][1] = 'o';
	}
	else if (m_grid[1][2] == ' ')
	{
		//Fill the space with the CPU's character
		m_grid[1][2] = 'o';
	}
	else if (m_grid[2][0] == ' ')
	{
		//Fill the space with the CPU's character
		m_grid[2][0] = 'o';
	}
	else if (m_grid[2][1] == ' ')
	{
		//Fill the space with the CPU's character
		m_grid[2][1] = 'o';
	}
	else if (m_grid[2][2] == ' ')
	{
		//Fill the space with the CPU's character
		m_grid[2][2] = 'o';
	}
#endif
}

// hit the board with the mouse
void Board::checkMouseHit(COORD a_pt)
{
	int x = 3, y = 3;

	//what zone are we in?
	if (a_pt.X > mTopX + 4 && a_pt.X < mTopX + mBoardWidth - 4) {
		x = 0;
		if (a_pt.X > mTopX + 4 + 20) x = 1;
		if (a_pt.X > mTopX + 4 + 20 + 20) x = 2;
	}
	if (a_pt.Y > mTopY + 1 && a_pt.Y < mTopY + mBoardHeight - 1) {
		y = 0;
		if (a_pt.Y > mTopY + 10) y = 1;
		if (a_pt.Y > mTopY + 10 + 9) y = 2;
	}
	SetTextColor(WHITE);
	SetXY(2, 2);
	cout << x << "  " << y;
	//On the board
	if (x >= 0 && x < 3 && y >= 0 && y < 3) {
		if (m_grid[x][y] != ' ') return;
		//Human is an x
		m_grid[x][y] = 'x';

		int outwinner;
		if (!IsWinner(outwinner)) {
			char tempBoard[3][3];
			for (int x = 0; x < 3; ++x)
				for (int y = 0; y < 3; ++y)
					tempBoard[x][y] = m_grid[x][y];
			//and call the AI
			int where_to_move = pick_best_move(tempBoard, 'x', 'o');
			int row = where_to_move / 10;
			int col = where_to_move % 10;
			if (row >= 0 && row < 3 && col >= 0 && col < 3)
				m_grid[row][col] = 'o';
		}

		Print();
		//and end
	}

}

