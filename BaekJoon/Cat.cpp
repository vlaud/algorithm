#include "Cat.h"

void Cat::PrintCat() const
{
	std::cout << "Cat's name: " << name << std::endl;
	std::cout << "Cat's age: " << age << std::endl;
	std::cout << "Cat's weight: " << weight << std::endl;
}