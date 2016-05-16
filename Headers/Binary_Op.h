#ifndef BINARY_OP_H
#define BINARY_OP_H

#include "Declarations.h"

#include <vector>
#include <string>

template <typename T>
unsigned int findPos(const T &element, const std::vector<T> &vec, unsigned int start, unsigned int end)
{
	if (start != end)
	{
		if (element < vec.at((start + end) / 2))
			return findPos(element, vec, start, ((end-start) > 1) ? ((start + end) / 2) - 1 : end -1);
		else if (element > vec.at((start + end) / 2))
			return findPos(element, vec, ((start + end) / 2) + 1, end);
		else
			return (start + end) / 2;
	}

	if (start == end && element > vec.at(start))
		return start + 1;
	if (start == end && element <= vec.at(start))
		return start;

	return 0;
}

template <typename T>
inline void binaryInsert(const T &element, std::vector<T> &vec)
{
	vec.insert(vec.begin() + findPos(element, vec, 0, vec.size() - 1), element);
}

template <typename T>
inline unsigned int binarySearch(const T &element, const std::vector<T> &vec)
{
	return findPos(element, vec, 0, vec.size() - 1);
}


#endif // !BINARY_OP_H

