#include "PmergeMe.hpp"


PmergeMe::PmergeMe()
{
}

PmergeMe::~PmergeMe()
{
	_vector.clear();
	_list.clear();
}

PmergeMe::PmergeMe(const PmergeMe &copy)
{
	*this = copy;
}

PmergeMe &PmergeMe::operator=(const PmergeMe &copy)
{
	if (this != &copy)
	{
		this->_vector = copy._vector;
		this->_list = copy._list;
	}
	return (*this);
}

void PmergeMe::printVector(std::string const &mode)
{
	std::cout << mode;
	for (std::vector<int>::iterator it = _vector.begin(); it != _vector.end(); it++)
			std::cout << *it << " ";
	std::cout << std::endl;
}

void PmergeMe::checkInput(char **argv)
{
	size_t i = 1;

	while (argv[i]) {
		std::stringstream ss(argv[i]);
		int number;
		ss >> number;
		if (ss.fail() || !ss.eof())
			throw std::runtime_error("bad input => " + std::string(argv[i]));
		if (number < 0)
			throw std::runtime_error("bad input  => " + std::string(argv[i]));
		_vector.push_back(number);
		_list.push_back(number);
		i++;
	}
}


bool PmergeMe::isSorted(std::string const &mode)
{
	if (mode == "vector")
	{
		for (std::vector<int>::iterator it = _vector.begin(); it != _vector.end() - 1; it++)
			if (*it > *(it + 1))
				return (false);
	}
	else if (mode == "list")
	{
		std::list<int>::iterator next_it = _list.begin();
		next_it++;
		for (std::list<int>::iterator it = _list.begin() ; next_it != _list.end(); it++, next_it++)
			if (*it > *next_it)
				return (false);
	}
	return (true);
}

void PmergeMe::mergeInsertionSort()
{
	if (isSorted("vector"))
		throw std::runtime_error("already sorted.");
	mergeInsertionSortVector();
	mergeInsertionSortList();

}

void PmergeMe::mergeInsertionSortVector()
{
	clock_t start = clock();

	std::sort(this->_vector.begin(), this->_vector.end());
	if (!isSorted("vector"))
		throw std::runtime_error("Not sorted.");
	clock_t end = clock();
	_vector_time = (double)(end - start) / CLOCKS_PER_SEC * 1000000.0;
}

void PmergeMe::mergeInsertionSortList()
{
	clock_t start = clock();
	_list.sort();
	if (!isSorted("list"))
		throw std::runtime_error("Not sorted.");
	clock_t end = clock();

	_list_time = (double)(end - start) / CLOCKS_PER_SEC * 1000000.0;
}

void PmergeMe::printTime(void)
{
	std::cout << "Time to process a range of 5 elements with std::vector<unsigned int> : " << _vector_time << " us" << std::endl;
	std::cout << "Time to process a range of 5 elements with std::list<unsigned int>   : " << _list_time   << " us" << std::endl;
}

void PmergeMe::executeMergeInsertionSort(char **argv)
{
	checkInput(argv);
	printVector("Before: ");
	mergeInsertionSort();
	printVector("After:  ");
	printTime();
}