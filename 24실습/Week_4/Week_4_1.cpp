#include <iostream>
using namespace std;

class Node {
private:
	int value;
	Node* next;

public:
	Node(int value) {
		this->value = value;
		next = nullptr;
	}

	friend class listQueue;
};

class listQueue {
private:
	Node* f;
	Node* r;
	int s;

public:
	listQueue() {
		f = r = nullptr;
		s = 0;
	}

	bool empty() {
		return (s == 0);
	}

	int size() {
		return s;
	}

	void front() {
		if (empty()) {
			cout << "Empty\n";
			return;
		}

		cout << f->value << '\n';
	}

	void rear() {
		if (empty()) {
			cout << "Empty\n";
			return;
		}

		cout << r->value << '\n';
	}

	void enqueue(int value) {
		Node* new_node = new Node(value);

		if (empty()) {
			f = r = new_node;
		}

		else {
			r->next = new_node;
			r = new_node;
		}

		s++;
	}

	void dequeue() {
		if (empty()) {
			cout << "Empty\n";
			return;
		}

		Node* del_node = f;

		if (s == 1) {
			f = r = nullptr;
		}

		else {
			f = f->next;
		}

		cout << del_node->value << '\n';
		delete del_node;
		s--;
	}

	void frontNsum(int num) {
		if (empty()) {
			cout << "Empty\n";
			return;
		}

		if (num > s) {
			cout << "error\n";
			return;
		}

		Node* cur_node = f;
		int sum = 0;

		for (int i = 0; i < num; i++) {
			sum += cur_node->value;
			cur_node = cur_node->next;
		}

		cout << sum << '\n';
	}
};

int main() {
	listQueue lq;
	int T; cin >> T;

	while (T--) {
		string cmd; cin >> cmd;

		if (cmd == "size") {
			cout << lq.size() << '\n';
		}

		else if (cmd == "isEmpty") {
			string result;
			result = lq.empty() ? "True" : "False";
			cout << result << '\n';
		}

		else if (cmd == "frontNsum") {
			int num; cin >> num;
			lq.frontNsum(num);
		}

		else if (cmd == "rear") {
			lq.rear();
		}

		else if (cmd == "enqueue") {
			int value; cin >> value;
			lq.enqueue(value);
		}

		else if (cmd == "dequeue") {
			lq.dequeue();
		}
	}
}
