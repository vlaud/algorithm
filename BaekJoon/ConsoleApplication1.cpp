#include <iostream>

using namespace std;

#define mx 10000

class str
{
private:
	int size, max_size;
	char* words;
	void updateSize();
	int getsize(const char* string);

public:
	str();
	~str();

	void operator=(const char* string);
	void operator+=(const char* string);
	bool operator==(const char* string);
	char* wPtr();
	int getsize();
};

str::str()
{
	size = 0;
	max_size = mx;
	words = new char[max_size + 1];
}

str::~str()
{
	delete(words);
	words = nullptr;
}

void str::operator=(const char* string)
{
	size = getsize(string);
	updateSize();

	for (int i = 0; i < size; i++)
	{
		words[i] = string[i];
	}
}

void str::operator+=(const char* string)
{
	char* old = words;
	int oldsize = size;
	size += getsize(string);

	updateSize();

	for (int i = 0; i < oldsize; i++)
	{
		words[i] = old[i];
	}
	for (int i = oldsize; i < size; i++)
	{
		words[i] = string[i - oldsize];
	}
}

bool str::operator==(const char* string)
{
	if (size != getsize(string)) return false;

	for (int i = 0; i < size; i++)
	{
		if (words[i] != string[i]) return false;
	}

	return true;
}

void str::updateSize()
{
	if (size <= max_size) return;
	max_size = size;
	words = new char[max_size + 1];
}

char* str::wPtr()
{
	return words;
}

int str::getsize(const char* string)
{
	int tsize = 0;
	while (string[tsize] != '\0')
	{
		tsize++;
	}
	return tsize;
}

int str::getsize()
{
	return size;
}

ostream& operator<<(ostream& os, str& string)
{
	for (int i = 0; i < string.getsize(); i++)
	{
		os << string.wPtr()[i];
	}
	return os;
}

istream& operator>>(istream& is, str& string)
{
	char words[256] = {};
	is >> words;
	string = words;
	return is;
}

int main()
{
	str s;
	s = "amorcito";
	cout << s << "\n";

	s += "love";
	cout << s << "\n";

	s = "love";
	cout << s << "\n";

	s += "you";
	cout << s << "\n";

	cout << (s == "loveyou") << endl;
	cout << (s == "loveyo") << endl;
	cout << (s == "loveytt") << endl;

	cin >> s;
	cout << s << "\n";

	cin >> s;
	cout << s << "\n";
	return 0;
}