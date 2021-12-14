#pragma once
#ifndef _DATA_MOCKER_H_
#define _DATA_MOCKER_H_

#include <time.h>
#include <iostream>
#include <vector>
#include "Sort.h"

template<class T>
class DataMocker {

private:
	static const int MAX_SIZE = 20;
	static const int REP = 100000;
	static bool _isSeeded;

private:
	std::vector<AbstractSort<T>*> prototypes;
	std::vector<int> sizes = { 5, 10, MAX_SIZE};
	T arr[MAX_SIZE + 1];

public:

	void run() {
		for (AbstractSort<T>* algor: prototypes) {

			for (int size : sizes) {
				double avgValue = 0;
				printf("[sort = %s, size = %d, res = ", algor->name().c_str(), size);
				for (int i = 0; i < REP; ++i) {

					//randomize array
					for (int i = 0; i < size; ++i) 
					{
						arr[i] = rand();
					}

					//sort
					//printf("Finish i = %d\n", i);	//log
					avgValue += algor->sort(arr, size);
				}

				printf("%f]\n", (double)avgValue / REP);
			}

			

		}
	}

public:
	DataMocker() {
		if (!_isSeeded) {
			srand((unsigned int)time(NULL));
			_isSeeded = true;
		}

		prototypes.push_back(new BubbleSort<T>());
		prototypes.push_back(new InsertionSort<T>());
		prototypes.push_back(new SelectionSort<T>());
	}

	~DataMocker() {
		for (AbstractSort<T>* algor : prototypes) {
			if (algor) {
				delete algor;
			}
		}
	}
};
 
template<class T>
bool DataMocker<T>::_isSeeded = false;

#endif // !_DATA_MOCKER_H_



