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

	int front() {
		return f->value;
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

	void plus(int hp) {
		f->value += hp;
	}
};

int main() {
	int T; cin >> T;

	while (T--) {
		listQueue Q1;
		listQueue Q2;

		int N; cin >> N;

		for (int i = 0; i < N; i++) {
			int a; cin >> a;
			Q1.enqueue(a);
		}

		for (int i = 0; i < N; i++) {
			int a; cin >> a;
			Q2.enqueue(a);
		}

		int score_1 = 0;
		int score_2 = 0;

		for (int i = 1; i <= N; i++) {
			cout << "Round" << i << " ";

			int extra_hp = 0;

			if (Q1.front() > Q2.front()) {
				score_1++;
				cout << Q1.front() << ">" << Q2.front();
				cout << " " << score_1 << ":" << score_2 << endl;
				extra_hp = Q1.front() - Q2.front();
				Q1.dequeue(); Q2.dequeue();

				if (!Q1.empty()) {
					Q1.plus(extra_hp);
				}
			}

			else if (Q1.front() < Q2.front()) {
				score_2++;
				cout << Q1.front() << "<" << Q2.front();
				cout << " " << score_1 << ":" << score_2 << endl;
				extra_hp = Q2.front() - Q1.front();
				Q1.dequeue(); Q2.dequeue();

				if (!Q2.empty()) {
					Q2.plus(extra_hp);
				}
			}

			else {
				cout << Q1.front() << "=" << Q2.front();
				cout << " " << score_1 << ":" << score_2 << endl;
				Q1.dequeue(); Q2.dequeue();
			}
		}

		if (score_1 == score_2) {
			cout << "Draw\n";
		}

		else if (score_1 > score_2) {
			cout << "Winner P1\n";
		}

		else if (score_1 < score_2) {
			cout << "Winner P2\n";
		}
	}
}
