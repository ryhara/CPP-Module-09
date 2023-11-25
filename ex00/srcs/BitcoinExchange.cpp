#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{
}

BitcoinExchange::~BitcoinExchange()
{
	_data.clear();
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
	}
	return (*this);
}

void BitcoinExchange::readData(std::string const &file)
{
	std::ifstream ifs(file);
	std::string line;
	if (!ifs)
	{
		std::cerr << RED <<  "Error: " << "could not open file." << END << std::endl;
		std::exit(1);
	}
	else
	{
		getline(ifs, line);
		while (getline(ifs, line))
		{
			std::stringstream ss(line);
			std::string date, rate;
			double rate_value;
			getline(ss, date, ',');
			ss >> rate_value;
			_data[date] =  rate_value;
		}
		ifs.close();
	}
}

void BitcoinExchange::startTransaction(std::string const &file)
{
	std::ifstream ifs(file);
	std::string line;
	if (!ifs)
	{
		std::cerr << RED <<  "Error: " << "could not open file." << END << std::endl;
		std::exit(1);
	}
	else
	{
		if (getline(ifs, line))
		{
			if (!checkFirstLine(line))
				std::exit(1);
		}
		while (getline(ifs, line)) {
			if (line.empty())
				continue ;
			checkLine(line);
		}
		ifs.close();
	}
}


bool BitcoinExchange::checkFirstLine(std::string line)
{
	line.erase(std::remove(line.begin(), line.end(), ' '), line.end());
	if (!line.compare("date|value"))
		return (true);
	else
	{
		std::cerr << RED << "Error: " <<  "Input file must start with \"date | value\"" << END  << std::endl;
		return (false);
	}
}

void BitcoinExchange::checkLine(std::string const &line)
{
	std::string date;
	std::string value;
	std::stringstream ss(line);
	double number;

	try {
		if (getline(ss, date, '|'))
			checkDate(date); // throw exception
		else
			throw std::runtime_error("getline failed.");
		if (getline(ss, value))
			checkValue(value); // throw exception
		else
			throw std::runtime_error("getline failed.");
	} catch (std::exception &e) {
		std::cerr << RED << "Error: " << e.what() << END << std::endl;
		return ;
	}
	date.erase(std::remove(date.begin(), date.end(), ' '), date.end());
	ss.clear(); ss.str("");
	ss << value;
	ss >> number;
	exchange(date, number);
}

void BitcoinExchange::checkDate(std::string const &date)
{
	std::string new_date;
	new_date = date;
	new_date.erase(std::remove(new_date.begin(), new_date.end(), ' '), new_date.end());
	if (!checkDateFormat(new_date))
		throw std::runtime_error("bad input => " + date);
	if (!checkDateRange(new_date))
		throw std::runtime_error("bad input => " + date);
	return ;
}

bool BitcoinExchange::checkDateFormat(std::string const &date)
{
	if (date.length() != 10)
		return (false);
	if (date[4] != '-' || date[7] != '-')
		return (false);
	for (int i = 0; i < 10; i++)
	{
		if (i == 4 || i == 7)
			continue ;
		if (date[i] < '0' || date[i] > '9')
			return (false);
	}
	return (true);
}

bool BitcoinExchange::checkDateRange(std::string const &date)
{
	int lastDayOfMonth[]  = {31,28,31,30,31,30,31,31,30,31,30,31};
	Date d;

	splitDate(date, d);
	if (d.year % 400 == 0 || (d.year % 4 == 0 && d.year % 100 != 0))
		lastDayOfMonth[1] = 29;
	if (d.month < 1 ||d.month > 12)
		return (false);
	if (d.day < 1 || d.day > 31)
		return (false);
	if (d.day > lastDayOfMonth[d.month - 1])
		return (false);
	return (true);
}


void BitcoinExchange::splitDate(std::string const &date, Date &d)
{
	std::stringstream ss(date);
	std::string year, month, day;
	getline(ss, year, '-');
	getline(ss, month, '-');
	getline(ss, day);
	ss.clear();
	ss.str("");
	ss << year << " " << month << " "  <<  " " << day;
	ss >> d.year >> d.month >> d.day;
}


void BitcoinExchange::exchange(std::string const &date, double value)
{
	std::string nearestDate = findNearestDate(date);
	double rate = _data[nearestDate];
	std::cout << date << " => " << value << " = " << rate * value << std::endl;
	return ;
}

std::string BitcoinExchange::findNearestDate(std::string const &date)
{
	iterator it = _data.begin();
	iterator prev = it;

	for (++it ; it != _data.end(); it++) {
		Date data_d, input_d;
		splitDate(date, input_d);
		splitDate(it->first, data_d);
		if (input_d.year == data_d.year) {
			if (input_d.month == data_d.month) {
				if (input_d.day == data_d.day)
					return (it->first);
				else if (input_d.day < data_d.day)
					return (prev->first);
			}
			else if (input_d.month < data_d.month) {
				return (prev->first);
			}
		}
		else if (input_d.year < data_d.year) {
			return (prev->first);
		}
		prev = it;
	}
	return (prev->first);
}


void BitcoinExchange::checkValue(std::string const &value)
{
	std::stringstream ss(value);
	double number;
	ss >> number;
	if (ss.fail() || !ss.eof())
		throw std::runtime_error("bad input => " + value);
	if (number < 0.0 )
		throw std::runtime_error("not a positive number.");
	else if (number > 1000.0)
		throw std::runtime_error("too large a number.");
}