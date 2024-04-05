#include <iostream>
using namespace std;

class Node {
public:
	string value;
	Node* prev;
	Node* next;

	Node() {
		this->value = "";
		prev = next = nullptr;
	}

	Node(string value) {
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

	void insert(Node* pos, string value) {
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

	void append(Node* pos, string value) {
		Node* new_node = new Node(value);

		if (empty()) {
			pos = header;
		}

		new_node->prev = pos;
		new_node->next = pos->next;

		pos->next->prev = new_node;
		pos->next = new_node;

		s++;
	}

	void print() {
		if (empty()) {
			cout << "And Then There Were None\n";
			return;
		}

		Node* cur_node = begin();

		while (cur_node != end()) {
			cout << cur_node->value << " ";
			cur_node = cur_node->next;
		}
		cout << '\n';
	}
};

int main() {
	int T; cin >> T;

	while (T--) {
		List L;
		Node* p = L.begin();
		int n, m, k; cin >> n >> m >> k;

		while (n--) {
			string str; cin >> str;
			L.insert(p, str);
		}

		p = L.begin();

		while (k--) {
			p = p->next;
		}

		while (m--) {
			string cmd; cin >> cmd;

			if (cmd == "up") {
				int x; cin >> x;

				if (L.empty()) {
					continue;
				}

				while (x--) {
					if (p == L.begin()) {
						break;
					}

					p = p->prev;
				}
			}

			else if (cmd == "down") {
				int x; cin >> x;

				if (L.empty()) {
					continue;
				}

				while (x--) {
					if (p == L.end()->prev) {
						break;
					}

					p = p->next;
				}
			}

			else if (cmd == "cut") {
				if (L.empty()) {
					continue;
				}

				if (p == L.begin()) {
					Node* temp = p->next;
					L.erase(p);
					p = temp;
				}

				else {
					Node* temp = p->prev;
					L.erase(p);
					p = temp;
				}
			}

			else if (cmd == "append") {
				string name; cin >> name;
				L.append(p, name);

				if (L.size() == 1) {
					p = L.begin();
				}
			}
		}

		L.print();
	}
}
