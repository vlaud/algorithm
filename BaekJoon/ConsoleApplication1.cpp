#include <iostream>

using namespace std;

class Vehicle
{
public:
	virtual void StartEngine() = 0;
	virtual void Drive() = 0;
	virtual void StopEngine() = 0;
};

class Car : public Vehicle
{
public:
	void StartEngine()
	{
		printf("자동차 엔진 시동!\n");
	}
	void Drive()
	{
		printf("부릉 부릉~!\n");
	}
	void StopEngine()
	{
		printf("자동차가 멈췄다\n\n");
	}
};
class Motorcycle : public Vehicle
{
public:
	void StartEngine()
	{
		printf("오토바이 엔진 시동!\n");
	}
	void Drive()
	{
		printf("부와앙~!\n");
	}
	void StopEngine()
	{
		// 원시 문자열 리터럴
		cout << R"(!@#@!#!%#@&)" << endl;
		printf("오토바이가 멈췄다\n\n");
	}
};


int main()
{
	Car c; Motorcycle m;
	Vehicle* vehicles[] = { &c, &m };
	for (int i = 0; i < 2; i++)
	{
		vehicles[i]->StartEngine();
		vehicles[i]->Drive();
		vehicles[i]->StopEngine();
	}
	return 0;
}