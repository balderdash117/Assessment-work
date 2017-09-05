#pragma once

#include <fstream>

using std::string;
using std::ios;
using std::ifstream;
using std::ofstream;


class ScoreTracker
{
public:
	struct PlayerScore
	{
		int mPlayerId;
		int mScore;
	};
	ScoreTracker() = default;
	ScoreTracker(string a_scorePath) : mScorePath(a_scorePath)
	{
		ofstream fout(mScorePath, ios::out | ios::binary | ios::app);
		if (fout.good())
		{
			fout.close();
		}
	};

	void Increase(int a_playerId, int a_amount);
	int GetScore(int a_playerId) const;

private:
	void WriteScore(int a_playerId, int a_score);
	string mScorePath;
};

