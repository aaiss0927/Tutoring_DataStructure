#include <iostream>
using namespace std;

class arrayQueue {
private:
	int* arr;
	int capacity;
	int f;
	int r;
	int s;

public:
	arrayQueue(int capacity) {
		this->capacity = capacity;
		arr = new int[capacity];
		f = r = 0;
		s = 0;
	}

	bool empty() {
		return (s == 0);
	}

	bool full() {
		return (s == capacity);
	}

	int size() {
		return s;
	}

	int front() {
		return arr[f];
	}

	void rear() {
		if (empty()) {
			cout << "Empty\n";
			return;
		}

		if (r == 0) {
			cout << arr[capacity - 1] << '\n';
			return;
		}

		cout << arr[r - 1] << '\n';
	}

	void enqueue(int value) {
		if (full()) {
			cout << "Full\n";
			return;
		}

		arr[r] = value;

		r = (r + 1) % capacity;
		s++;
	}

	void dequeue() {
		if (empty()) {
			cout << "Empty\n";
			return;
		}

		f = (f + 1) % capacity;
		s--;
	}

	void plus(int hp) {
		arr[f] += hp;
	}
};

int main() {
	int T; cin >> T;

	while (T--) {
		arrayQueue lq_1(100);
		arrayQueue lq_2(100);
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

				if (!lq_2.empty()) {
					lq_2.plus(extra_hp);
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

				if (!lq_1.empty()) {
					lq_1.plus(extra_hp);
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
