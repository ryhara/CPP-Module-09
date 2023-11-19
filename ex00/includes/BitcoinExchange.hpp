#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <map>

class BitcoinExchange
{
	private:
		std::map<std::string, double> _data;
		int _year;
		int _month;
		int _day;
	public :
		BitcoinExchange();
		~BitcoinExchange();
		BitcoinExchange(const BitcoinExchange &copy);
		BitcoinExchange &operator=(const BitcoinExchange &copy);
		void setAmount(double amount);
		void display();
		void parseInput(std::string input);
		void parseLine(std::string line);
		void parseDate(std::string date);
		void parseRateData(std::string rateData);

};


#endif