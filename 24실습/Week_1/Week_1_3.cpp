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

	void sum() {
		int temp = 0;

		for (int i = 0; i < s; i++) {
			temp += arr[i];
		}

		cout << temp << '\n';
	}
};

int main() {
	int T, N; cin >> T >> N;
	Array a(N);

	while (T--) {
		string cmd; cin >> cmd;

		if (cmd == "at") {
			int i; cin >> i;
			cout << a.at(i) << '\n';
		}

		else if (cmd == "add") {
			int i, z; cin >> i >> z;
			a.add(i, z);
		}

		else if (cmd == "remove") {
			int i; cin >> i;
			a.remove(i);
		}

		else if (cmd == "set") {
			int i, z; cin >> i >> z;
			a.set(i, z);
		}

		else if (cmd == "sum") {
			a.sum();
		}

		else if (cmd == "print") {
			a.print();
		}
	}
}
