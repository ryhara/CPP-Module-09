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
	std::pair<int, int> tmp;
	if (_vector.size() % 2 != 0) {
		tmp = pairs.back();
		pairs.pop_back();
	}
	sortPairsVector(pairs, 0, pairs.size() - 1);
	if (_vector.size() % 2 != 0)
		pairs.push_back(tmp);
	InsertionSortVector(pairs);
	#if DEBUG
		if (!isSorted("vector"))
			throw std::runtime_error("Not sorted in vector.");
	#endif
	clock_t end = clock();
	_vector_time = (double)(end - start) / CLOCKS_PER_SEC * 1000000.0;
}

void PmergeMe::mergeInsertionSortList()
{
	clock_t start = clock();
	std::list<std::pair<int, int> > pairs = makePairsList();
	std::pair<int, int> tmp;
	if (_list.size() % 2 != 0) {
		tmp = pairs.back();
		pairs.pop_back();
	}
	sortPairsList(pairs, 0, pairs.size() - 1);
	if (_list.size() % 2 != 0)
		pairs.push_back(tmp);
	InsertionSortList(pairs);
	#if DEBUG
		if (!isSorted("list"))
			throw std::runtime_error("Not sorted in list.");
	#endif
	clock_t end = clock();
	_list_time = (double)(end - start) / CLOCKS_PER_SEC * 1000000.0;
}

std::vector<std::pair<int, int> > PmergeMe::makePairsVector()
{
	std::vector<std::pair<int, int> > pairs;
	std::vector<int> sorted;
	size_t vector_size = _vector.size();

	if (vector_size % 2 != 0)
		vector_size--;
	for (size_t i = 0; i < vector_size; i += 2) {
		std::pair<int, int> pair;
		if (_vector[i] > _vector[i + 1]) {
			pair.first = _vector[i + 1];
			pair.second = _vector[i];
		} else {
			pair.first = _vector[i];
			pair.second = _vector[i + 1];
		}
		pairs.push_back(pair);
	}
	if (_vector.size() % 2 != 0)
		pairs.push_back(std::make_pair(-1, _vector.back()));
	return (pairs);
}

std::list<std::pair<int, int> >  PmergeMe::makePairsList()
{
	std::list<std::pair<int, int> > pairs;
	std::list<int> sorted;
	std::list<int>::iterator it, prev_it, end;

	end = _list.end();
	if (_list.size() % 2 != 0)
		end--;
	for (std::list<int>::iterator it = _list.begin(); it != end; it++)
	{
		std::pair<int, int> pair;
		std::list<int>::iterator prev_it = it++;
		if (*prev_it > *it) {
			pair.first = *it;
			pair.second = *prev_it;
		} else {
			pair.first = *prev_it;
			pair.second = *it;
		}
		pairs.push_back(pair);
	}
	if (_list.size() % 2 != 0)
		pairs.push_back(std::make_pair(-1, _list.back()));
	return (pairs);
}

void PmergeMe::InsertionSortVector(std::vector<std::pair<int, int> > &pairs)
{
	std::vector<int> sorted;
	int last_one;
	if (_vector.size() % 2 != 0) {
		last_one = pairs.back().second;
		pairs.pop_back();
	}
	for (std::vector<std::pair<int, int> >::iterator it = pairs.begin(); it != pairs.end(); it++) {
		sorted.push_back(it->first);
	}
	std::vector<int> jacobs = jacobsthalInsertionSequence(pairs.size());
	std::vector<int>::iterator pos, start;
	for (std::vector<int>::iterator it = jacobs.begin(); it != jacobs.end(); it++) {
		start = sorted.begin() + pairs.size() - 1 - *it;
		pos = std::lower_bound(start, sorted.end(), pairs[pairs.size() - 1 - *it].second);
		sorted.insert(pos, pairs[pairs.size() - 1 - *it].second);
	}
	if (_vector.size() % 2 != 0) {
		pos = std::lower_bound(sorted.begin(), sorted.end(), last_one);
		sorted.insert(pos, last_one);
	}
	_vector.clear();
	_vector = sorted;
}

void PmergeMe::InsertionSortList(std::list<std::pair<int, int> > &pairs)
{
	std::list<int> sorted;
	int last_one;
	if (_list.size() % 2 != 0) {
		last_one = pairs.back().second;
		pairs.pop_back();
	}
	for (std::list<std::pair<int, int> >::iterator it = pairs.begin(); it != pairs.end(); it++) {
		sorted.push_back(it->first);
	}
	std::vector<int> jacobs = jacobsthalInsertionSequence(pairs.size());
	std::list<int>::iterator pos, start;
	std::list<std::pair<int, int> >::iterator tmp_it;;
	for (std::vector<int>::iterator it = jacobs.begin(); it != jacobs.end(); it++) {
		tmp_it = pairs.end();
		std::advance(tmp_it, -1 - *it);
		start = sorted.begin();
		std::advance(start, pairs.size() - 1 - *it);
		pos = std::lower_bound(start, sorted.end(), (*tmp_it).second);
		sorted.insert(pos, (*tmp_it).second);
	}
	if (_list.size() % 2 != 0) {
		pos = std::lower_bound(sorted.begin(), sorted.end(), last_one);
		sorted.insert(pos, last_one);
	}
	_list.clear();
	_list = sorted;
}

int PmergeMe::binarySearchInsertionPointVector(std::vector<int>& arr, int start, int value) {
	int low = start;
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

int PmergeMe::binarySearchInsertionPointList(std::list<int>& arr, int start, int value) {
	int low = start;
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

void PmergeMe::sortPairsVector(std::vector<std::pair<int, int> > &pairs, int left, int right)
{
	if (left < right)
	{
		int mid = left + (right - left) / 2;
		sortPairsVector(pairs, left, mid);
		sortPairsVector(pairs, mid + 1, right);
		mergeVector(pairs, left, mid, right);
	}
}


void PmergeMe::sortPairsList(std::list<std::pair<int, int> > &pairs, int left, int right)
{
	if (left < right)
	{
		int mid = left + (right - left) / 2;
		sortPairsList(pairs, left, mid);
		sortPairsList(pairs, mid + 1, right);
		mergeList(pairs, left, mid, right);
	}
}

void PmergeMe::mergeList(std::list<std::pair<int, int > > &pairs, int left, int mid, int right)
{
	int n1 = mid - left + 1;
	int n2 = right - mid;
	std::list<std::pair<int, int> > L, R;
	std::list<std::pair<int, int> >::iterator it = pairs.begin(); std::advance(it, left);
	for (int i = 0; i < n1; i++)
		L.push_back(*it++);
	for (int j = 0; j < n2; j++)
		R.push_back(*it++);
	std::list<std::pair<int, int> >::iterator itL, itR;
	itL = L.begin();
	itR = R.begin();
	it = pairs.begin(); std::advance(it, left);
	while (itL != L.end() && itR != R.end())
	{
		if (itL->first <= itR->first)
			*it++ = *itL++;
		else
			*it++ = *itR++;
	}
	while (itL != L.end())
		*it++ = *itL++;
	while (itR != R.end())
		*it++ = *itR++;
}

void PmergeMe::mergeVector(std::vector<std::pair<int, int> > &pairs, int left, int mid, int right)
{
	int i, j, k;
	int n1 = mid - left + 1;
	int n2 = right - mid;
	std::vector<std::pair<int, int> > L, R;
	for (i = 0; i < n1; i++)
		L.push_back(pairs[left + i]);
	for (j = 0; j < n2; j++)
		R.push_back(pairs[mid + 1 + j]);
	i = 0;
	j = 0;
	k = left;
	while (i < n1 && j < n2)
	{
		if (L[i].first <= R[j].first)
			pairs[k++] = L[i++];
		else
			pairs[k++] = R[j++];
	}
	while (i < n1)
		pairs[k++] = L[i++];
	while (j < n2)
		pairs[k++] = R[j++];
}

int PmergeMe::jacobsthal(int n)
{
	if (n == 0)
		return (0);
	if (n == 1)
		return (1);
	return (jacobsthal(n - 1) + 2 * jacobsthal(n - 2));
}

std::vector<int> PmergeMe::jacobsthalInsertionSequence(int n)
{
	std::vector<int> indexes, sequence;
	int i = 2;
	while (jacobsthal(i) < n)
		indexes.push_back(jacobsthal(i++));
	indexes.push_back(n);
	sequence.push_back(0);
	for (size_t i = 1; i < indexes.size(); i++) {
		for (int j = indexes[i]; j > indexes[i - 1]; j--)
			sequence.push_back(j - 1);
	}
	return sequence;
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

std::ostream &operator<<(std::ostream &out, std::vector<std::pair<int, int> > &v)
{
	out << "vector<std::pair<int, int> >: " << std::endl;
	for (std::vector<std::pair<int, int> >::iterator it = v.begin(); it != v.end(); it++)
		out << "(" << it->first << ", " << it->second << ") " << std::endl;
	out << std::endl;
	return (out);
}

std::ostream &operator<<(std::ostream &out, std::list<std::pair<int, int> > &l)
{
	out << "list<std::pair<int,int > >:" << std::endl;
	for (std::list<std::pair<int, int> >::iterator it = l.begin(); it != l.end(); it++)
		out << "(" << it->first << ", " << it->second << ") " << std::endl;
	out << std::endl;
	return (out);
}
