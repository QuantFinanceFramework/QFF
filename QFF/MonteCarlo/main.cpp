#include <random>
#include <PseudoNormalRsg.h>
#include <iostream>

int main() 
{
	PseudoNormalRsg rsg{ 10, 100 };
	PseudoNormalRsg rsg2{ 10, 100 };
	auto seq1 = rsg.generateNormalSequence();
	auto seq2 = rsg.generateNormalSequence();
	auto seq3 = rsg2.generateNormalSequence(); 

	for (auto i : seq1)
	{
		std::cout << i << std::endl;
	}

	std::cout << '\n';

	for (auto i : seq2)
	{
		std::cout << i << std::endl;
	}

	std::cout << '\n';

	for (auto i : seq3)
	{
		std::cout << i << std::endl;
	}
	
	system("pause");
	return 0;
}