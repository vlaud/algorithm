#include <iostream>
using namespace std;

#define endl '\n'
#define mx 1000005

template<typename T>
class Heap {
private:
	T* arr;
	int size = 0;
public:
	Heap();
	~Heap();
	void push(T val);
	T top();
	int getSize();
	void pop();
};
template<typename T>
Heap<T>::Heap() {
	arr = new T[mx];
}
template<typename T>
Heap<T>::~Heap() {
	delete[] arr;
	arr = nullptr;
}
template<typename T>
void Heap<T>::push(T val) {
	int i = ++size;

	// 최소 힙
	while (i != 1 && arr[i / 2] > val) {
		arr[i] = arr[i / 2];
		i /= 2;
	}
	arr[i] = val;
}
template<typename T>
T Heap<T>::top() {
	return arr[1];
}
template<typename T>
int Heap<T>::getSize() {
	return size;
}
template<typename T>
void Heap<T>::pop() {
	if (!size) return;

	T temp = arr[size--];
	int p = 1, c = 2;

	while (c <= size) {
		if (c < size && arr[c] > arr[c + 1]) c++;
		if (temp <= arr[c]) break;
		arr[p] = arr[c];
		p = c;
		c *= 2;
	}
	arr[p] = temp;
}


int main() {
	Heap<int> iheap;
	cout << iheap.getSize() << endl;
	iheap.push(3);
	cout << iheap.top() << endl;
	iheap.push(10);
	cout << iheap.top() << endl;
	iheap.push(2);
	cout << iheap.top() << endl;
	iheap.push(11);
	cout << iheap.top() << endl;
	iheap.pop();
	cout << iheap.top() << endl;
	return 0;
}