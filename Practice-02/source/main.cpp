/**
 * Code by Tran Hoang Quan - 19120338
 *
 * https://github.com/trhgquan
 */

#include<iostream>
#include<chrono>

#define longint int64_t

/**
 * Counters
 *
 */
longint __total_assign = 0;
longint __total_compare = 0;

/**
 * Recursive Fibonacci calculation
 * @param  n
 * @return   nth-fibonacci
 */
longint recursive_fibonacci(longint n) {
  if (++__total_compare && n <= 1) {
    return 1;
  }

  return recursive_fibonacci(n - 1) + recursive_fibonacci(n - 2);
}

/**
 * Iterative Fibonacci calculation
 * @param  n
 * @return   n-th fibonacci
 */
longint iterative_fibonacci(longint n) {
  if (++__total_compare && n <= 1) {
    return 1;
  }

  longint last, nextToLast, res; last = nextToLast = res = 1;
  __total_assign += 3;

  // Because 1 assign created at the loop's start
  __total_assign += 1;

  for (int i = 2; ++__total_compare && i <= n; ++i && ++__total_assign) {
    res = last + nextToLast;
    nextToLast = last;
    last = res;

    __total_assign += 3;
  }

  return res;
}

int main() {
  freopen("input.inp", "r+", stdin);

  std::chrono::steady_clock clock;
  auto start = clock.now();
  //-----------------------------------------------------
  int t; std::cin >> t;
  while (t--) {
    longint n; std::cin >> n;

    // BỎ COMMENT DÒNG NÀY ĐỂ CHẠY THUẬT TOÁN ĐỆ QUY
    // longint res = recursive_fibonacci(n);

    // BỎ COMMENT DÒNG NÀY ĐỂ CHẠY THUẬT TOÁN KHỬ ĐỆ QUY
    longint res = iterative_fibonacci(n);


    std::cout << res << ' '
              << __total_assign << ' '
              << __total_compare << '\n';

    __total_assign = __total_compare = 0;
  }
  //-----------------------------------------------------
  auto end = clock.now();
  std::chrono::duration<double> diff = end - start;
  std::cout << "----------------" << '\n';
  std::cout << "Execution time: " << diff.count() << '\n';
  return 0;
}
