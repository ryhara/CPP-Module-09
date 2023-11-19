#include "BitcoinExchange.hpp"

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << "Error" << std::endl << "Usage: ./bitcoin [file_path]" << std::endl;
		return (1);
	}
	BitcoinExchange exchange;
	exchange.setAmount(std::stod(argv[1]));
	exchange.display();
	return (0);
}