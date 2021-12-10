/**
 * @file main.cpp
 * @author @trhgquan - https://github.com/trhgquan
 * @date 2021-12-10
 */

#include<iostream>
#include"Fenwick.h"
using namespace std;

int main() {
    int a[] = {2, 1, 4, 3, 5};

    cout << inversionCount<int>(a, 5) << endl;
    return 0;
}