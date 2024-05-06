#include <iostream>
#include <vector>
using namespace std;

class Heap {
private:
    vector<int> arr;

public:
    Heap() {
        arr.push_back(0);
    }

    int size() {
        return arr.size() - 1;
    }

    bool empty() {
        return (arr.size() - 1 == 0);
    }

    void swap(int idx1, int idx2) {
        arr[0] = arr[idx1];
        arr[idx1] = arr[idx2];
        arr[idx2] = arr[0];
    }

    void insert(int e) {
        arr.push_back(e);
        upHeap(size());
    }

    int max() {
        if (empty()) {
            return -1;
        }

        return arr[1];
    }

    void removeMax() {
        if (empty()) {
            cout << "-1\n";
            return;
        }

        cout << arr[1] << '\n';
        swap(1, size());
        arr.pop_back();
        downHeap(1);
    }

    void upHeap(int idx) {
        if (idx == 1) {
            return;
        }

        int par = idx / 2;
        if (arr[par] < arr[idx]) {
            swap(par, idx);
            upHeap(par);
        }
    }

    void downHeap(int idx) {
        int left = 2 * idx; int right = 2 * idx + 1;
        int child;

        if (left > size()) {
            return;
        }

        else if (left == size()) {
            child = left;
        }

        else {
            if (arr[left] >= arr[right])
                child = left;

            else
                child = right;
        }

        if (arr[child] > arr[idx]) {
            swap(child, idx);
            downHeap(child);
        }
    }

    void print() {
        if (empty()) {
            cout << "-1\n";
            return;
        }

        for (int i = 1; i <= size(); i++) {
            cout << arr[i] << ' ';
        }
        
        cout << '\n';
    }
};

int main() {
    Heap pq;
    int T; cin >> T;

    while (T--) {
        string cmd; cin >> cmd;

        if (cmd == "insert") {
            int i; cin >> i;
            pq.insert(i);
        }

        else if (cmd == "size") {
            cout << pq.size() << '\n';
        }

        else if (cmd == "isEmpty") {
            cout << pq.empty() << '\n';
        }

        else if (cmd == "pop") {
            pq.removeMax();
        }

        else if (cmd == "top") {
            cout << pq.max() << '\n';
        }

        else if (cmd == "print") {
            pq.print();
        }
    }
}
