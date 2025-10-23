#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <queue>
#include <sstream>

using namespace std;

struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

/// <summary>
/// 정석 연결리스트
/// </summary>
/// <typeparam name="T"></typeparam>
template<typename T>
struct Node {
	Node *prev, *next;
	T val;

	Node(const T& x) : val(x), next(nullptr) {}
};

template<typename T>
class LinkedList {
private:
	Node<T>* head;
	int list_size = 0;
public:
	LinkedList() : head(nullptr) {}
	~LinkedList();

	int size() const { return list_size; }
	void push_front(const T& val);
	void pop_front();
	void push_back(const T& val);
	void pop_back();
	void insert_after(Node<T>* prev, const T& val);
	void erase_after(Node<T>* prev);
	void insert_at(int idx, const T& val);
	void erase_at(int idx);
	Node<T>* find(int idx) const;
	bool contains(const T& val) const;
	void reverse();
	bool empty() const;
	void print() const;
	void clear() { while (head) pop_front(); }
	vector<T> to_vector() const;
	T* to_array(int& size) const;
};

template<typename T>
void LinkedList<T>::push_front(const T& val) {
	Node<T>* newNode = new Node<T>(val);
	newNode->next = head;
	head = newNode;
	list_size++;
	cout << "push_front " << val << endl;
}

template<typename T>
void LinkedList<T>::pop_front() {
	if (!head) return;
	Node<T>* old = head;
	head = head->next;
	cout << "pop_front " << old->val << endl;
	delete old;
	list_size--;
}

template<typename T>
void LinkedList<T>::push_back(const T& val)
{
	Node<T>* newNode = new Node<T>(val);
	if (!head) head = newNode;
	else {
		Node<T>* cur = head;
		while (cur->next) cur = cur->next;
		cur->next = newNode;
	}
	list_size++;
	cout << "push_back " << val << endl;
}

template<typename T>
void LinkedList<T>::pop_back()
{
	if (!head) return;
	if (!head->next) {
		cout << "delete " << head->val << " ";
		delete head;
		head = nullptr;
		list_size--;
		return;
	}
	Node<T>* cur = head;
	while (cur->next->next) cur = cur->next;
	cout << "delete " << cur->next->val << " ";
	delete cur->next;
	cur->next = nullptr;
	list_size--;
}

template<typename T>
void LinkedList<T>::insert_after(Node<T>* prev, const T& val)
{
	if (!prev) return;

	Node<T>* newNode = new Node<T>(val);
	newNode->next = prev->next;
	prev->next = newNode;
	list_size++;
}

template<typename T>
void LinkedList<T>::erase_after(Node<T>* prev)
{
	if (!prev || !prev->next) return;

	Node<T>* target = prev->next;
	prev->next = target->next;
	delete target;
	list_size--;
}

template<typename T>
void LinkedList<T>::insert_at(int idx, const T& val)
{
	if (idx < 0 || idx > list_size) return; // Invalid index
	if (idx == 0) push_front(val);
	else {
		Node<T>* prev = find(idx - 1);
		insert_after(prev, val);
	}
	list_size++;
	cout << "insert_at " << idx << " " << val << endl;
}

template<typename T>
void LinkedList<T>::erase_at(int idx)
{
	if (idx < 0 || idx >= list_size) return; // Invalid index
	if (idx == 0) pop_front();
	else {
		Node<T>* prev = find(idx - 1);
		erase_after(prev);
	}
	list_size--;
	cout << "erase_at " << idx << endl;
}

template<typename T>
Node<T>* LinkedList<T>::find(int idx) const
{
	if (idx < 0 || idx >= list_size) return nullptr;
	Node<T>* cur = head;
	int i = 0;
	while (cur && i < idx) {
		cur = cur->next;
		i++;
	}
	cout << "find idx: " << idx << ", element: " << (cur ? cur->val : -1) << endl;
	return cur;
}

template<typename T>
bool LinkedList<T>::contains(const T& val) const
{
	Node<T>* cur = head;
	while (cur) {
		if (cur->val == val) {
			cout << "contains " << val << ": true" << endl;
			return true;
		}
		cur = cur->next;
	}
	cout << "contains " << val << ": false" << endl;
	return false;
}

template<typename T>
void LinkedList<T>::reverse()
{
	Node<T>* prev = nullptr, * cur = head, * next = nullptr;
	while (cur) {
		next = cur->next;
		cur->next = prev;
		prev = cur;
		cur = next;
	}
	head = prev;
}

template<typename T>
bool LinkedList<T>::empty() const {
	cout << boolalpha << (!head) << endl;
	return !head;
}

template<typename T>
void LinkedList<T>::print() const {
	if (!head) return;
	Node<T>* cur = head;
	while (cur) {
		cout << cur->val;
		cur = cur->next;
		if (cur) cout << "->";
	}
	cout << endl;
}
template<typename T>
vector<T> LinkedList<T>::to_vector() const
{
	vector<T> v;
	Node<T>* cur = head;
	while (cur) {
		v.push_back(cur->val);
		cur = cur->next;
	}
	return v;
}
template<typename T>
T* LinkedList<T>::to_array(int& out_size) const
{
	int n = list_size;
	out_size = n;
	T* arr = new T[n];
	Node<T>* cur = head;
	for (int i = 0; i < n; i++) {
		arr[i] = cur->val;
		cur = cur->next;
	}
	return arr;
}
template<typename T>
LinkedList<T>::~LinkedList() {
	while (head) pop_front();
}

class Codec {
public:

	// Encodes a tree to a single string.
	string serialize(TreeNode* root) {
		string s;
		serialize(root, s);
		return s;
	}
	void serialize(TreeNode* root, string& s) {
		if (!root) {
			s += "#|";
			return;
		}
		s += to_string(root->val) + "|";
		serialize(root->left, s);
		serialize(root->right, s);
	}

	// Decodes your encoded data to tree.
	TreeNode* deserialize(string data) {
		stringstream in(data);
		return deserialize(in);
	}
	TreeNode* deserialize(stringstream& in) {
		string s;
		getline(in, s, '|');
		if (s == "#") return nullptr;
		TreeNode* node = new TreeNode(stoi(s));
		node->left = deserialize(in);
		node->right = deserialize(in);
		return node;
	}
};

int partition(vector<int>& nums, int l, int r) {
	int pivot = nums[l];
	while (true) {
		while (nums[l] < pivot) l++;
		while (nums[r] > pivot) r--;

		if (l >= r) break;
		swap(nums[l++], nums[r--]);
	}

	return r;
}
int quickSelect(vector<int>& arr, int low, int high, int k) {
	if (low >= high) return -1;

	int pi = partition(arr, low, high);

	if (pi == k) return arr[pi];
	else if (k < pi) return quickSelect(arr, low, pi, k);
	else return quickSelect(arr, pi + 1, high, k);
}

void quickSort(vector<int>& arr, int low, int high) {
	if (low >= high) return;
	/* pi is partitioning index, arr[pi] is now
		   at right place */
	int pi = partition(arr, low, high);
	// Separately sort elements before 
	// partition and after partition
	quickSort(arr, low, pi);
	quickSort(arr, pi + 1, high);
}

// 야매 연결 리스트
const int MX = 1000005;
// dat[i]: i번지 원소의 값, pre[i]: 이전 원소 인덱스, nxt[i]: 다음 원소 인덱스
// pre, nxt의 값이 -1 => 존재하지 않음
int dat[MX], pre[MX], nxt[MX];
// unused: 현재 사용되지 않는 인덱스, 원소 추가시 1씩 증가
// 0번지는 연결 리스트 시작 원소로 고정, 즉 dummy node
int unused = 1;
int tail = 0;
void insert(int addr, int num) {
	dat[unused] = num;
	pre[unused] = addr;
	nxt[unused] = nxt[addr];
	
	nxt[addr] = unused;
	if (nxt[unused] != -1) pre[nxt[unused]] = unused;
	else tail = unused;

	unused++;
}

void erase(int addr) {
	nxt[pre[addr]] = nxt[addr];
	if (nxt[addr] != -1) pre[nxt[addr]] = pre[addr];
	else tail = pre[addr];
}

void traverse() {
	int cur = nxt[0];
	while (cur != -1) {
		cout << dat[cur] << ' ';
		cur = nxt[cur];
	}
	cout << "\n" << dat[tail];
	cout << "\n\n";
}

void insert_test() {
	cout << "****** insert_test *****\n";
	insert(0, 10); // 10(address=1)
	traverse();
	insert(0, 30); // 30(address=2) 10
	traverse();
	insert(2, 40); // 30 40(address=3) 10
	traverse();
	insert(1, 20); // 30 40 10 20(address=4)
	traverse();
	insert(4, 70); // 30 40 10 20 70(address=5)
	traverse();
}

void erase_test() {
	cout << "****** erase_test *****\n";
	erase(1); // 30 40 20 70
	traverse();
	erase(2); // 40 20 70
	traverse();
	erase(4); // 40 70
	traverse();
	erase(5); // 40
	traverse();
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	// 야매 연결 리스트
	fill(pre, pre + MX, -1);
	fill(nxt, nxt + MX, -1);
	insert_test();
	erase_test();

	//vector<int> arr = { 4,5,6,7,2,3,1};
	////quickSort(arr, 0, arr.size()-1);

	//int k = 3; // 3번째 작은 수 (즉, index 2)
	//int result = partition(arr, 0, arr.size() - 1);
	//cout << result << endl;
	//for (int it : arr) cout << it << ' ';
	//cout << endl;

	/*LinkedList<int> list;
	list.push_back(2);
	list.push_back(3);
	list.push_back(5);
	list.push_back(8);
	list.print();
	cout << "List size: " << list.size() << endl;

	list.find(2);
	list.insert_at(2, 4);
	list.print();
	list.contains(4);
	list.contains(6);
	list.erase_at(2);
	list.print();*/

	/*for (int i = 0; i < 5; i++) {
		for (int j = 0; j <= i; j++) {
			cout << "*";
		}
		cout << endl;
	}

	int n = 5;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < i+n; j++) {
			if (j < n - i - 1 || (i % 2) != (j % 2)) cout << " ";
			else cout << "*";
		}
		if (i < 4) cout << endl;
	}

	cout << pow(3, 7) << endl;*/

	return 0;
}