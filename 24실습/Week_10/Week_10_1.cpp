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

    void swap(int idx1, int idx2) {
        arr[0] = arr[idx1];
        arr[idx1] = arr[idx2];
        arr[idx2] = arr[0];
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

        if (left > size())    // 자식 존재 x
            return;

        else if (left == size())    // 왼쪽 자식만 존재
            child = left;

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

    void second_top() {
        if (size() < 2) {
            cout << "Error\n";
            return;
        }

        if (size() == 2) {
            cout << arr[2] << '\n';
            return;
        }

        int result = (arr[2] < arr[3]) ? arr[2] : arr[3];
        cout << result << '\n';
    }
};

int main() {
    Heap pq;
    int T; cin >> T;

    while (T--) {
        string cmd; cin >> cmd;

        if (cmd == "push") {
            int i; cin >> i;
            pq.insert(i);
        }

        else if (cmd == "size") {
            cout << pq.size() << '\n';
        }

        else if (cmd == "empty") {
            cout << pq.empty() << '\n';
        }

        else if (cmd == "pop") {
            pq.removeMin();
        }

        else if (cmd == "top") {
            cout << pq.min() << '\n';
        }

        else if (cmd == "second_top") {
            pq.second_top();
        }
    }
}
