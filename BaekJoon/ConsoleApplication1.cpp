#include <iostream>

using namespace std;

#define mx 30

namespace Dong
{
	template<typename T>
	class list // 이중 원형 리스트
	{
	public:
		struct Node
		{
			T val;
			Node* next, * prev;
			Node() : val(0), next(this), prev(this) {}
			Node(T val) :val(val), next(this), prev(this) {}
		};

		class iterator
		{
		public:
			iterator() : node(nullptr), head(nullptr), idx(0) {}
			iterator(Node* iter, Node* head, int idx) : node(iter), head(head), idx(idx) {}

			~iterator()
			{
				node = nullptr;
			}

			bool operator==(const iterator& other) const
			{
				return node == other.node;
			}

			/// <summary>
			/// 기본 우측 이동
			/// </summary>
			void baseUp()
			{
				node = node->next;
				idx++;
			}

			/// <summary>
			/// 기본 좌측 이동
			/// </summary>
			void baseDown()
			{
				node = node->prev;
				idx--;
			}

			void reset()
			{
				node = head->next;
			}

			void operator++() // ++iter
			{
				baseUp();
			}

			void operator++(int) // iter++
			{
				baseUp();
			}

			void operator--()
			{
				baseDown();
			}

			void operator--(int)
			{
				baseDown();
			}

			T operator*() const
			{
				if (!node) return (T)0;
				return node->val;
			}

			int index() const { return idx; }
			Node* Ptr() const { return node; }
		private:
			Node* node, * head;
			int idx;
		};

		list() : head(new Node())
		{
			iterator it(head, head, 0);
			b = e = it;
		}

		~list()
		{
			while (head->next != head) pop_front();

			head->next = nullptr;
			head->prev = nullptr;
			delete head;
			head = nullptr;
		}

		bool empty()
		{
			return head->next == head;
		}

		void insert(Node* prev, Node* node)
		{
			node->prev = prev;
			node->next = prev->next;

			if (node->next) node->next->prev = node;
			prev->next = node;

			b.reset();
		}

		void push_front(T val)
		{
			insert(head, new Node(val));
		}

		void push_back(T val)
		{
			insert(head->prev, new Node(val));
		}

		void remove(Node* node)
		{
			if (empty() || node == head) return;

			node->prev->next = node->next;
			node->next->prev = node->prev;
			delete node;

			b.reset();
		}

		void pop_front()
		{
			if (empty()) return;

			remove(head->next);
		}

		void pop_back()
		{
			if (empty()) return;

			remove(head->prev);
		}

		iterator erase(iterator& iter)
		{
			if (iter.Ptr() == head) return iter;
			iterator newIter(iter.Ptr()->next, head, iter.index());
			remove(iter.Ptr());
			return newIter;
		}

		iterator begin()
		{
			return b;
		}

		iterator end()
		{
			return e;
		}

		void printAll()
		{
			Node* cur = head->next;

			while (cur != head)
			{
				cout << cur->val;
				cur = cur->next;
			}
			cout << endl;
		}
	private:
		Node* head;
		iterator b, e;
	};
}

void CMD(char& c, Dong::list<char>& li, Dong::list<char>::iterator& iter)
{
	if (c == 'L')
	{
		if (iter == li.begin()) return;
		iter--;
	}
	else if (c == 'R')
	{
		if (iter == li.end()) return;
		iter++;
	}
	else
	{
		// 커서 앞 부분을 지움
		iter = li.erase(iter);
	}
}

int main()
{
	Dong::list<char> li;

	for (char c = 'a'; c <= 'z'; c++)
	{
		li.push_front(c);
	}

	li.pop_front();

	cout << *li.begin();

	while (!li.empty()) li.pop_front();
	li.push_back('a');
	cout << *li.begin();
	return 0;
}
