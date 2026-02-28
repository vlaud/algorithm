#pragma once

class Time
{
private:
	int hour_;
	int minute_;
	int second_;
public:
	Time(int hour, int minute, int second);
	Time operator+(Time target);
	int GetHour();
	int GetSecond();
	int GetMinute();
	void Print();
};