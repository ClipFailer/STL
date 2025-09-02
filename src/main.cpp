#include <iostream>

#include "Vector.h"

int main(int argc, char** argv)
{
	std::cout << "STL implentation\n";

	Vector<int> vec(4, 4);
	std::cout << vec;

	vec.Insert(10, 3);
	std::cout << vec;

	std::cout << vec.Remove(10) << std::endl;
	std::cout << vec;

	return 0;
}