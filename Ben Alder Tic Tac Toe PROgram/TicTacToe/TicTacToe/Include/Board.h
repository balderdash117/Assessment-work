#pragma once
#include <array>
#include "window.h"
#include "../ScoreTracker.h"


class Board : public Window
{
public:
	Board();

	

	void Print();
	void setUp(ScoreTracker *a_score);
	bool IsWinner(int& a_outWinner) const;
	bool IsDraw() const;
	//// setter
	void setGrid(int a_x, int a_y, char a_ch) { m_grid[a_x][a_y] = a_ch; }
	// getter
	char getGrid(int a_x, int a_y) { return m_grid[a_x][a_y]; }
	//
	bool mainLoop(int a_width, int a_height);
	void checkMouseHit(COORD a_pt);
	void get_computer_move();
	int pick_best_move(char board[3][3], char player1, char player2);
	int negamax(char board[3][3], char player1, char player2);
	char check_win(char board[3][3]);
private:
	ScoreTracker *mScore;

	// 'x' is the human player
	bool firstPlayerIsHuman;
	// returns false if the given 1D index is off the grid
	bool ResolveIndex(int a_index1D, int& a_outX, int& a_outY) const;

	// first way to initialize the 2D array
	char m_grid[3][3];

	short mTopX;
	short mTopY;
	short mBoardWidth;
	short mBoardHeight;

};

