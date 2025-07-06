#ifndef SORT_H
#define SORT_H

#include <vector>
#include <algorithm>
#include <limits>
#include <type_traits>

// Bubble Sort
template <typename T>
void bubbleSort(std::vector<T>& arr) {
    bool swapped;
    for (size_t i = 0; i < arr.size(); ++i) {
        swapped = false;
        for (size_t j = 1; j < arr.size() - i; ++j) {
            if (arr[j - 1] > arr[j]) {
                std::swap(arr[j - 1], arr[j]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

// Radix Sort (for non-negative integers)
template <typename T>
typename std::enable_if<std::is_integral<T>::value && std::is_unsigned<T>::value, void>::type
radixSort(std::vector<T>& arr) {
    if (arr.empty()) return;
    const size_t base = 256;
    std::vector<T> output(arr.size());
    for (size_t shift = 0; shift < sizeof(T) * 8; shift += 8) {
        size_t count[base] = {0};
        for (const auto& num : arr)
            ++count[(num >> shift) & 0xFF];
        for (size_t i = 1; i < base; ++i)
            count[i] += count[i - 1];
        for (ptrdiff_t i = arr.size() - 1; i >= 0; --i)
            output[--count[(arr[i] >> shift) & 0xFF]] = arr[i];
        arr = output;
    }
}

// Merge Sort
template <typename T>
void merge(std::vector<T>& arr, size_t left, size_t mid, size_t right) {
    size_t n1 = mid - left + 1;
    size_t n2 = right - mid;
    std::vector<T> L(n1), R(n2);
    for (size_t i = 0; i < n1; ++i)
        L[i] = arr[left + i];
    for (size_t j = 0; j < n2; ++j)
        R[j] = arr[mid + 1 + j];
    size_t i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }
    while (i < n1)
        arr[k++] = L[i++];
    while (j < n2)
        arr[k++] = R[j++];
}

template <typename T>
void mergeSortHelper(std::vector<T>& arr, size_t left, size_t right) {
    if (left < right) {
        size_t mid = left + (right - left) / 2;
        mergeSortHelper(arr, left, mid);
        mergeSortHelper(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

template <typename T>
void mergeSort(std::vector<T>& arr) {
    if (!arr.empty())
        mergeSortHelper(arr, 0, arr.size() - 1);
}

/*
 * Leap Sort: A variant of Shell Sort using a leap (gap) sequence.
 * This implementation uses Shell's original gap sequence (n/2, n/4, ..., 1).
 */
template <typename T>
void leapSort(std::vector<T>& arr) {
    size_t n = arr.size();
    for (size_t gap = n / 2; gap > 0; gap /= 2) {
        for (size_t i = gap; i < n; ++i) {
            T temp = arr[i];
            size_t j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}
#endif // SORT_H