#ifndef _STATS_
#define _STATS_
class Stats 
{
private:
    int mScore;
    int mLinesCleared;
    int mTetrises;
    int mLevel;
    long& mWaitTime;
public:
    Stats(long& WaitTime);
    void AddScore(int Lines);
    void UpdateLineClears(int Lines);
    void UpdateTetrises(int Lines);
    void UpdateLevel();
};
#endif _STATS_
