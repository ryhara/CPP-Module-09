#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <map>
#include <regex>

#define END				"\033[0m"
#define BOLD			"\033[1m"
#define BLACK			"\033[30m"
#define RED				"\033[31m"
#define GREEN			"\033[32m"
#define YELLOW			"\033[33m"
#define BLUE			"\033[34m"
#define MAGENTA			"\033[35m"
#define CYAN			"\033[36m"
#define WHITE			"\033[37m"
#define UNDERLINE		"\033[4m"
#define BOLD_UNDERLINE	"\033[1;4m"


struct Date
{
	int day;
	int month;
	int year;
};

typedef std::map<std::string, double>::iterator iterator;

class BitcoinExchange
{
	private:
		std::map<std::string, double> _data;

		void checkLine(std::string const &line);
		bool checkFirstLine(std::string line);
		void checkDate(std::string const &date);
		bool checkDateFormat(std::string const &date);
		bool checkDateRange(std::string const &date);
		void splitDate(std::string const &date, Date &d);
		void checkValue(std::string const &value);
		std::string findNearestDate(std::string const &date);
		void exchange(std::string const &date, double value);
	public :
		BitcoinExchange();
		~BitcoinExchange();
		BitcoinExchange(const BitcoinExchange &copy);
		BitcoinExchange &operator=(const BitcoinExchange &copy);

		void readData(std::string const &file);
		void startTransaction(std::string const &file);
};


#endif