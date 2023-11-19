#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() : _year(0), _month(0), _day(0)
{
}

BitcoinExchange::~BitcoinExchange()
{
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &copy)
{
	*this = copy;
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &copy)
{
	if (this != &copy)
	{
		this->_data = copy._data;
		this->_year = copy._year;
		this->_month = copy._month;
		this->_day = copy._day;
	}
	return (*this);
}

