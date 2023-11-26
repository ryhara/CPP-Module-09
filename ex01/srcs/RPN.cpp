#include "RPN.hpp"

RPN::RPN()
{
}

RPN::~RPN()
{
}

RPN::RPN(const RPN &copy)
{
	*this = copy;
}

RPN &RPN::operator=(const RPN &copy)
{
	if (this != &copy)
	{
		this->_data = copy._data;
	}
	return *this;
}

void RPN::calculate(std::string str)
{
	int i = 0;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			this->_data.push_back(str[i] - '0');
		}
		else if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/')
		{
			if (this->_data.size() < 2)
			{
				std::cout << RED <<  "Error: Invalid format." << END << std::endl;
				std::exit(1);
			}
			int a = this->_data.back();
			this->_data.pop_back();
			int b = this->_data.back();
			this->_data.pop_back();
			if (str[i] == '+')
				this->_data.push_back(b + a);
			else if (str[i] == '-')
				this->_data.push_back(b - a);
			else if (str[i] == '*')
				this->_data.push_back(b * a);
			else if (str[i] == '/')
			{
				if (a == 0)
				{
					std::cout << RED << "Error: Division by zero." << END << std::endl;
					std::exit(1);
				}
				this->_data.push_back(b / a);
			}
		}
		else if (str[i] != ' ')
		{
			std::cout << RED << "Error: Invalid character." << END << std::endl;
			std::exit(1);
		}
		i++;
	}
	printAnswer();
}

void RPN::printAnswer()
{
	if (this->_data.size() != 1)
	{
		std::cout << RED << "Error: Invalid format." << END << std::endl;
		std::exit(1);
	}
	std::cout << GREEN << this->_data.back() << END << std::endl;
}