#include <iostream>

enum class eColor
{
	Red,
	Black,
	End,
};

struct Node
{
	int data;
	eColor Color;

	Node* left;
	Node* right;
	Node* parent;

	Node(int data)
		: data(data)
		, Color(eColor::Red)
		, left(nullptr)
		, right(nullptr)
		, parent(nullptr)
	{}
};

class RedBlackTree
{
public:
	RedBlackTree()
	{
		NIL = new Node(0);
		NIL->Color = eColor::Black;
		mRoot = NIL;
	}

	void LeftRotate(Node* x)
	{
		Node* y = x->right;

		// 1단계: y의 왼쪽 서브트리 -> x의 오른쪽 이동
		x->right = y->left;
		if (y->left != NIL) // 자식이 빈 노드가 아니면 부모를 x로 변환
		{
			y->left->parent = x;
		}

		// 2단계: y의 부모를 x의 부모로 설정
		y->parent = x->parent;
		if (x->parent == NIL)
		{
			mRoot = y;
		}
		else if (x == x->parent->left)
		{
			x->parent->left = y;
		}
		else
		{
			x->parent->right = y;
		}

		// 3단계: x를 y의 왼쪽 자식으로 설정
		y->left = x;
		x->parent = y;
	}

	void RightRotate(Node* y)
	{
		Node* x = y->left;

		y->left = x->right;
		if (x->right != NIL)
		{
			x->right->parent = y;
		}

		x->parent = y->parent;
		if (y->parent == NIL)
		{
			mRoot = x;
		}
		else if (y == y->parent->left)
		{
			y->parent->left = x;
		}
		else
		{
			y->parent->right = x;
		}

		x->right = y;
		y->parent = x;
	}

	void insert(int data)
	{
		Node* newNode = new Node(data);
		newNode->left = NIL;
		newNode->right = NIL;

		Node* y = NIL;
		Node* x = mRoot;

		// 새로운 노드 삽입 위치 찾기
		// 재귀로 대체 가능

		while (x != NIL)
		{
			y = x;
			if (newNode->data < x->data)
			{
				x = x->left;
			}
			else
			{
				x = x->right;
			}
		}

		newNode->parent = y;

		if (y == NIL)
		{
			mRoot = newNode;
		}
		else if (newNode->data < y->data)
		{
			y->left = newNode;
		}
		else
		{
			y->right = newNode;
		}
		newNode->Color = eColor::Red;
		InsertFixup(newNode);
	}

	void fixInsert(Node* z)
	{
		while (z->parent->Color == eColor::Red)
		{
			Node* g = z->parent->parent;
			Node* u = z->parent == g->right ? g->left : g->right;

			// recoloring
			if (u->Color == eColor::Red)
			{
				z->parent->Color = eColor::Black;
				u->Color = eColor::Black;
				g->Color = eColor::Red;
				z = g;
				continue;
			}

			// restructuring
			if (z->parent == g->left)
			{
				// 부모, 삼촌 가운데 껴있음
				if (z == z->parent->right)
				{
					z = z->parent;
					LeftRotate(z);
				}
				z->parent->Color = eColor::Black;
				g->Color = eColor::Red;
				RightRotate(g);
			}
			else
			{
				if (z == z->parent->left)
				{
					z = z->parent;
					RightRotate(z);
				}
				z->parent->Color = eColor::Black;
				g->Color = eColor::Red;
				LeftRotate(g);
			}
		}
		mRoot->Color = eColor::Black;
	}

	void InsertFixup(Node* z)
	{
		while (z->parent->Color == eColor::Red)
		{
			Node* grand = z->parent->parent;
			if (z->parent == grand->left)
			{
				Node* uncle = grand->right; // 삼촌 노드
				if (uncle->Color == eColor::Red) // 삼촌 빨간색
				{
					z->parent->Color = eColor::Black; // recoloring
					uncle->Color = eColor::Black;
					grand->Color = eColor::Red;
					z = grand;
				}
				else // 삼촌 검은색
				{
					// restructuring
					if (z == z->parent->right) // 삼촌 검은색, z 오른쪽 자식
					{
						z = z->parent;
						LeftRotate(z);
					}
					// 삼촌 검은색, z 왼쪽 자식
					z->parent->Color = eColor::Black;
					grand->Color = eColor::Red;
					RightRotate(grand);
				}
			}
			else
			{
				Node* uncle = grand->left;
				if (uncle->Color == eColor::Red)
				{
					z->parent->Color = eColor::Black;
					uncle->Color = eColor::Black;
					grand->Color = eColor::Red;
					z = grand;
				}
				else
				{
					if (z == z->parent->left)
					{
						z = z->parent;
						RightRotate(z);
					}
					z->parent->Color = eColor::Black;
					grand->Color = eColor::Red;
					LeftRotate(grand);
				}
			}
		}
		mRoot->Color = eColor::Black;
	}
private:
	Node* mRoot;
	Node* NIL;
};