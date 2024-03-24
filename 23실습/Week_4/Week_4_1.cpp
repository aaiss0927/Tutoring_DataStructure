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
	Node* f;    // front(head)
	Node* r;    // rear(tail)
	int s;      // 큐의 크기

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
			f = r = new_node;    // 예외
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
			f = r = nullptr;    // 예외
		}

		else {
			f = f->next;
		}

		cout << del_node->value << '\n';
		// del_node->next = nullptr;
		delete del_node;
		s--;
	}
};

int main() {
	int T;
	cin >> T;
	listQueue Q;

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
