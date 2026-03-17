#include <iostream>
#include <print>


/* 변수 템플릿 */
template<typename T>
constexpr T pi = T(3.1415926535897932385L);

/* 명시적 특수화 */
template<typename T>
void Swap(T& a, T& b)
{
	T temp = a;
	a = b;
	b = temp;
}

template<>
void Swap<double>(double& a, double& b)
{
	std::cout << "double은 스왑 x" << std::endl;
}


/* 가변 인자 템플릿 - 폴드 방식 C++17 */

template<typename... Args>
void print(Args... args)
{
	//(std::print("{} ", args), ...);
	(std::cout << ... << args);
	std::print("\n");
}

template<typename... Args>
auto sum(Args... args)
{
	return (... + args);
}

int main()
{
	int x = 10, y = 20;
	Swap(x, y);

	double a = 1.5, b = 2.5;

	Swap(a, b);

	print(1, 2, 'A', "dfewge");

	std::cout << sum(1, 2, 3, 4, 5);

	return 0;
}