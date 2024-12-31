#ifndef __MYTIMER_H__
#define __MYTIMER_H__

#include "windows.h"

class MyTimer
{
public:
	MyTimer();
	static MyTimer &GetIns();
	void TimerStart();
	void TimerEnd();
	double Getms();
	double GetHz();
protected:
private:
	double mPCFreq;
	double mMS;
	LARGE_INTEGER mstart, mend;
};

#endif