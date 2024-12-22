#include <iostream>
#include <vector>

#include "heap_draw.cpp"
#include "heap_functions.hpp"

using namespace std;

void read_array(vector<int> &array, int n) {
    for (int i = 0; i < n; i++) {
        int data;
        data = rand() % 20;
        // cin >> data;
        array.push_back(data);
    }
}

void output_heap(vector<int> heap) {
    cout << endl << '|';
    for (int i = 0; i < heap.size(); i++) {
        cout << heap[i] << '|';
    }
}

void heapify(vector<int> &heap, int i, int heapsize) // also called sift_up
{
    int N = heapsize;
    int smallest = i;  // Initialize smallest as root
    int l = 2 * i + 1; // left = 2*i + 1
    int r = 2 * i + 2; // right = 2*i + 2

    // If left child is larger than root
    if (l < N && heap[l] <= heap[smallest])
        smallest = l;

    // If right child is larger than smallest so far
    if (r < N && heap[r] <= heap[smallest])
        smallest = r;

    // If smallest is not root
    if (smallest != i) {
        swap(heap[i], heap[smallest]);

        // Recursively heapify the affected sub-tree
        heapify(heap, smallest, heapsize);
    }
}

void build_heap(vector<int> &heap) {
    for (int i = heap.size() / 2 - 1; i >= 0; i--) {
        heapify(heap, i, heap.size());
    }
}

void insert_heap(vector<int> &heap, int data) {
    heap.push_back(data);
    int data_index = heap.size() - 1;

    int parent_index = (data_index - 1) / 2;

    while (heap[data_index] > heap[parent_index]) {
        int tmp = heap[data_index];
        heap[data_index] = heap[parent_index];
        heap[parent_index] = tmp;

        data_index = parent_index;
        parent_index = (data_index - 1) / 2;
    }
}

int delete_heap(vector<int> &heap) {
    int ans = heap[0];

    heap[0] = heap[heap.size() - 1];
    heap.erase(heap.end() - 1);

    heapify(heap, 0, heap.size());

    return ans;
}

void del_heap(vector<int> &heap, int data) {
    for (int i = 0; i < heap.size(); i++) {
        if (heap[i] == data) {
            heap[i] = heap[heap.size() - 1];
            heap.erase(heap.end() - 1);
            heapify(heap, i, heap.size());
            return;
        }
    }
}

void heap_sort(vector<int> &array) {

    build_heap(array);

    int heapsize = array.size();

    for (int i = 0; i < array.size(); i++) {
        // replace the smallest element (root) with the last element in level_order
        int tmp = array[0];
        array[0] = array[heapsize - 1];
        // recover the heap property from the new root
        heapify(array, 0, heapsize);

        // save the smallest element at the end of the heap
        array[heapsize - 1] = tmp;

        // decrement the virtual size of the heap
        heapsize--;
    }
}
