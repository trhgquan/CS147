/**
 * @file Fenwick.h
 * @author @trhgquan - https://github.com/trhgquan
 * @date 2021-12-10
 */

/**
 * @brief Implementation of Fenwick tree.
 * 
 * @tparam T 
 */
template<class T>
class Fenwick {
private:
    T* _f;
    int _size;

public:
    /**
     * @brief Construct a new Fenwick object
     * 
     * @param size 
     */
    Fenwick(int size) {
        _f = new T[size + 1]();

        _size = size;
    }

    /**
     * @brief Construct a new Fenwick object
     * 
     * @param arr 
     * @param size 
     */
    Fenwick(const T* arr, int size) {
        _f = new T[size + 1]();

        _size = size;

        for (int i = 0; i < _size; ++i) {
            update(i + 1, arr[i]);
        }
    }

    /**
     * @brief Destroy the Fenwick object
     * 
     */
    ~Fenwick() {
        delete[] _f;
    }
public:
    /**
     * @brief Update Fenwick tree at index i.
     * 
     * @param i 
     * @param value 
     */
    void update(int i, T value) {
        for (; i < _size; i += (i & -i)) {
            _f[i] += value;
        }
    }

    /**
     * @brief Query for sum in range [1, i]
     * 
     * @param i 
     * @return T 
     */
    T query(int i) {
        T res = 0;
        for (; i > 0; i -= (i & -i)) {
            res += _f[i];
        }
        return res;
    }

    /**
     * @brief Query for sum in range [left, right]
     * 
     * @param left 
     * @param right 
     * @return T 
     */
    T sumRange(int left, int right) {
        return query(right) - query(left - 1);
    }
};

/**
 * @brief Counting inversions in an array.
 * 
 * @tparam T datatype of the array.
 * @param a Pointer to the array.
 * @param n Total elements of the array.
 * @return int Number of inversions in the array.
 */
template<class T>
int inversionCount(const T* a, int n) {
    T maxElement = -1;
    for (int i = 0; i < n; ++i) {
        maxElement = (maxElement > a[i]) ? maxElement : a[i];
    }

    Fenwick<T> f(maxElement);
    int inversions = 0;

    for (int i = n - 1; i >= 0; --i) {
        inversions += f.query(a[i] - 1);
        f.update(a[i], 1);
    }

    return inversions;
}