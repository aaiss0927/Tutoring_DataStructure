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

	void rearNsum(int num) {
		if (empty()) {
			cout << "Empty\n";
			return;
		}

		if (num > s) {
			cout << "error\n";
			return;
		}

		int sum = 0;
		int idx;

		if (r != 0) {
			idx = r - 1;
		}

		else {
			idx = capacity - 1;
		}

		while (num--) {
			sum += arr[idx];

			if (idx != 0) {
				idx--;
			}

			else {
				idx = capacity - 1;
			}
		}

		cout << sum << '\n';
	}
};

int main() {
	int N, T; cin >> N >> T;
	arrayQueue aq(N);

	while (T--) {
		string cmd; cin >> cmd;

		if (cmd == "size") {
			cout << aq.size() << '\n';
		}

		else if (cmd == "isEmpty") {
			string result;
			result = aq.empty() ? "True" : "False";
			cout << result << '\n';
		}

		else if (cmd == "full") {
			string result;
			result = aq.full() ? "True" : "False";
			cout << result << '\n';
		}

		else if (cmd == "front") {
			aq.front();
		}

		else if (cmd == "rearNsum") {
			int num; cin >> num;
			aq.rearNsum(num);
		}

		else if (cmd == "enqueue") {
			int value; cin >> value;
			aq.enqueue(value);
		}

		else if (cmd == "dequeue") {
			aq.dequeue();
		}
	}
}
