#include <iostream>
using namespace std;

class Node {
public:
	int value;
	Node* next;

	Node(int value) {
		this->value = value;
		next = nullptr;
	}

	friend class SinglyLinkedList;
};

class SinglyLinkedList {
public:
	Node* head;
	Node* tail;
	int list_size;

	SinglyLinkedList() {
		head = tail = nullptr;
		list_size = 0;
	}

	bool empty() {
		return list_size == 0;
	}

	int find_node_idx(int value) {
		Node* cur_node = head;
		int idx = 0;

		while (cur_node != nullptr) {
			if (cur_node->value == value) {
				return idx;
			}

			idx++;
			cur_node = cur_node->next;
		}
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
};

void merge(SinglyLinkedList& sll_1, SinglyLinkedList& sll_2) {
	// sll_1, sll_2를 sll_1로 통합
	// 이후 sll_1만 사용
	
	sll_1.tail->next = sll_2.head;
	sll_1.tail = sll_2.tail;

	sll_1.list_size += sll_2.list_size;
}

int main() {
	int m; cin >> m;

	while (m--) {
		SinglyLinkedList sll_1, sll_2;

		int n_1; cin >> n_1;

		while (n_1--) {
			int x; cin >> x;
			sll_1.append(x);
		}
		
		int n_2; cin >> n_2;

		while (n_2--) {
			int x; cin >> x;
			sll_2.append(x);
		}

		merge(sll_1, sll_2);
		sll_1.print();

		int e; cin >> e;
		sll_1.deletion(sll_1.find_node_idx(e));
		sll_1.print();

		int k; cin >> k;
		cout << sll_1.find_node_idx(k) << '\n';
	}
}
