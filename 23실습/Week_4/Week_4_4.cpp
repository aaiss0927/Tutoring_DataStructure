#include <iostream>
using namespace std;

class arrayQueue {
private:
	int* arr;       // 배열
	int capacity;   // 큐의 최대 크기
	int f;          // front의 index
	int r;          // rear의 index + 1
	int s;          // 큐의 크기

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

	int size() {
		return s;
	}

	int front() {
		return arr[f];
	}

	void enqueue(int value) {
		arr[r] = value;

		r = (r + 1) % capacity;
		s++;
	}

	void dequeue() {
		if (empty()) {
			cout << "Empty\n";
			return;
		}

		cout << arr[f] << '\n';

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
		arrayQueue Q1(100);
		arrayQueue Q2(100);

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
				cout << "P1 ";
				extra_hp = Q1.front() - Q2.front();
				cout << extra_hp << '\n';
				Q1.dequeue(); Q2.dequeue();

				if (!Q2.empty()) {
					Q2.plus(extra_hp);
				}
			}

			else if (Q1.front() < Q2.front()) {
				score_2++;
				cout << "P2 ";
				extra_hp = Q2.front() - Q1.front();
				cout << extra_hp << '\n';
				Q1.dequeue(); Q2.dequeue();

				if (!Q1.empty()) {
					Q1.plus(extra_hp);
				}
			}

			else {
				cout << "Draw\n";
				Q1.dequeue(); Q2.dequeue();
			}
		}

		cout << "Total Score " << score_1 << ":" << score_2 << " ";

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
