#include <iostream>
using namespace std;

class Array {
private:
	int* arr;
	int s;

public:
	Array(int s) {
		this->s = s;
		this->arr = new int[s];

		for (int i = 0; i < s; i++) {
			arr[i] = 0;
		}
	}

	int at(int idx) {
		return arr[idx];
	}

	void add(int idx, int value) {
		for (int i = s - 2; i >= idx; i--) {
			arr[i + 1] = arr[i];
		}

		arr[idx] = value;
	}

	void set(int idx, int value) {
		arr[idx] = value;
	}

	void print() {
		for (int i = 0; i < s; i++) {
			cout << arr[i] << ' ';
		}
		cout << '\n';
	}

	void remove(int idx) {
		for (int i = idx + 1; i < s; i++) {
			arr[i - 1] = arr[i];
		}

		arr[s - 1] = 0;
	}

	void shift(int s, int e) {
		int temp = arr[e];

		for (int i = e; i >= s + 1; i--) {
			arr[i] = arr[i - 1];
		}

		arr[s] = temp;
	}

	void swap(int i, int j) {
		int temp = arr[i];
		arr[i] = arr[j];
		arr[j] = temp;
	}
};

int main() {
	int T, N; cin >> T >> N;
	Array a(N);

	for (int i = 0; i < N; i++) {
		a.add(i, i);
	}

	while (T--) {
		string cmd; cin >> cmd;

		if (cmd == "shift") {
			int i, j; cin >> i >> j;
			a.shift(i, j);
		}

		else if (cmd == "swap") {
			int i, j; cin >> i >> j;
			a.swap(i, j);
		}

		else if (cmd == "print") {
			a.print();
		}
	}
}
