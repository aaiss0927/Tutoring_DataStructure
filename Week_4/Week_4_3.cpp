#include <iostream>
using namespace std;

class arrayQueue {
private:
	int* arr;
	int capacity;
	int f;
	int r;
	int s;

public:
	arrayQueue(int capacity) {
		this->capacity = capacity;
		arr = new int[capacity];
		f = r = 0;
		s = 0;
	}

	bool empty() {
		return (s == 0);
	}

	bool full() {
		return (s == capacity);
	}

	int size() {
		return s;
	}

	void front() {
		if (empty()) {
			cout << "Empty\n";
			return;
		}

		cout << arr[f] << '\n';
	}

	void rear() {
		if (empty()) {
			cout << "Empty\n";
			return;
		}

		if (r == 0) {
			cout << arr[capacity - 1] << '\n';
			return;
		}

		cout << arr[r - 1] << '\n';
	}

	void enqueue(int value) {
		if (full()) {
			cout << "Full\n";
			return;
		}

		arr[r] = value;

		r = (r + 1) % capacity;
		s++;
	}

	void dequeue() {
		if (empty()) {
			cout << "Empty\n";
			return;
		}

		cout << arr[f] << '\n';

		f = (f + 1) % capacity;
		s--;
	}
};

int main() {
	int N, T;
	cin >> N >> T;
	arrayQueue Q(N);

	while (T--) {
		string cmd; cin >> cmd;

		if (cmd == "size") {
			cout << Q.size() << '\n';
		}

		else if (cmd == "isEmpty") {
			if (Q.empty()) {
				cout << "True\n";
			}
			else {
				cout << "False\n";
			}
		}

		else if (cmd == "full") {
			if (Q.full()) {
				cout << "True\n";
			}
			else {
				cout << "False\n";
			}
		}

		else if (cmd == "front") {
			Q.front();
		}

		else if (cmd == "rear") {
			Q.rear();
		}

		else if (cmd == "enqueue") {
			int x; cin >> x;
			Q.enqueue(x);
		}

		else if (cmd == "dequeue") {
			Q.dequeue();
		}
	}
}
