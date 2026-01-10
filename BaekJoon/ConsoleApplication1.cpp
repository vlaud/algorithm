#include <iostream>

using namespace std;
class SegTree
{
private:
	int* tree;
public:
	SegTree(int n);
	int init(int vect[], int l, int r, int node);
	int findSum(int vect[], int l, int r, int begin, int end, int node);
	void change(int vect[], int l, int r, int idx, int offset, int node);
};

SegTree::SegTree(int n)
{
	tree = new int[n * 4];
}

int SegTree::init(int vect[], int l, int r, int node)
{
	if (l == r) return tree[node] = vect[l];

	int mid = l + (r - l) / 2;
	return tree[node] = init(vect, l, mid, node * 2) + init(vect, mid + 1, r, node * 2 + 1);
}

int SegTree::findSum(int vect[], int l, int r, int begin, int end, int node)
{
	if (end < l || r < begin) return 0;
	if (begin <= l && r <= end) return tree[node];

	int mid = l + (r - l) / 2;
	return findSum(vect, l, mid, begin, end, node * 2) + findSum(vect, mid + 1, r, begin, end, node * 2 + 1);
}

void SegTree::change(int vect[], int l, int r, int idx, int offset, int node)
{
	if (idx < l || r < idx) return;
	tree[node] += offset;
	if (l == r) return;
	int mid = l + (r - l) / 2;
	change(vect, l, mid, idx, offset, node * 2);
	change(vect, mid + 1, r, idx, offset, node * 2 + 1);
}

int main()
{
	int vect[8] = { 1,2,3,4,5,6,7,8 };
	SegTree seg(8);
	seg.init(vect, 0, 7, 1);
	cout << seg.findSum(vect, 0, 7, 3, 6, 1) << endl;
	seg.change(vect, 0, 7, 4, 100, 1);
	cout << seg.findSum(vect, 0, 7, 3, 6, 1);
	return 0;
}