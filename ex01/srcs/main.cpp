#include "RPN.hpp"

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cout << RED << "Usage: ./RPN \"[0-9] or [+-*/]\"" << END << std::endl;
		return 1;
	}
	RPN rpn;
	rpn.calculate(argv[1]);
	return 0;
}