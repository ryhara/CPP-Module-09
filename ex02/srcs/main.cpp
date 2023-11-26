#include "PmergeMe.hpp"

int main(int argc, char **argv)
{
	PmergeMe p;

	if (argc == 1)
	{
		std::cout << RED << "Error: " << "No input" << END << std::endl;
		return (1);
	}
	try {
		p.executeMergeInsertionSort(argv);
	} catch (std::exception &e) {
		std::cout << RED << "Error: " << e.what() << END << std::endl;
		return (1);
	}
	return (0);
}