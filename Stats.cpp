#include "Stats.h"

Stats::Stats(long& WaitTime):mWaitTime(WaitTime)
{
    Stats::mScore = 0;
    Stats::mLinesCleared = 0;
    Stats::mTetrises = 0;
    Stats::mLevel = 1;
}

void Stats::AddScore(int Lines)
{
    switch (Lines)
    {
    case 1:
        mScore += 40;
        break;
    case 2:
        mScore += 100;
        break;
    case 3:
        mScore += 300;
        break;
    case 4:
        mScore += 1200;
        mTetrises++;
        break;
    }
}

void Stats::UpdateLineClears(int Lines)
{
    mLinesCleared += Lines;
}

void Stats::UpdateTetrises(int Lines)
{
    if (Lines==4)
        mTetrises++;
}

void Stats::UpdateLevel() 
{
    if (mScore < 2000) 
    {
        mLevel = 1;
        mWaitTime = 600;
    }
    else if (mScore < 4000) 
    {
        mLevel = 2;
        mWaitTime = 500;
    }
    else if (mScore < 8000)
    {
        mLevel = 3;
        mWaitTime = 400;
    }
    else 
    {
        mLevel = 4;
        mWaitTime = 350;
    }
}
