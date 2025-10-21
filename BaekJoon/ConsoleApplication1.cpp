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

template<typename T>
struct Node {
	T val;
	Node* next;

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

int func1(int N) {
	int sum = 0;
	int a = N / 3;
	sum += 3 * a * (a + 1) / 2;

	a = N / 5;
	sum += 5 * a * (a + 1) / 2;

	a = N / 15;
	sum -= 15 * a * (a + 1) / 2;
	return sum;
}

int func2(int arr[], int N) {
	bool mp[101] = { false };

	for (int i = 0; i < N; i++) {
		if (mp[arr[i]]) return 1;
		mp[100 - arr[i]] = true;
	}

	return 0;
}

int func3(int N) {
	if (N == 1) return 1;
	int l = 1, r = N / 2;

	while (l <= r) {
		long long mid = l + (r - l) / 2;

		if (mid * mid == N) return 1;
		else if (mid * mid < N) l = mid + 1;
		else r = mid - 1;
	}
	return 0;
}

int func4(int N) {
	int a = 1;

	while (a * 2 <= N) {
		a *= 2;
	}
	return a;
}

void test1() {
	cout << "****** func1 test ******\n";
	int n[3] = { 16, 34567, 27639 };
	int ans[3] = { 60, 278812814, 178254968 };
	for (int i = 0; i < 3; i++) {
		int result = func1(n[i]);
		cout << "TC #" << i << '\n';
		cout << "expected : " << ans[i] << " result : " << result;
		if (ans[i] == result) cout << " ... Correct!\n";
		else cout << " ... Wrong!\n";
	}
	cout << "*************************\n\n";
}

void test2() {
	cout << "****** func2 test ******\n";
	int arr[3][4] = { {1,52,48}, {50,42}, {4,13,63,87} };
	int n[3] = { 3, 2, 4 };
	int ans[3] = { 1, 0, 1 };
	for (int i = 0; i < 3; i++) {
		int result = func2(arr[i], n[i]);
		cout << "TC #" << i << '\n';
		cout << "expected : " << ans[i] << " result : " << result;
		if (ans[i] == result) cout << " ... Correct!\n";
		else cout << " ... Wrong!\n";
	}
	cout << "*************************\n\n";
}

void test3() {
	cout << "****** func3 test ******\n";
	int n[3] = { 9, 693953651, 756580036 };
	int ans[3] = { 1, 0, 1 };
	for (int i = 0; i < 3; i++) {
		int result = func3(n[i]);
		cout << "TC #" << i << '\n';
		cout << "expected : " << ans[i] << " result : " << result;
		if (ans[i] == result) cout << " ... Correct!\n";
		else cout << " ... Wrong!\n";
	}
	cout << "*************************\n\n";
}

void test4() {
	cout << "****** func4 test ******\n";
	int n[3] = { 5, 97615282, 1024 };
	int ans[3] = { 4, 67108864, 1024 };
	for (int i = 0; i < 3; i++) {
		int result = func4(n[i]);
		cout << "TC #" << i << '\n';
		cout << "expected : " << ans[i] << " result : " << result;
		if (ans[i] == result) cout << " ... Correct!\n";
		else cout << " ... Wrong!\n";
	}
	cout << "*************************\n\n";
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	test1();
	test2();
	test3();
	test4();

	//vector<int> arr = { 4,5,6,7,2,3,1};
	//quickSort(arr, 0, arr.size()-1);

	//int k = 3; // 3번째 작은 수 (즉, index 2)
	//int result = partition(arr, 0, arr.size() - 1);
	//cout << result << endl;
	//for (int it : arr) cout << it << ' ';
	//cout << endl;

	//LinkedList<int> list;
	//list.push_back(2);
	//list.push_back(3);
	//list.push_back(5);
	//list.push_back(8);
	//list.print();
	//cout << "List size: " << list.size() << endl;

	//list.find(2);
	//list.insert_at(2, 4);
	//list.print();
	//list.contains(4);
	//list.contains(6);
	//list.erase_at(2);
	//list.print();

	//for (int i = 0; i < 5; i++) {
	//	for (int j = 0; j <= i; j++) {
	//		cout << "*";
	//	}
	//	cout << endl;
	//}

	//int n = 5;
	//for (int i = 0; i < n; i++) {
	//	for (int j = 0; j < i+n; j++) {
	//		if (j < n - i - 1 || (i % 2) != (j % 2)) cout << " ";
	//		else cout << "*";
	//	}
	//	if (i < 4) cout << endl;
	//}

	//cout << pow(3, 7) << endl;

	return 0;
}