#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <string>
#include <typeinfo>

using namespace std;

#define endl '\n'

int main()
{
	int arr[2][3] = { {1,2,3},
					  {4,5,6}, };

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 3; j++) {
			printf("%d ", arr[i][j]);
		}
		cout << endl;
	}
	int (*pt)[3] = arr;
	int att[2] = { 1,3 };
	int* p = att;
	int* pthh[3] = { new int[2]{1,5}, new int[3]{4,5,5}, new int[2]{2,6} };
	cout << endl;

	printf("pt[0][2] = %d\n", pt[0][2]);
	printf("typeid(arr) = %s\n", typeid(arr).name());
	printf("typeid(&arr[0]) = %s\n", typeid(&arr[0]).name());
	printf("typeid(*arr) = %s\n", typeid(*arr).name());
	printf("typeid(arr[0]) = %s\n", typeid(arr[0]).name());
	printf("typeid(&arr[0][0]) = %s\n", typeid(&arr[0][0]).name());
	printf("typeid(**arr) = %s\n", typeid(**arr).name());
	printf("typeid(*arr[0]) = %s\n", typeid(*arr[0]).name());
	printf("typeid(att) = %s\n", typeid(att).name());
	printf("typeid(p) = %s\n", typeid(p).name());
	printf("typeid(pthh) = %s\n", typeid(pthh).name());
	printf("typeid(pthh[0][1]) = %s\n", typeid(pthh[0][1]).name());
	printf("typeid(&pthh[0][1]) = %s\n", typeid(&pthh[0][1]).name());
	printf("pthh[0][1] = %d\n", pthh[0][1]);

	cout << endl;
	cout << "[] == *" << endl;
	cout << "배열은 포인터다" << endl;
	cout << endl;
	const char* str[3] = {"df", "ee", "gwegwe"};
	const char **ptt = str;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < str[i][j]; j++) {
			cout << str[i][j];
		}
		cout << endl;
	}

	cout << endl;
	cout << "이중 포인터" << endl;
	printf("typeid(str) = %s\n", typeid(str).name());
	printf("typeid(str[0]) = %s\n", typeid(str[0]).name());
	printf("typeid(&str[0]) = %s\n", typeid(&str[0]).name());
	printf("typeid(ptt) = %s\n", typeid(ptt).name());
	
	printf("ptt[0] = %s\n", ptt[0]);

	return 0;
}