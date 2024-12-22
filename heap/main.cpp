#include "heap_functions.cpp"

using namespace std;

int main() {
    srand(time(nullptr));
    int n, sortie = 1;

    cout << "Number of elements: ";
    cin >> n;

    vector<int> heap;

    read_array(heap, n);

    const clock_t begin_time = clock();

    // Draw_Heap(heap, &sortie);
    // output_heap(heap);
    build_heap(heap);
    Draw_Heap(heap, &sortie);

    // output_heap(heap);

    // heap_sort(heap);
    // Draw_Heap(heap, &sortie);

    // output_heap(heap);

    cout << "\n\n" << float(clock() - begin_time) / CLOCKS_PER_SEC << endl;

    return 0;
}
