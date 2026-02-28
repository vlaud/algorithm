#include <iostream>
#include <string>

using namespace std;

class Text
{
public:
	static const char *dictMessage[];
};

const char *Text::dictMessage[] =
{
	"doesn't exist.", "exists."
};

class Trie
{
private:
	Trie *children[26] = {};
	bool isEnd = false;

public:
	Trie() {};
	Trie *GetPrefix(string word, bool make);
	void insert(string word);
	bool isWord(string word);
	bool isPrefix(string word, bool isWord);
};

Trie *Trie::GetPrefix(string word, bool make = false)
{
	Trie *cur = this;
	for (char &c : word)
	{
		c = tolower(c);
		c -= 'a';
		if (cur->children[c] == nullptr)
		{
			if (make)
			{
				cur->children[c] = new Trie();
			}
			else
			{
				return nullptr;
			}
		}
		cur = cur->children[c];
	}
	return cur;
}

void Trie::insert(string word)
{
	Trie *cur = GetPrefix(word, true);
	cur->isEnd = true;
}

bool Trie::isPrefix(string word, bool isWord = false)
{
	Trie *cur = GetPrefix(word);
	if (cur == nullptr)
		return false;
	return isWord ? cur->isEnd : true;
}

bool Trie::isWord(string word)
{
	return isPrefix(word, true);
}

int main()
{
	Trie *trie = new Trie();
	int loop = 1;
	string input;
	while (loop)
	{
		printf("insert word: ");
		cin >> input;
		trie->insert(input);
		printf("search word: ");
		cin >> input;
		printf("The word \"%s\" %s\n\n", input.c_str(), Text::dictMessage[trie->isWord(input)]);
		printf("search prefix: ");
		cin >> input;
		printf("The prefix \"%s\" %s\n\n", input.c_str(), Text::dictMessage[trie->isPrefix(input)]);
		printf("Continue? ");
		cin >> loop;
	}
	return 0;
}