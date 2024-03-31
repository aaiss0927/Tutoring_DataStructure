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

	void insertFront(int value) {
		insert(begin(), value);
	}

	void insertBack(int value) {
		insert(end(), value);
	}

	void erase(Node* pos) {
		pos->prev->next = pos->next;
		pos->next->prev = pos->prev;

		delete pos;
		s--;
	}

	void eraseFront() {
		erase(begin());
	}

	void eraseBack() {
		erase(end()->prev);
	}

	void finddivisor(int e) {
		Node* cur_node = begin();
		int idx = 0;
		bool flag_print = false;

		while (cur_node != end()) {
			if (e % cur_node->value == 0) {
				cout << idx << " ";
				flag_print = true;
			}

			cur_node = cur_node->next;
			idx++;
		}

		if (!flag_print) {
			cout << "-1";
		}

		cout << '\n';
	}
};

int main() {
	List L;
	Node* p = L.begin();
	int N; cin >> N;

	while (N--) {
		string cmd; cin >> cmd;

		if (cmd == "begin") {
			p = L.begin();
		}

		else if (cmd == "end") {
			p = L.end();
		}

		else if (cmd == "insert") {
			int e; cin >> e;
			L.insert(p, e);
		}

		else if (cmd == "erase") {
			if (L.empty()) {
				cout << "empty\n";
				continue;
			}

			if (p == L.end()) {
				continue;
			}

			L.erase(p);
			p = L.begin();
		}

		else if (cmd == "nextP") {
			if (p == L.end()) {
				continue;
			}

			p = p->next;
		}

		else if (cmd == "prevP") {
			if (p == L.begin()) {
				continue;
			}

			p = p->prev;
		}

		else if (cmd == "finddivisor") {
			int e; cin >> e;
			L.finddivisor(e);
		}
	}
}
