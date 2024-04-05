#include <iostream>
using namespace std;

class Node {
public:
	int value;
	Node* prev;
	Node* next;

	Node() {
		this->value = 0;
		prev = next = nullptr;
	}

	Node(int value) {
		this->value = value;
		prev = next = nullptr;
	}

	friend class List;
};

class List {
private:
	Node* header;
	Node* trailer;
	int s;

public:
	List() {
		header = new Node();
		trailer = new Node();
		header->next = trailer;
		trailer->prev = header;
		header->prev = trailer->next = nullptr;
		s = 0;
	}

	bool empty() {
		return (s == 0);
	}

	int size() {
		return s;
	}

	Node* begin() {
		return header->next;
	}

	Node* end() {
		return trailer;
	}

	void insert(Node* pos, int value) {
		Node* new_node = new Node(value);

		new_node->prev = pos->prev;
		new_node->next = pos;

		pos->prev->next = new_node;
		pos->prev = new_node;

		s++;
	}

	void erase(Node* pos) {
		pos->prev->next = pos->next;
		pos->next->prev = pos->prev;

		delete pos;
		s--;
	}

	void find(int x) {
		Node* cur_node = begin();
		int idx = 0;

		while (cur_node != end()) {
			if (cur_node->value == x) {
				cout << idx << '\n';
				return;
			}

			cur_node = cur_node->next;
			idx++;
		}

		cout << "not_found\n";
	}

	void print(int m) {
		if (empty()) {
			cout << "empty\n";
			return;
		}

		if (m == 0) {
			Node* cur_node = begin();

			while (cur_node != end()) {
				cout << cur_node->value << " ";
				cur_node = cur_node->next;
			}
			cout << '\n';
		}

		else {
			Node* cur_node = end()->prev;

			while (cur_node != begin()->prev) {
				cout << cur_node->value << " ";
				cur_node = cur_node->prev;
			}
			cout << '\n';
		}
	}
};

int main() {
	List L;
	int N; cin >> N;

	while (N--) {
		string cmd; cin >> cmd;

		if (cmd == "insert") {
			int i, x; cin >> i >> x;

			if (i < 0 || i > L.size()) {
				cout << "out_of_range\n";
				continue;
			}

			Node* p = L.begin();

			while (i--) {
				p = p->next;
			}

			L.insert(p, x);
		}

		else if (cmd == "erase") {
			int i; cin >> i;

			if (i < 0 || i >= L.size()) {
				cout << "out_of_range\n";
				continue;
			}

			Node* p = L.begin();

			while (i--) {
				p = p->next;
			}

			L.erase(p);
		}

		else if (cmd == "empty") {
			cout << boolalpha << L.empty() << '\n';
		}

		else if (cmd == "find") {
			int x; cin >> x;
			L.find(x);
		}

		else if (cmd == "print") {
			int m; cin >> m;
			L.print(m);
		}
	}
}
