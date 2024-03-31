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
};

int main() {
	int T; cin >> T;

	while (T--) {
		List L;
		Node* p = L.begin();
		int N; cin >> N;

		while (N--) {
			int e; cin >> e;
			L.insert(p, e);
		}

		p = L.begin();

		int M; cin >> M;

		while (M--) {
			int k; cin >> k;

			if (k > 0) {
				while (k--) {
					if (p == L.end()) {
						break;
					}

					p = p->next;
				}
			}

			else if (k < 0) {
				k = -k;

				while (k--) {
					if (p == L.begin()) {
						break;
					}

					p = p->prev;
				}
			}

			else {

			}

			int temp = p->value;

			if (temp > 0) {
				while (temp--) {
					if (p == L.end()) {
						break;
					}

					p = p->next;
				}
			}

			else if (temp < 0) {
				temp = -temp;

				while (temp--) {
					if (p == L.begin()) {
						break;
					}

					p = p->prev;
				}
			}

			else {

			}
		}

		Node* node_check_dist_header = p;
		Node* node_check_dist_trailer = p;
		int dist_header = 0;
		int dist_trailer = 0;

		while (node_check_dist_header != L.begin()->prev) {
			node_check_dist_header = node_check_dist_header->prev;
			dist_header++;
		}

		while (node_check_dist_trailer != L.end()) {
			node_check_dist_trailer = node_check_dist_trailer->next;
			dist_trailer++;
		}

		if (dist_header > dist_trailer) {
			cout << "trailer\n";
		}

		else if (dist_header < dist_trailer) {
			cout << "header\n";
		}

		else {
			cout << "middle\n";
		}
	}
}
