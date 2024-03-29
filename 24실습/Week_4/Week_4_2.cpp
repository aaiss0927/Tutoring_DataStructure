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

	int front() {
		return f->value;
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
		Node* del_node = f;

		if (s == 1) {
			f = r = nullptr;
		}

		else {
			f = f->next;
		}

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
		listQueue lq_1;
		listQueue lq_2;
		int score_1 = 0;
		int score_2 = 0;
		int last_winner = -1;

		int N; cin >> N;

		for (int i = 0; i < N; i++) {
			int hp; cin >> hp;
			lq_1.enqueue(hp);
		}

		for (int i = 0; i < N; i++) {
			int hp; cin >> hp;
			lq_2.enqueue(hp);
		}

		for (int i = 0; i < N; i++) {
			cout << "Round" << i + 1 << " ";

			int card_1 = lq_1.front();
			int card_2 = lq_2.front();
			int extra_hp = 0;

			if (card_1 > card_2) {
				cout << card_1 << ">" << card_2 << " ";
				score_1++;
				cout << score_1 << ":" << score_2 << '\n';

				extra_hp = card_1 - card_2;
				
				lq_1.dequeue();
				lq_2.dequeue();

				if (!lq_1.empty()) {
					lq_1.plus(extra_hp);
				}

				if (i == N - 1) {
					last_winner = 1;
				}
			}

			else if (card_1 < card_2) {
				cout << card_1 << "<" << card_2 << " ";
				score_2++;
				cout << score_1 << ":" << score_2 << '\n';

				extra_hp = card_2 - card_1;

				lq_1.dequeue();
				lq_2.dequeue();

				if (!lq_2.empty()) {
					lq_2.plus(extra_hp);
				}

				if (i == N - 1) {
					last_winner = 2;
				}
			}

			else {
				cout << card_1 << "=" << card_2 << " ";
				cout << score_1 << ":" << score_2 << '\n';

				lq_1.dequeue();
				lq_2.dequeue();

				if (i == N - 1) {
					last_winner = 0;
				}
			}
		}

		if (score_1 > score_2) {
			cout << "Winner P1\n";
		}

		else if (score_1 < score_2) {
			cout << "Winner P2\n";
		}

		else {
			if (last_winner == 1) {
				cout << "Winner P1\n";
			}

			else if (last_winner == 2) {
				cout << "Winner P2\n";
			}

			else if (last_winner == 0) {
				cout << "Draw\n";
			}
		}
	}
}
