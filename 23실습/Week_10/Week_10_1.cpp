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

    int min() {
        if (empty()) {
            return -1;
        }

        return arr[1];
    }

    void removeMin() {
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
        if (arr[par] > arr[idx]) {
            swap(par, idx);
            upHeap(par);
        }
    }

    void downHeap(int idx) {
        int left = 2 * idx; int right = 2 * idx + 1;
        int child;

        if (left > size()) {    // 자식 존재 x
            return;
        }

        else if (left == size()) {    // 왼쪽 자식만 존재
            child = left;
        }

        else {    // 두 자식 모두 존재 - 둘 비교해서 더 작은 자식 선택
            if (arr[left] <= arr[right])
                child = left;

            else
                child = right;
        }

        if (arr[child] < arr[idx]) {
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
            pq.removeMin();
        }

        else if (cmd == "top") {
            cout << pq.min() << '\n';
        }

        else if (cmd == "print") {
            pq.print();
        }
    }
}
