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

	friend class SinglyLinkedList;
};

class SinglyLinkedList {
private:
	Node* head;
	Node* tail;
	int list_size;

public:
	SinglyLinkedList() {
		head = tail = nullptr;
		list_size = 0;
	}

	bool empty() {
		return list_size == 0;
	}

	void append(int value) {
		Node* new_node = new Node(value);

		if (empty()) {
			head = tail = new_node;
		}

		else {
			tail->next = new_node;
			tail = new_node;
		}

		list_size++;
	}

	void insertion(int idx, int value) {
		if (idx < 0 || idx > list_size) {
			return;
		}

		if (idx == list_size) {
			append(value);
		}

		else if (idx == 0) {
			Node* new_node = new Node(value);

			new_node->next = head;
			head = new_node;

			list_size++;
		}

		else {
			Node* new_node = new Node(value);
			Node* cur_node = head;

			for (int i = 1; i < idx; i++) {
				cur_node = cur_node->next;
			}

			new_node->next = cur_node->next;
			cur_node->next = new_node;

			list_size++;
		}
	}

	void deletion(int idx) {
		if (empty() || idx >= list_size) {
			cout << "-1\n";
			return;
		}

		Node* del_node = head;

		if (idx == 0) {
			if (list_size == 1) {
				head = tail = nullptr;
			}

			else {
				head = head->next;
			}
		}

		else {
			Node* pre_node = head;

			for (int i = 0; i < idx; i++) {
				pre_node = del_node;
				del_node = del_node->next;
			}

			pre_node->next = del_node->next;

			if (del_node == tail) {
				tail = pre_node;
			}
		}

		cout << del_node->value << '\n';
		delete del_node;
		list_size--;
	}

	void print() {
		if (empty()) {
			cout << "empty\n";
			return;
		}

		Node* cur_node = head;

		while (cur_node != nullptr) {
			cout << cur_node->value << " ";
			cur_node = cur_node->next;
		}

		cout << '\n';
	}

	void after_max(int idx) {
		if (empty() || idx >= list_size) {
			cout << "error\n";
			return;
		}

		Node* cur_node = head;

		for (int i = 0; i < idx; i++) {
			cur_node = cur_node->next;
		}

		int max = cur_node->value;

		while (cur_node->next != nullptr) {
			cur_node = cur_node->next;

			if (cur_node->value > max) {
				max = cur_node->value;
			}
		}

		cout << max << '\n';
	}

	int sum() {
		if (empty()) {
			return 0;
		}

		Node* cur_node = head;
		int s = 0;

		while (cur_node != nullptr) {
			s += cur_node->value;
			cur_node = cur_node->next;
		}

		return s;
	}
};

int main() {
	int m; cin >> m;
	SinglyLinkedList sll;

	while (m--) {
		string cmd; cin >> cmd;

		if (cmd == "Print") {
			sll.print();
		}

		else if (cmd == "Append") {
			int x; cin >> x;
			sll.append(x);
			sll.print();
		}

		else if (cmd == "Delete") {
			int i; cin >> i;
			sll.deletion(i);
		}

		else if (cmd == "AfterMax") {
			int i; cin >> i;
			sll.after_max(i);
		}

		else if (cmd == "Sum") {
			cout << sll.sum() << '\n';
		}
	}
}
