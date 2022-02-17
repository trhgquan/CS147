#pragma once
#ifndef _DATA_MOCKER_H_
#define _DATA_MOCKER_H_

#include <time.h>
#include <iostream>
#include <vector>

#include "Sort.h"
#include "ElementWrapper.h"

template<class T>
class DataMocker {

private:
	static const int MIN_SIZE = 30;
	static const int MAX_SIZE = 100;
	static const int REP = 1;
	static const int STEP = 5;
	static bool _isSeeded;

private:
	std::vector<AbstractSort<T>*> prototypes;
	//std::vector<int> sizes = { 5 };
	ElementWrapper<int> _arr[MAX_SIZE + 1];
	double** _inversionTable;

private:
	void _resetInversionTable(int size) {
		for (int i = 0; i < size; ++i) {
			memset(_inversionTable[i], 0, sizeof(double)*size);
		}
	}

	void _getAVGInversionTable(int size) {
		for (int i = 0; i < size; ++i) {
			for (int j = 0; j < size; ++j) {
				_inversionTable[i][j] /= REP;
			}
		}
	}

	void _printInversionTable(int size) {
		for (int i = 0; i < size; ++i) {
			printf("- Lan %d: ", i);
			for (int j = 0; j < size; ++j) 
			{
				printf("%0.2f; ", _inversionTable[i][j]);
			}
			printf("\n");
		}
		printf("\n");
	}

public:

	void run() {
		for (AbstractSort<T>* algor: prototypes) {
			algor->setArray(_arr);
			algor->setInversionTable(_inversionTable);
			for (int size = MIN_SIZE; size <= MAX_SIZE; size += STEP ) {
				double avgSwapCount = 0;
				algor->setSize(size);
				_resetInversionTable(size);
				
				for (int i = 0; i < REP; ++i) {

					//randomize array
					for (int i = 0; i < size; ++i)
					{
						_arr[i].setValue(rand());
					}

					//sort
					
					/*avgValue += algor->sort();*/
					avgSwapCount += algor->sort();
					//printf("\tSwap count: %d\n\n", algor->swapCount());
				}
				avgSwapCount /= REP;
				printf("[sort = %s, size = %d, rep = %d, AVG swap = %0.2f]\n", algor->name().c_str(), size, REP, avgSwapCount);
				_getAVGInversionTable(size);
				_printInversionTable(size); printf("\n");
				//printf("%f]\n", (double)avgValue / REP);

				
			}

			

		}
	}

public:
	DataMocker() {
		if (!_isSeeded) {
			srand((unsigned int)time(NULL));
			_isSeeded = true;
		}

		_inversionTable = new double*[MAX_SIZE + 2];
		for (int i = 0; i < MAX_SIZE + 2; ++i) {
			_inversionTable[i] = new double[MAX_SIZE + 2];
		}

		//prototypes.push_back(new BubbleSort<T>());
		//prototypes.push_back(new InsertionSort<T>());
		prototypes.push_back(new SelectionSort<T>());
	}

	~DataMocker() {
		for (AbstractSort<T>* algor : prototypes) {
			if (algor) {
				delete algor;
			}
		}

		if (_inversionTable) {
			for (int i = 0; i < MAX_SIZE + 2; ++i) {
				if (_inversionTable[i])
				{
					delete[] _inversionTable[i];
				}
			}
			delete[] _inversionTable;
		}

	}
};
 
template<class T>
bool DataMocker<T>::_isSeeded = false;

#endif // !_DATA_MOCKER_H_



