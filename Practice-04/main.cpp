/**
* @file main.cpp
* @author @trhgquan - https://github.com/trhgquan
* @date 2021-12-10
*/

#include<iostream>
#include "DataMocker.h"

int main() {

	DataMocker<int> mocker;
	mocker.run();

	printf("Fin\n");
	system("PAUSE");
	return 0;
}