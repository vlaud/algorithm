#include "time.h"
#include <iostream>

Time::Time(int hour, int minute, int second) : hour_(hour), minute_(minute), second_(second)
{

}

Time Time::operator+(Time target)
{
	int totalSecond = second_ + target.GetSecond();
	int second = totalSecond % 60;
	int tempMin = totalSecond / 60;

	int totalMinute = minute_ + target.GetMinute() + tempMin;
	int minute = totalMinute % 60;
	int tempHour = totalMinute / 60;

	int hour = hour_ + target.GetHour() + tempHour;

	Time newTime(hour, minute, second);
	return newTime;
}

int Time::GetHour()
{
	return hour_;
}
int Time::GetSecond()
{
	return second_;
}
int Time::GetMinute()
{
	return minute_;
}

void Time::Print()
{
	printf("%dΩ√ %d∫– %d√ \n", hour_, minute_, second_);
}