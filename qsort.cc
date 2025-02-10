#include <iostream>
#include <stack>
#include <vector>

using namespace std;

pair<pair<int, int>, pair<int, int>> partition(vector<int> &array, int l, int r) {
    bool j_turn = true;
    int i = l, j = r;

    while (i < j) {
        while (array[i] < array[j]) {
            if (j_turn) {
                j--;
            } else {
                i++;
            }
        }

        int tmp = array[i];
        array[i] = array[j];
        array[j] = tmp;

        j_turn = !j_turn;
    }

    pair<pair<int, int>, pair<int, int>> boundries;

    if (j_turn) {
        boundries.first.first = l;
        boundries.first.second = j - 1;
        boundries.second.first = j + 1;
        boundries.second.second = r;
    } else {
        boundries.first.first = l;
        boundries.first.second = i - 1;
        boundries.second.first = i + 1;
        boundries.second.second = r;
    }

    return boundries;
}

void qs(vector<int> &arr) {
    stack<pair<int, int>> stack;

    pair<int, int> initial;

    initial.first = 0;
    initial.second = arr.size() - 1;
    stack.push(initial);

    int l, r;

    pair<pair<int, int>, pair<int, int>> boundries;

    do {
        l = stack.top().first;
        r = stack.top().second;
        stack.pop();

        while (r > l) {
            boundries = partition(arr, l, r);

            if (boundries.first.second - boundries.first.first > boundries.second.second - boundries.second.first) {
                stack.push(boundries.first);
                l = boundries.second.first;
                r = boundries.second.second;
            } else {
                stack.push(boundries.second);
                l = boundries.first.first;
                r = boundries.first.second;
            }
        }
    } while (stack.empty() == false);
}

int main() {
    int n;
    cout << "Enter the size of the array: ";
    cin >> n;

    vector<int> array;

    for (int i = 0; i < n; i++)
        array.push_back(rand());

    const clock_t begin_time = clock();

    qs(array);

    cout << "sorting took: " << float(clock() - begin_time) / CLOCKS_PER_SEC << " seconds" << endl;

    // for (int i = 0; i < array.size(); i++) {
    //     cout << array[i] << "|";
    // }

    return 0;
}
