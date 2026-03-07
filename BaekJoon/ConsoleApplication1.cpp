#include <iostream>

using namespace std;

class Component
{
public:
	virtual void Display() = 0;
	virtual ~Component() {}
};

class Transform : public Component
{
private:
	string name;
public:
	Transform(string n) : name(n) {}

	void Display() override
	{
		cout << "Transform: " << name << endl;
	}
};

class Renderer : public Component
{
private:
	string name;
public:
	Renderer(string n) : name(n) {}

	void Display() override
	{
		cout << "Renderer: " << name << endl;
	}
};

class GameObject : public Component
{
private:
	string name;
	Component* components[10];
	int childCount;
public:
	GameObject(string n) : name(n), childCount(0), components() {}

	void Add(Component* c)
	{
		components[childCount++] = c;
	}

	void Display() override
	{
		cout << "Composite: " << name << endl;

		// 모든 자식 Display()
		for (int i = 0; i < childCount; ++i)
		{
			components[i]->Display();
		}
	}
};

int main()
{
	Transform file1("file1.txt");
	Transform file2("file2.txt");

	GameObject folder1("forder1");
	folder1.Add(&file1);
	folder1.Add(&file2);

	Transform file3("file3.txt");
	GameObject rootFolder("Root");
	rootFolder.Add(&folder1);
	rootFolder.Add(&file3);

	rootFolder.Display();
	return 0;
}