#include <iostream>

using namespace std;

void tt()
{
	int** test = new int* [3];

	for (int i = 0; i < 3; i++)
	{
		test[i] = new int[3];
	}


	for (int i = 0; i < 3; i++)
	{
		delete[] test[i];
	}
	delete[] test;
}

int main()
{
	tt();
	return 0;
}