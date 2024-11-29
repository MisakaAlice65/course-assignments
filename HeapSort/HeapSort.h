#ifndef HEAPSORT_H
#define HEAPSORT_H

#include <vector>
#include <algorithm>    

template <typename T>
//在堆排序过程中，当将堆顶元素与堆的最后一个元素交换位置后，堆的大小减小了，此时需要重新调整堆的结构，确保堆的性质仍然成立

//构建heapify————比较父节点与子节点的大小，并根据需要交换节点，直到堆的结构恢复正常。
void heapify(std::vector<T>& vec, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;   
    int right = 2 * i + 2;  


    if (left < n && vec[left] > vec[largest]) {
        largest = left;
    }


    if (right < n && vec[right] > vec[largest]) {
        largest = right;
    }


    if (largest != i) {
        std::swap(vec[i], vec[largest]);
        heapify(vec, n, largest);
    }
}

template <typename T>
void heapSort(std::vector<T>& vec) {
    int n = vec.size();

    // Build a max heap  构建一个最大堆
    for (int i = n / 2 - 1; i >= 0; --i) {
        heapify(vec, n, i);
    }

    // One by one extract elements from heap 从堆里面逐个取出
    for (int i = n - 1; i > 0; --i) {
        std::swap(vec[0], vec[i]); // Move current root to end 当前根节点移动到末尾
        heapify(vec, i, 0);         // 比较大小，并调整堆
    }
}

#endif
