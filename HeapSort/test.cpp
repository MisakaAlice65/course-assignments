#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <cassert>
#include "HeapSort.h"

// 使用check检查排序的正确性
template <typename T>
bool check(const std::vector<T>& vec) {
    for (size_t i = 1; i < vec.size(); ++i) {
        if (vec[i] < vec[i - 1]) {
            return false; 
        }
    }
    return true;
}

// 生成随机序列
std::vector<int> generateRandomSequence(size_t size) {
    std::vector<int> vec(size);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 1000000);

    for (auto& elem : vec) {
        elem = dis(gen);
    }
    return vec;
}

// 生成有序序列
std::vector<int> generateOrderedSequence(size_t size) {
    std::vector<int> vec(size);
    for (size_t i = 0; i < size; ++i) {
        vec[i] = i;
    }
    return vec;
}

// 生成逆序序列
std::vector<int> generateReversedSequence(size_t size) {
    std::vector<int> vec(size);
    for (size_t i = 0; i < size; ++i) {
        vec[i] = size - i;
    }
    return vec;
}

// 生成部分重复序列
std::vector<int> generatePartiallyRepeatedSequence(size_t size) {
    std::vector<int> vec(size);
    for (size_t i = 0; i < size; ++i) {
        vec[i] = i % 100; // 这一步重复 0 到 99 的元素
    }
    return vec;
}

int main() {
    const size_t TEST_SIZE = 1000000;

    std::vector<std::string> testNames = {
        "Random Sequence",
        "Ordered Sequence",
        "Reversed Sequence",
        "Partially Repeated Sequence"
    };


    std::vector<std::vector<int>(*)(size_t)> testGenerators = {
        generateRandomSequence,
        generateOrderedSequence,
        generateReversedSequence,
        generatePartiallyRepeatedSequence
    };

    // 遍历
    for (size_t i = 0; i < testNames.size(); ++i) {
        std::cout << testNames[i]  << "\n";

        // 生成测试用例
        std::vector<int> vec = testGenerators[i](TEST_SIZE);
        std::vector<int> vecHeap = vec; 

        // 使用自定义堆排序
        auto start = std::chrono::high_resolution_clock::now();
        heapSort(vec);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> heapSortTime = end - start;

        // 检查
        assert(check(vec) && "HeapSort failed!");

        // 输出堆排序所用时长
        std::cout << "My HeapSort time: " << heapSortTime.count() << " seconds\n";

        // 使用 std::sort_heap
        start = std::chrono::high_resolution_clock::now();
        std::make_heap(vecHeap.begin(), vecHeap.end());
        std::sort_heap(vecHeap.begin(), vecHeap.end());
        end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> sortHeapTime = end - start;

        // 检查排序结果
        assert(check(vecHeap) && "std::sort_heap failed!");

        // 输出 std::sort_heap 所用时长
        std::cout << "std::sort_heap time: " << sortHeapTime.count() << " seconds\n";

        std::cout << "\n---✩ ✫ ✬ ✭ ✮ ✡-----------------------✩ ✫ ✬ ✭ ✮ ✡-----happy ending~\n\n";
    }

    return 0;
}
