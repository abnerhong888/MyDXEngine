#include "MyTimer.h"



MyTimer::MyTimer() : mPCFreq(0.0)
{
	LARGE_INTEGER l_li;
	QueryPerformanceFrequency(&l_li);
	mPCFreq = double(l_li.QuadPart) / 1000.0;
}

MyTimer &MyTimer::GetIns()
{
	static MyTimer l_ins;
	return l_ins;
}

void MyTimer::TimerStart()
{
	QueryPerformanceCounter(&mstart);
}

void MyTimer::TimerEnd()
{
	QueryPerformanceCounter(&mend);
	mMS = ((mend.QuadPart - mstart.QuadPart) / mPCFreq);
}

double MyTimer::Getms()
{
	return mMS;
}

double MyTimer::GetHz()
{
	return (1 / (mMS / 1000));
}