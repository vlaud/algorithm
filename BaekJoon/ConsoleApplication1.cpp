#include <iostream>

using namespace std;

#define mx 20

class Text
{
public:
	static void SetText(char* var, const char* txt)
	{
		for (int i = 0; i < mx; i++)
		{
			var[i] = txt[i];
			if (var[i] == '\0') break;
		}
	}
};
class Animal
{
protected:
	char name[mx] = "";
public:
	Animal(const char* name)
	{
		Text::SetText(this->name, name);
	}
	virtual void Speak() = 0;
};

class Dog : public Animal
{
public:
	Dog(const char* name);
	void Speak() override
	{
		cout << "barks!" << endl;
	}
};

/// <summary>
/// 부모의 생성자 오버라이딩
/// </summary>
/// <param name="name"></param>
Dog::Dog(const char* name) : Animal(name) {}

class Cat : public Animal
{
public:
	Cat(const char* name);
	void Speak() override
	{
		cout << "meows!" << endl;
	}
};

Cat::Cat(const char* name) : Animal(name) {}

int main()
{
	Dog d1("Baekgu"); Cat c1("Nabi");
	Animal* animals[] = { &d1, &c1 };
	for (int i = 0; i < 2; i++)
	{
		animals[i]->Speak();
	}
	return 0;
}