#include <iostream>
#include <ctime>
#include "Solver.h"

int main(int argc, char** argv)
{
	clock_t start = clock();


	for (size_t i = 1; i < argc; i++)
	{
		std::string fileName = argv[i];

		Solver s(fileName);
		s.start();
	}
	double duration = (clock() - start) / static_cast<double>(CLOCKS_PER_SEC);
	std::cout << "total time: " << duration << '\n';


	return 0;
}
