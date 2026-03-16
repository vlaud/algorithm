#include <iostream>
#include <unordered_set>

using namespace std;

class ITest
{
public:
	virtual void test() = 0;
};

class IComponent
{
public:
	virtual void Execute() = 0;
};

class Test : public IComponent, public ITest
{
public:
	void Execute() override
	{
		test();
	}

	void test() override
	{
		cout << "테스트" << endl;
	}

};
class ICamera
{
public:
	virtual void Rotate() = 0;
};

class Camera : public IComponent, public ICamera
{
public:
	Camera() {}
	void Rotate() override
	{
		cout << "돌기" << endl;
	}
	void Execute() override
	{
		Rotate();
	}
};

class GameObeject : public IComponent
{
public:
	GameObeject() : cam(nullptr), _components(), camObject(nullptr)
	{
		
	}

	void Execute() override
	{
		for (auto& comp : _components)
		{
			comp->Execute();
		}
	}

	void AddCamera(IComponent* component)
	{
		if (ICamera* cm = dynamic_cast<ICamera*>(component))
		{
			camObject = component;
			cam = cm;
		}
	}

	void AddComponent(IComponent* component)
	{
		if (_components.find(component) != _components.end())
		{
			cout << "이미 있음" << endl;
			return;
		}

		_components.insert(component);
	}

	template<class T>
	T* GetComponent()
	{
		for (auto& comp : _components)
		{
			if (T* type = dynamic_cast<T*>(comp))
			{
				return type;
			}
		}

		cout << "해당 컴포넌트 없음" << endl;
		return nullptr;
	}

	void Rotate()
	{
		if (!cam)
		{
			cout << "카메라 없음" << endl;
			return;
		}
		cam->Rotate();
	}

private:
	unordered_set<IComponent*> _components;
	ICamera* cam;
	IComponent* camObject;
};

int main()
{
	GameObeject* player = new GameObeject();
	player->Rotate();
	player->Execute();

	Test* test = new Test();
	player->AddComponent(test);
	player->Execute();

	Test* test1 = new Test();
	player->AddComponent(test);
	player->Execute();

	Camera* cam = new Camera();
	player->AddComponent(cam);
	player->Execute();
	player->AddCamera(cam);

	player->Rotate();
	player->GetComponent<ITest>()->test();
	player->GetComponent<ICamera>()->Rotate();
	player->GetComponent<Camera>()->Rotate();

	// player->GetComponent<T>가 nullptr이면 에러
	return 0;
}