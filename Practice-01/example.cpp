/**
 * Code by nhatdang2604
 *
 * https://github.com/nhatdang2604
 */
#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<random>
#include<chrono>
#include<vector>
// #include<thread>

#define OUTFILE "result.csv"

const int N_MAX = 100000;
const int M = 1;


//const int N_MAX = 100;
//const int M = 100;
//int arr[N_MAX + 10];
FILE* fptr = fopen(OUTFILE, "w");
double value[N_MAX + 10];
int count = N_MAX;

std::random_device rDevice;
std::mt19937 gen(rDevice());

inline void generateArray(int size, int*& arr)
{
	std::uniform_int_distribution<int> uDistribution(0, size - 1);
	for (int i = 0; i < size; ++i) {
		arr[i] = uDistribution(gen);
	}
}

inline int countCompareOperatorOfMax(int size, int*& arr)
{
	int max = arr[0];
	int res = 0;
	for (int i = 1; i < size; ++i) {
		if (max < arr[i]) {
			max = arr[i];
			++res;
		}
	}

	return res;
}

void countInASize(int size) {
	long long average = 0;
	int* arr = new int[size + 1];
	for (int j = 1; j <= M; ++j) {
		generateArray(size, arr);
		average += countCompareOperatorOfMax(size, arr);
	}
	delete[]arr;
	value[size] = (double)average / M;
	--count;
	printf("Number of situations remain: %d (n = %d finished)\n", count, size);
}

void run() {
	// std::vector<std::thread> threads;
	// for (int i = N_MAX; i >= 1; --i) {
	// 	threads.emplace_back(countInASize, i);
	// }

  for (int i = N_MAX; i >= 1; --i) {
    countInASize(i);
  }

	//Write the column names
	fprintf(fptr, "\"N\",\"Average of comparations\"\n");

	//Write data to result.csv
	for (int i = 1; i <= N_MAX; ++i) {
		fprintf(fptr, "%d,%f\n", i, value[i]);
	}

	//Complete log
	fclose(fptr);
	printf("Completed 100%%\n");
	return;
}

int main() {

	/*
	auto start = std::chrono::high_resolution_clock::now();
	startCount();
	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
	std::cout << "Process finish in: " << (double)duration.count()/(1000000) << " seconds" << std::endl;
	*/

	auto start = std::chrono::high_resolution_clock::now();

	run();

	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
	printf("Process finish in: %lf seconds\n", (double)duration.count() / (1000000));

	return 0;
}
