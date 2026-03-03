#include <iostream>

using namespace std;

#define mx 30
class Book
{
protected:
	char title[mx] = "";
	char writer[mx] = "";
public:
	Book(const char* title, const char* writer)
	{
		strcpy_s(this->title, title);
		strcpy_s(this->writer, writer);
	}
	virtual void Display()
	{
		printf("제목 : %s\n", title);
		printf("저자 : %s\n", writer);
	}
};

class EBook : public Book
{
private:
	double cap = 0.0;
public:
	EBook(const char* title, const char* writer, double cap) : Book(title, writer), cap(cap) {}
	void Display()
	{
		Book::Display();
		printf("파일 크기 : %.1lfmb\n\n", cap);
	}
};

class PaperBook : public Book
{
private:
	int pages = 0;
public:
	PaperBook(const char* title, const char* writer, int pages) : Book(title, writer), pages(pages) {}
	void Display()
	{
		Book::Display();
		printf("페이지 수 : %d 페이지\n", pages);
	}
};
int main()
{
	EBook eb("Clean Code", "Robert Martin", 5.2);
	PaperBook pb("Refactoring", "Martin Fowler", 450);
	Book* books[] = { &eb, &pb };
	for (int i = 0; i < 2; i++)
		books[i]->Display();
	return 0;
}