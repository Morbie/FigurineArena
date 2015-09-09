#ifndef TIMER_H
#define TIMER_H
#pragma once

class CTimer
{
public:
	CTimer();
	~CTimer();

	float getTime()const;
	float getDelta()const;

	void reset();
	void start();
	void stop();
	void tick();

private:
	double mSecondsPerCount;
	double mDeltaTime;

	__int64 mBaseTime;
	__int64 mPausedTime;
	__int64 mStopTime;
	__int64 mPreviousTime;
	__int64 mCurrentTime;

	bool mStopped;
};

#endif