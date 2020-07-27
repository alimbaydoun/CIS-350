/*
	SortedArray.cpp skeleton
	Ali Baydoun
	CIS-350-001
*/

#ifndef SORTEDARRAY_CPP
#define SORTEDARRAY_CPP

#include "SortedArray.h"
#include <algorithm> 

// Default constructor
template <typename Object>
SortedArray<Object>::SortedArray()
{
	theSize = 0;
	theCapacity = 0;
	objects = new Object[SPARE_CAPACITY];
}

// Copy constructor
template <typename Object>
SortedArray<Object>::SortedArray(const SortedArray <Object>& from)
{
	theSize = from.size();
	theCapacity = from.theCapacity;
	objects = new Object[from.theCapacity];

	for (int d = 0; d < theSize; d++) {
		objects[d] = from[d];

	}
}

// destructor
template <typename Object>
SortedArray<Object>::~SortedArray()
{
	delete[] objects;
}

// overloaded assignment operator
template <typename Object>
const SortedArray<Object>& SortedArray<Object>::operator= (const SortedArray& from)
{
	if (this != &from) {
		delete[] objects;
		theSize = from.size();
		theCapacity = from.theCapacity;
		objects = new Object[theCapacity];

		for (int d = 0; d < theSize; d++) {
			objects[d] = from.objects[d];
		}

	}
	return *this;
}

// Accessor Operator []
template <typename Object>
const Object& SortedArray<Object>::operator[](int idx) const
{
	return objects[idx];
}

// check if two sorted arrays are the same
template <typename Object>
bool SortedArray<Object>::equals(const SortedArray <Object>& rhs)
{
	if (rhs.theSize == theSize) {
		for (int d = 0; d < theSize; d++) {
			if (objects[d] != rhs[d]) {

				return false;
			}
		}

		return true;
	}

	return false;
}

//check if the array is empty
template <typename Object>
bool SortedArray<Object>::empty() const
{
	if (theSize > 0) {
		return false;
	}

	return true;
}

//get the size
template <typename Object>
int SortedArray<Object>::size() const
{
	return theSize;
}

//get the capacity 
template <typename Object>
int SortedArray<Object>::capacity() const
{
	return theCapacity;
}

// reserve
template<typename Object>
void SortedArray<Object>::reserve(int newCapacity)
{
	if (newCapacity <= theCapacity) {
		return;

	}
	else {
		Object* currArray = objects;
		objects = new Object[newCapacity];
		theCapacity = newCapacity;
		for (int d = 0; d < theSize; d++) {
			objects[d] = currArray[d];
		}
		delete[] currArray;
	}
}

//print elements of the array
template <typename Object>
void SortedArray<Object>::print(ostream& out, char delimiter) const
{
	for (int d = 0; d < theSize; d++) {
		out << objects[d] << delimiter;
	}
	
	out << endl;
}


// clear array of elements
template <typename Object>
void SortedArray<Object>::clear()
{
	for (int d = 0; d < theSize; d++) {
		objects[d] = {
		  0
		};
	}
}

// insert element into sorted array
template <typename Object>
void SortedArray<Object>::insert(const Object& obj)
{
	if (theSize < 0)
		theSize = 0;

	if (theSize >= theCapacity) {
		reserve(max(1, (2 * theSize + 1)));
	}

	if (theSize >= 0) {
		objects[theSize] = obj;
		int d = theSize - 1;
		while (d >= 0 && objects[d] > objects[d + 1]) {
			swap(objects[d], objects[d + 1]);
			d--;
		}
		theSize++;
	}
}

//remove the first element
template <typename Object>
void SortedArray<Object>::deleteMin()
{
	for (int d = 1; d < theSize; d++) {
		objects[d - 1] = objects[d];
	}
	theSize--;
}

//delete the maximum element from the sorted array
template <typename Object>
void SortedArray<Object>::deleteMax()
{
	if (theSize > 0) {
		--theSize;
	}
}

//find the minimum element in the sorted array
template <typename Object>
const Object& SortedArray<Object>::findMin() const
{
	return objects[0];
}

//find the max element in the sorted array
template <typename Object>
const Object& SortedArray<Object>::findMax() const
{
	return objects[theSize - 1];
}

//binary search the array
template <typename Object>
int SortedArray<Object>::binarySearch(const Object& obj)
{
	if (theSize > 0) {
		int iLow = 0, iHigh = theSize - 1;

		while (iLow <= iHigh) {
			int iMid = (iLow + iHigh) / 2;

			if (objects[iMid] == obj) {
				return iMid;
			}

			if (objects[iMid] < obj) {
				iLow = iMid + 1;
			}
			
			else {
				iHigh = iMid - 1;
			}
		}
	}
	return -1;
}


#endif