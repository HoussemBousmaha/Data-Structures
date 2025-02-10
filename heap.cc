#include <iostream>

using namespace std;

void Draw_Heap(vector<int> tree);
void dessinArbre(vector<int> tree, int index, FILE *f, int *nbNil, int treesize);
void read_array(vector<int> &array, int n);
void output_heap(vector<int> heap);
void heapify(vector<int> &heap, int i, int heapsize);
void build_heap(vector<int> &heap);
void insert_heap(vector<int> &heap, int data);
int delete_heap(vector<int> &heap);
void del_heap(vector<int> &heap, int data);
void heap_sort(vector<int> &array);

void Draw_Heap(vector<int> tree, int *sortie) {

    int nbNil;
    char file_path[20];
    FILE *f;

    if (tree.size() == 0)
        cout << "> ERREUR : Arbre vide !";
    else {
        snprintf(file_path, sizeof(file_path), "out%d.dot", *sortie);
        f = fopen(file_path, "w");
        fprintf(f, "graph arbre {\n");
        fprintf(f, "\tordering = out;\n");
        fprintf(f, "\tsplines = false;\n");

        nbNil = 0;

        dessinArbre(tree, 0, f, &nbNil, tree.size());
        fprintf(f, "}\n");
        fclose(f);

        (*sortie)++;

        // printf("\n\n>> L'arbre est dessine correctement !\n\n");
    }
}

void dessinArbre(vector<int> tree, int index, FILE *f, int *nbNil, int treesize) {
    int info, info_fg, info_fd;
    if (index < treesize) {
        info = tree[index];
        // Dessiner un arc vers le fils gauche
        if (2 * index + 1 < treesize) {

            info_fg = tree[2 * index + 1];
            fprintf(f, "  \"{%d, %d}\" -- \"{%d, %d}\" \n", info, index, info_fg, 2 * index + 1);
        } else {
            fprintf(f, "  \"NIL%d\" [style=invis];\n", *nbNil);
            fprintf(f, "  \"{%d, %d}\" -- \"NIL%d\" ", info, index, (*nbNil)++);
            fprintf(f, " [style=invis];\n");
        }

        // Dessiner un fils NIL virtuel et invisible au milieu (pour une meilleure s�paration des fils gauches et
        // droits)
        fprintf(f, "  \"NIL%d\" [style=invis];\n", *nbNil);
        fprintf(f, "  \"{%d, %d}\" -- \"NIL%d\" ", info, index, (*nbNil)++);
        fprintf(f, " [style=invis];\n");

        // Dessiner un arc vers le fils droit
        if (2 * index + 2 < treesize) {
            info_fd = tree[2 * index + 2];
            fprintf(f, "  \"{%d, %d}\" -- \"{%d, %d}\" \n", info, index, info_fd, 2 * index + 2);
        } else {
            fprintf(f, "  \"NIL%d\" [style=invis];\n", *nbNil);
            fprintf(f, "  \"{%d, %d}\" -- \"NIL%d\" ", info, index, (*nbNil)++);
            fprintf(f, " [style=invis];\n");
        }

        // Dessiner les sous-arbres gauche et droit
        dessinArbre(tree, 2 * index + 1, f, nbNil, treesize);
        dessinArbre(tree, 2 * index + 2, f, nbNil, treesize);
    }
}

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
    for (size_t i = 0; i < heap.size(); i++) {
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
    for (size_t i = 0; i < heap.size(); i++) {
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

    for (size_t i = 0; i < array.size(); i++) {
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

int main() {
    srand(time(nullptr));
    int n, sortie = 1;

    cout << "Number of elements: ";
    cin >> n;

    vector<int> heap;

    read_array(heap, n);

    const clock_t begin_time = clock();

    build_heap(heap);
    Draw_Heap(heap, &sortie);
    cout << "\n\n" << float(clock() - begin_time) / CLOCKS_PER_SEC << endl;

    return 0;
}
