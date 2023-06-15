#ifndef _STATS_
#define _STATS_
class Stats
{
private:
	int mScore;
	int mLinesCleared;
	int mTetrises;
	int mLevel;
	int& mWaitTime;
public:
	Stats(int WaitTime);
	void AddScore(int Lines);
	void UpdateLineClears(int Lines);
	void UpdateTetrises(int Lines);
	void UpdateLevel();
	int GetScore();
	int GetLinesCleared();
	int GetTetrises();
	int GetLevel();
};
#endif _STATS_
