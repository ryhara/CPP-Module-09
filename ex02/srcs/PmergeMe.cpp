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

void PmergeMe::executeMergeInsertionSort(char **argv)
{
	checkInput(argv);
	printVector("Before: ");
	mergeInsertionSort();
	printVector("After:  ");
	printTime();
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
	std::vector<std::pair<int, int> >  pairs = makePairsVector();
	sortPairsVector(pairs);
	InsertionSortVector(pairs);
	#if DEBUG
		if (!isSorted("vector"))
			throw std::runtime_error("Not sorted.");
	#endif
	clock_t end = clock();
	_vector_time = (double)(end - start) / CLOCKS_PER_SEC * 1000000.0;
}

void PmergeMe::mergeInsertionSortList()
{
	clock_t start = clock();
	std::list<std::pair<int, int> > pairs = makePairsList();
	sortPairsList(pairs);
	InsertionSortList(pairs);
	#if DEBUG
		if (!isSorted("list"))
			throw std::runtime_error("Not sorted.");
	#endif
	clock_t end = clock();
	_list_time = (double)(end - start) / CLOCKS_PER_SEC * 1000000.0;
}

std::vector<std::pair<int, int> > PmergeMe::makePairsVector()
{
	std::vector<std::pair<int, int> > pairs;
	std::vector<int> sorted, tmp;

	for (std::vector<int>::iterator it = _vector.begin(); it != _vector.end(); it++)
	{
		std::pair<int, int> pair;
		std::vector<int>::iterator prev_it = it++;
		if (it == _vector.end()) {
			pairs.push_back(std::make_pair(*prev_it, -1));
			break;
		}
		if (*prev_it > *it) {
			pair.first = *it;
			pair.second = *prev_it;
		} else {
			pair.first = *prev_it;
			pair.second = *it;
		}
		pairs.push_back(pair);
	}
	return (pairs);
}

std::list<std::pair<int, int> >  PmergeMe::makePairsList()
{
	std::list<std::pair<int, int> > pairs;
	std::list<int> sorted, tmp;
	for (std::list<int>::iterator it = _list.begin(); it != _list.end(); it++)
	{
		std::pair<int, int> pair;
		std::list<int>::iterator prev_it = it++;
		if (it == _list.end()) {
			pairs.push_back(std::make_pair(*prev_it, -1));
			break;
		}
		if (*prev_it > *it) {
			pair.first = *it;
			pair.second = *prev_it;
		} else {
			pair.first = *prev_it;
			pair.second = *it;
		}
		pairs.push_back(pair);
	}
	return (pairs);
}

void PmergeMe::InsertionSortVector(std::vector<std::pair<int, int> > &pairs)
{
	std::vector<int> sorted, tmp;
	for (std::vector<std::pair<int, int> >::iterator it = pairs.begin(); it != pairs.end(); it++) {
		if (it->second == -1) {
			tmp.insert(tmp.begin(), it->first);
			continue;
		}
		sorted.push_back(it->first);
		tmp.push_back(it->second);
	}
	for (std::vector<int>::reverse_iterator it = tmp.rbegin(); it != tmp.rend(); it++) {
		int pos = binarySearchInsertionPointVector(sorted, *it);
		sorted.insert(sorted.begin() + pos, *it);
	}
	#if DEBUG
		if (sorted.size() != _vector.size())
			throw std::runtime_error("Not sorted.");
	#endif
	_vector.clear();
	_vector = sorted;
}

void PmergeMe::InsertionSortList(std::list<std::pair<int, int> > &pairs)
{
	std::list<int> sorted, tmp;
	for (std::list<std::pair<int, int> >::iterator it = pairs.begin(); it != pairs.end(); it++) {
		if (it->second == -1) {
			tmp.insert(tmp.begin(), it->first);
			continue;
		}
		sorted.push_back(it->first);
		tmp.push_back(it->second);
	}
	for (std::list<int>::reverse_iterator it = tmp.rbegin(); it != tmp.rend(); it++) {
		int pos = binarySearchInsertionPointList(sorted, *it);
		std::list<int>::iterator i = sorted.begin();
		std::advance(i, pos);
		sorted.insert(i, *it);
	}
	#if DEBUG
		if (sorted.size() != _list.size())
			throw std::runtime_error("Not sorted.");
	#endif
	_list.clear();
	_list = sorted;
}

int PmergeMe::binarySearchInsertionPointVector(std::vector<int>& arr, int value) {
	int low = 0;
	int high = arr.size() - 1;
	while (low <= high) {
		int mid = low + (high - low) / 2;
		if (arr[mid] < value) {
			low = mid + 1;
		} else {
			high = mid - 1;
		}
	}
	return low;
}

int PmergeMe::binarySearchInsertionPointList(std::list<int>& arr, int value) {
	int low = 0;
	int high = arr.size() - 1;
	while (low <= high) {
		int mid = low + (high - low) / 2;
		std::list<int>::iterator it = arr.begin();
		std::advance(it, mid);
		if (*it < value) {
			low = mid + 1;
		} else {
			high = mid - 1;
		}
	}
	return low;
}

bool comparePair(std::pair<int, int> a, std::pair<int, int> b)
{
	return (a.first < b.first);
}

void PmergeMe::sortPairsVector(std::vector<std::pair<int, int> > &pairs)
{
	std::sort(pairs.begin(), pairs.end(), comparePair);
}

void PmergeMe::sortPairsList(std::list<std::pair<int, int> > &pairs)
{
	pairs.sort(comparePair);
}

void PmergeMe::printVector(std::string const &mode)
{
	std::cout << mode;
	for (std::vector<int>::iterator it = _vector.begin(); it != _vector.end(); it++)
			std::cout << *it << " ";
	std::cout << std::endl;
}

void PmergeMe::printTime(void)
{
	std::cout << "Time to process a range of " << _vector.size() << " elements with std::vector<int> : " << _vector_time << " us" << std::endl;
	std::cout << "Time to process a range of " << _list.size() << " elements with std::list<int>   : " << _list_time   << " us" << std::endl;
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

std::ostream &operator<<(std::ostream &out, std::vector<int> &v)
{
	out << "vector: ";
	for (std::vector<int>::iterator it = v.begin(); it != v.end(); it++)
		out << *it << " ";
	out << std::endl;
	return (out);
}

std::ostream &operator<<(std::ostream &out, std::list<int> &l)
{
	out << "list:   ";
	for (std::list<int>::iterator it = l.begin(); it != l.end(); it++)
		out << *it << " ";
	out << std::endl;
	return (out);
}

