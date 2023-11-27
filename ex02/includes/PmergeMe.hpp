#ifndef PMERGEME_HPP
# define PMERGEME_HPP

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

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <utility>
#include <sstream>
#include <ctime>

class PmergeMe
{
	private:
		std::vector<int> _vector;
		std::list<int> _list;
		double _vector_time;
		double _list_time;

		void printVector(std::string const &mode);
		void printTime(void);
		bool isSorted(std::string const &mode);
		void checkInput(char **argv); // throw

		void mergeInsertionSort();
		void mergeInsertionSortVector();
		void mergeInsertionSortList();
		void sortPairsVector(std::vector< std::pair<int, int> > &pairs);
		void sortPairsList(std::list< std::pair<int, int> > &pairs);
		std::vector<std::pair<int, int> >  makePairsVector();
		std::list<std::pair<int, int> >  makePairsList();
		void InsertionSortVector(std::vector<std::pair<int, int> > &pairs);
		void InsertionSortList(std::list<std::pair<int, int> > &pairs);
	public:
		PmergeMe();
		~PmergeMe();
		PmergeMe(const PmergeMe &copy);
		PmergeMe &operator=(const PmergeMe &copy);

		void executeMergeInsertionSort(char **argv);
};

std::ostream &operator<<(std::ostream &out, std::vector<int> &v);
std::ostream &operator<<(std::ostream &out, std::list<int> &l);


#endif