#include "ScoreTracker.h"



void ScoreTracker::Increase(int a_playerId, int a_amount)
{
	int currentScore = GetScore(a_playerId);
	WriteScore(a_playerId, currentScore + a_amount);
}

int ScoreTracker::GetScore(int a_playerId) const
{
	ifstream fin(mScorePath, ios::in | ios::binary);
	if ((fin.rdstate() & ifstream::failbit) != 0)
	{
		return 0;
	}

	PlayerScore score{ a_playerId, 0 };

	fin.seekg(a_playerId * sizeof(PlayerScore));

	if (!fin.eof() && fin.peek() != EOF)
	{
		fin.read((char*)&score, sizeof(PlayerScore));
	}
	fin.close();
	return score.mScore;
}

void ScoreTracker::WriteScore(int a_playerId, int a_score)
{
	ofstream fout(mScorePath, ios::in | ios::in |ios::binary);
	if (fout.good())
	{
		PlayerScore score{ a_playerId, a_score };
		fout.seekp(a_playerId * sizeof(PlayerScore));
		fout.write((char*)&score, sizeof(PlayerScore));
		fout.close();
	}
}

