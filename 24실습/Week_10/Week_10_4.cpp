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

    int P() {
        return arr[1];
    }

    void removeP() {
        cout << arr[1] << ' ';
        swap(1, size());
        arr.pop_back();
        downHeap(1);
    }

    bool condition(int temp, int comp) {
        if (arr[temp] % 2 == 1 && arr[comp] % 2 == 1) {
            if (arr[temp] < arr[comp]) {
                return true;
            }
        }

        else if (arr[temp] % 2 == 1 && arr[comp] % 2 == 0) {
            return true;
        }

        /*else if (arr[temp] % 2 == 0 && arr[comp] % 2 == 1) {
            
        }*/

        else if (arr[temp] % 2 == 0 && arr[comp] % 2 == 0) {
            if (arr[temp] > arr[comp]) {
                return true;
            }
        }

        return false;
    }

    void upHeap(int idx) {
        if (idx == 1) {
            return;
        }

        int par = idx / 2;

        if (condition(par, idx)) {
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
            if (condition(left, right))
                child = right;

            else
                child = left;
        }

        if (condition(idx, child)) {
            swap(child, idx);
            downHeap(child);
        }
    }
};

int main() {
    int T; cin >> T;

    while (T--) {
        Heap pq;
        int N; cin >> N;

        for (int i = 0; i < N; i++) {
            int num; cin >> num;
            pq.insert(num);
        }

        for (int i = 0; i < N; i++) {
            pq.removeP();
        }
        cout << '\n';
    }
}
