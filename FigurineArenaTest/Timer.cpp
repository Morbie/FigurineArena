#include "Timer.h"
#include <Windows.h>


CTimer::CTimer() : mSecondsPerCount(0.0), mDeltaTime(-1.0), mBaseTime(0),
mPausedTime(0), mPreviousTime(0), mCurrentTime(0), mStopped(false)
{
	_int64 countsPerSec;
	QueryPerformanceFrequency((LARGE_INTEGER*)&countsPerSec);
}


CTimer::~CTimer()
{
}


float CTimer::getTime()const
{
	if (mStopped)
	{
		return (float)((mStopTime - mBaseTime)*mSecondsPerCount);
	}
	else
	{
		return (float)(((mCurrentTime - mPausedTime) - mBaseTime)*mSecondsPerCount);
	}

}

float CTimer::getDelta()const
{
	return (float)mDeltaTime;
}


void CTimer::reset()
{
	__int64 currTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&currTime);

	mBaseTime = currTime;
	mPreviousTime = currTime;
	mStopTime = 0;
	mStopped = false;
}

void CTimer::start()
{
	__int64 startTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&startTime);

	if (mStopped)
	{
		mPausedTime += (startTime - mStopTime);

		mPreviousTime = startTime;
		mStopTime = 0;
		mStopped = false;
	}
}

void CTimer::stop()
{
	if (!mStopped)
	{
		__int64 currTime;
		QueryPerformanceCounter((LARGE_INTEGER*)&currTime);

		mStopTime = currTime;
		mStopped = true;
	}
}

void CTimer::tick()
{
	if (mStopped)
	{
		mDeltaTime = 0.0;
		return;
	}

	__int64 currTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&currTime);
	mCurrentTime = currTime;


	mDeltaTime = (mCurrentTime - mPreviousTime)*mSecondsPerCount;


	mPreviousTime = mCurrentTime;


	if (mDeltaTime < 0.0)
	{
		mDeltaTime = 0.0;
	}
}

//test test