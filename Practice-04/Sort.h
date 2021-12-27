#pragma once
#ifndef _SORT_H_
#define _SORT_H_

#include <string>
#include <iostream>
#include <algorithm>
#include "ElementWrapper.h"

template<class T>
class AbstractSort {
protected:
	ElementWrapper<T>* _array;
	double** _inversionTable;
	int _size;

	/*Average inversion reduce count*/
	double _inversionReduceCount = 0;
	int _lastCount;	//number of inversion in the previous swap
	int _currCount;	//number of inversion in the current swap
	int _swapCount;	//number of swap

protected:
	void clearInversionTableRow() {
		for (int i = 0; i < _size; ++i)
		{
			_array[i].reset();
		}
	}

	
	void getLeftInversionTableRow() {
		for (int i = 1; i < _size; ++i) {
			for (int j = 0; j < i; ++j) {
				if (_array[j].value() > _array[i].value()) {
					_array[i].IncLeftInv();
				}
			}
		}
	}

	void updateLeftInversionTable(int stepIndex) {

		ElementWrapper<T>* tempArr = new ElementWrapper<T>[_size + 1];
		memcpy(tempArr, _array, sizeof(ElementWrapper<T>)*_size);
		std::sort(tempArr, tempArr + _size,
			[](ElementWrapper<T>& a, ElementWrapper<T>& b) -> bool
		{
			return a.value() < b.value();	//increase sort
		}
		);

		/*
		printf("\t%d) ", stepIndex);
		for (int i = 0; i < _size; ++i) {
			printf("%d ", tempArr[i].leftInversionCount());
		}
		printf("\n");
		*/

		for (int i = 0; i < _size; ++i) {
			_inversionTable[stepIndex][i] += tempArr[i].leftInversionCount();
		}
		delete[] tempArr;
	}

public:

	/*Return the average for number of inversion reduce count after swapping by sorting*/
	virtual double sort() 
	{
		return -1;
	}
	virtual std::string name() { return ""; }

	/*
	int getInvCount(ElementWrapper<T> arr[], int n) {
		int inversionCount = 0;
		for (int i = 0; i < n - 1; i++)
		{
			for (int j = i + 1; j < n; j++)
			{
				if (arr[i].value() > arr[j].value()) 
				{
					++inversionCount;
				}
			}
		}
		return inversionCount;
	}*/

public:
	int swapCount() { return _swapCount; }
	void setArray(ElementWrapper<T>* arr) {_array = arr;}
	void setSize(int size) { _size = size; }
	void setInversionTable(double** inversionTable) { _inversionTable = inversionTable; }

public:
	virtual ~AbstractSort() {/*do nothing*/}
};


template<class T>
class SelectionSort : public AbstractSort<T> {

public:
	double sort() override {

		//print input
		/*
		printf("- Input: ");
		for (int i = 0; i < _size; ++i) {
			printf("%d ", _array[i].value());
		}
		printf("\n");*/

		/*
		_lastCount = getInvCount(arr, size);
		_inversionReduceCount = 0;*/
		_swapCount = 0;

		for (int i = 0; i < _size - 1; ++i) {
			clearInversionTableRow();
			getLeftInversionTableRow();
			updateLeftInversionTable(i);
			int min = i;
			for (int j = i + 1; j < _size; ++j) {
				if (_array[min].value() >_array[j].value())
				{
					min = j;
				}
			}

			if (_array[i].value() > _array[min].value()) {
				std::swap(_array[min], _array[i]);

				++_swapCount;
				//_currCount = getInvCount(arr, size);
				//_inversionReduceCount += (_lastCount - _currCount);
				//_lastCount = _currCount;
			}
		}

		//Get the last inversion table
		clearInversionTableRow();
		getLeftInversionTableRow();
		updateLeftInversionTable(_size - 1);

		//print output
		/*
		printf("- Output: ");
		for (int i = 0; i < _size; ++i) {
			printf("%d ", _array[i].value());
		}
		printf("\n");*/

		//return (0 == _swapCount ? 0 : (double)_inversionReduceCount / _swapCount);
		return _swapCount;
	}

	std::string name() { return "Selection sort"; }
public:
	~SelectionSort() override
	{
		//do nothing
	}
};

/*
template<class T>
class BubbleSort : public AbstractSort<T> {

public:
	double sort(T* arr, int size) override {

		//_lastCount = inversionCount<T>(arr, size);
		_lastCount = getInvCount(arr, size);
		_inversionReduceCount = 0;
		_swapCount = 0;

		for (int i = 0; i < size - 1; ++i) {
			for (int j = i + 1; j < size; ++j) {
				if (arr[i] > arr[j]) {
					std::swap(arr[i], arr[j]);

					++_swapCount;
					//_currCount = inversionCount<T>(arr, size);
					_currCount = getInvCount(arr, size);
					_inversionReduceCount += (_lastCount - _currCount);
					_lastCount = _currCount;
				}
			}
		}

		return (0 == _swapCount ? 0 : (double)_inversionReduceCount/_swapCount);
	}

	std::string name() { return "Bubble sort"; }
public:
	~BubbleSort() override 
	{
		//do nothing
	}
};*/

/*
template<class T>
class InsertionSort : public AbstractSort<T> {

public:
	double sort(T* arr, int size) override {
		T save;
		int j;

		//_lastCount = inversionCount<T>(arr, size);
		_lastCount = getInvCount(arr, size);
		_inversionReduceCount = 0;

		for (int i = 1; i < size; ++i) {
			save = arr[i];
			for (j = i - 1; j >= 0; --j) {
				
				if (arr[j] > save) 
				{
					arr[j + 1] = arr[j];
				}
				else break;
			}
			arr[j + 1] = save;
			
			//_currCount = inversionCount<T>(arr, size);
			_currCount = getInvCount(arr, size);
			_inversionReduceCount += (_lastCount - _currCount);
			_lastCount = _currCount;
		}

		return (double)_inversionReduceCount / size;
	}

	std::string name() { return "Insertion sort"; }
public:
	~InsertionSort() override 
	{
		//do nothing
	}
};*/



#endif // !_SORT_H_



