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
        return arr[1];
    }

    void removeMax() {
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

    bool condition(int p) {
        for (int i = 1; i <= size(); i++) {
            if (arr[i] > p) {
                return false;
            }
        }

        return true;
    }

    bool exception_condition(int p) {
        return ((size() <= 2) && (max() > p));
    }

    void preorder_traversal(int e) {
        if (e > size()) {
            return;
        }

        cout << arr[e] << ' ';

        preorder_traversal(2 * e);
        preorder_traversal(2 * e + 1);
    }
};

int main() {
    int T; cin >> T;

    while (T--) {
        Heap pq;
        int n, p; cin >> n >> p;

        for (int i = 0; i < n; i++) {
            int k; cin >> k;
            pq.insert(k);
        }

        bool flag_exception = false;
        int cnt = 0;

        while (!pq.condition(p)) {
            int first, second, third;

            first = pq.max(); pq.removeMax();
            second = pq.max(); pq.removeMax();
            third = pq.max(); pq.removeMax();

            int temp = (first + third) / 2;
            pq.insert(temp);
            cnt++;

            if (pq.exception_condition(p)) {
                flag_exception = true;
                break;
            }
        }

        if (flag_exception) {
            cout << "False\n";

        }

        else {
            cout << cnt << '\n';
            pq.preorder_traversal(1);
            cout << '\n';
        }
    }
}
