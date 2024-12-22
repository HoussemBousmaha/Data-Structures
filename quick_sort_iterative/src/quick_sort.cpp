
#include "./quick_sort_functions.cpp"

using namespace std;

int main() {
    int n;
    cout << "Enter the size of the array: ";
    cin >> n;

    vector<int> array;

    for (int i = 0; i < n; i++)
        array.push_back(rand());

    const clock_t begin_time = clock();

    qs(array);

    // sort(array.begin(), array.end());

    cout << "\n\ntime taken by the program is : " << float(clock() - begin_time) / CLOCKS_PER_SEC << " seconds\n\n";

    for (int i = 0; i < array.size(); i++)
        cout << array[i] << "|";

    return 0;
}
