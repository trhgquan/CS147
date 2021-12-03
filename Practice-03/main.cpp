/**
 * @file main.cpp
 * @author trhgquan https://github.com/trhgquan
 * @date 2021-12-03
 */

#include<bits/stdc++.h>
#define longint int64_t
using namespace std;

template<class T>
class RandomGenerator {
private:
    bool _seed = false;

public:
    /**
     * @brief Genereate a random T-type.
     * 
     * @return T 
     */
    T randomInt() {
        if (!_seed) {
            srand(time(NULL));
            _seed = true;
        }

        return rand();
    }

    /**
     * @brief Generate a random T-type in range [0, right - 1]
     * 
     * @param right Right edge of the interval [0, n)
     * @return T 
     */
    T randomInt(T right) {
        return randomInt() % right;
    }

    /**
     * @brief Generate a random T-type in range [left, right]
     * 
     * @param left Left edge
     * @param right Right edge
     * @return T 
     */
    T randomInt(T left, T right) {
        return (randomInt() % (left - right + 1)) + left;
    }
};

class Testing {
private:
    RandomGenerator<longint> _rng;
    longint _totalSamples;
    longint _maxValue;
    longint _sampleSize;
    map<longint, double> _table;

private:
    /**
     * @brief Expected value of _table.
     * 
     * @return double 
     */
    double _E() {
        double expected_value = 0;
        for (auto i : table()) {
            expected_value += i.first * i.second;
        }
        return expected_value;
    }

    /**
     * @brief Testing samples.
     * 
     */
    void sample_test() {
        longint* array = new longint[_sampleSize];

        // For unique element.
        bool* existed = new bool[_maxValue];
        memset(existed, 0, _maxValue * sizeof(bool));

        // Create random array
        for (int i = 0; i < _sampleSize; ++i) {
            longint value = _rng.randomInt(_maxValue);
            while (existed[value]) {
                value = _rng.randomInt(_maxValue);
            }
            existed[value] = 1;
            array[i] = value;
        }

        // bool unsorted = false;
        longint count = 0; // Counting number of loop
        for (int i = 0; i < _sampleSize - 1; ++i) {
            ++count;
            if (array[i] > array[i + 1]) {
                // unsorted = true;
                break;
            }
        }

        _table[count]++;

        delete[] array;
        delete[] existed;
    }

public:
    /**
     * @brief Construct a new Testing object
     * 
     * @param totalSamples 
     * @param sampleSize 
     * @param maxValue 
     */
    Testing(longint totalSamples, longint sampleSize, longint maxValue) {
        if (sampleSize > maxValue) {
            throw "maxValue should be greater or equals sampleSize";
        }

        _totalSamples = totalSamples;
        _maxValue = maxValue;
        _sampleSize = sampleSize;

        // Perform test.
        for (int i = 0; i < _totalSamples; ++i) {
            cout << "Testing " << i + 1 << endl;
            sample_test();
        }
    }

    double E() {
        return _E();
    }

    /**
     * @brief Transform probability _table with counts to frequency.
     * 
     * @return map<longint, double> 
     */
    map<longint, double> table() {
        map<longint, double> table;

        for (auto i : _table) {
            table[i.first] = i.second / _totalSamples;
        }

        return table;
    }
};

int main() {

    // This code took a very-long time to finished.

    try {
        Testing a(1000000, 10, 10);
            
        cout << "Probability distribution (X f):" << endl; 

        for (auto i : a.table()) {
            cout << i.first << ' ' << i.second << endl;
        }

        cout << "Expected value = " << a.E() << endl;
    } catch (const exception& e) {
        cout << e.what() << endl;
    }
    

    return 0;
}