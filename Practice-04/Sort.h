#pragma once
#ifndef _SORT_H_
#define _SORT_H_

#include <string>
#include <iostream>

template<class T>
class AbstractSort {
protected:

	/*Average inversion reduce count*/
	double _inversionReduceCount = 0;
	int _lastCount;	//number of inversion in the previous swap
	int _currCount;	//number of inversion in the current swap
	int _swapCount;	//number of swap

public:

	/*Return the average for number of inversion reduce count after swapping by sorting*/
	virtual double sort(T* arr, int size) 
	{
		return -1;
	}
	virtual std::string name() { return ""; }

	int getInvCount(int arr[], int n) {
		int inversionCount = 0;
		for (int i = 0; i < n - 1; i++)
		{
			for (int j = i + 1; j < n; j++)
			{
				if (arr[i] > arr[j]) {
					inversionCount++;
				}
			}
		}
		return inversionCount;
	}

public:
	virtual ~AbstractSort() {/*do nothing*/}
};

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
	~BubbleSort() override {/*do nothing*/}
};


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
	~InsertionSort() override {/*do nothing*/ }
};

template<class T>
class SelectionSort : public AbstractSort<T> {

public:
	double sort(T* arr, int size) override {

		//_lastCount = inversionCount<T>(arr, size);
		_lastCount = getInvCount(arr, size);
		_inversionReduceCount = 0;
		_swapCount = 0;

		for (int i = 0; i < size - 1; ++i) {
			int min = i;
			for (int j = i + 1; j < size; ++j) {
				if (arr[min] > arr[j]) 
				{
					min = j;
				}
			}

			if (arr[i] > arr[min]) {
				std::swap(arr[min], arr[i]);

				++_swapCount;
				//_currCount = inversionCount<T>(arr, size);
				_currCount = getInvCount(arr, size);
				_inversionReduceCount += (_lastCount - _currCount);
				_lastCount = _currCount;
			}
		}

		return (0 == _swapCount ? 0 : (double)_inversionReduceCount / _swapCount);
	}

	std::string name() { return "Selection sort"; }
public:
	~SelectionSort() override {/*do nothing*/ }
};


#endif // !_SORT_H_



