#include <iostream>

#include "Vector.h"

int main(int argc, char** argv)
{
	std::cout << "STL implentation\n";

	Vector<int> vec;
	vec.ChangeGrowthFactor(1.5f);

	vec.AddBack(1);
	vec.AddBack(5);
	vec.AddBack(5);
	vec.AddBack(5);
	vec.AddBack(5);


	return 0;
}