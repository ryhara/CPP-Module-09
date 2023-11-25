#include "BitcoinExchange.hpp"

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << RED << "Error: could not open file." << END << std::endl;
		return (1);
	}
	BitcoinExchange exchange;
	exchange.readData("./data.csv");
	exchange.startTransaction(argv[1]);
	return (0);
}