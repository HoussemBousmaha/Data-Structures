using namespace std;

void read_array(vector<int> &array, int n);
void output_heap(vector<int> heap);
void heapify(vector<int> &heap, int i, int heapsize); // sift_up (recover the heap property at a given index i)
void build_heap(vector<int> &heap);                   // takes O(n)
void insert_heap(vector<int> &heap, int data);
int delete_heap(vector<int> &heap);
void del_heap(vector<int> &heap, int data);
void heap_sort(vector<int> &array);
