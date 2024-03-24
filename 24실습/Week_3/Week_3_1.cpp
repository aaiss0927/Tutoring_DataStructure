#include <iostream>
using namespace std;

int t;

class Stack {
private:
	int arr[10000]{};
	int tos;
public:
	Stack() {
		tos = 0;
	}

	int size_() {
		return tos;
	}

	bool empty() {
		return (tos == 0);
	}

	bool full() {
		return (tos == t);
	}

	int top() {
		if (empty()) {
			return -1;
		}

		return arr[tos - 1];
	}

	void push(int x) {
		if (full()) {
			cout << "FULL\n";
			return;
		}

		arr[tos++] = x;
	}

	void pop() {
		if (empty()) {
			return;
		}

		top();
		tos--;
	}
};

int main() {
	cin >> t;
	Stack S;
	int N; cin >> N;

	while (N--) {
		string cmd; cin >> cmd;

		if (cmd == "size") {
			cout << S.size_() << '\n';
		}

		else if (cmd == "empty") {
			cout << S.empty() << '\n';
		}

		else if (cmd == "top") {
			cout << S.top() << '\n';
		}

		else if (cmd == "push") {
			int x; cin >> x;
			S.push(x);
		}

		else if (cmd == "popsum") {
			int x; cin >> x;

			if (S.empty()) {
				cout << "-1\n";
				continue;
			}

			int sum = 0;

			if (S.size_() >= x) {
				while (x--) {
					sum += S.top();
					S.pop();
				}
			}

			else {
				int temp = S.size_();    // pop의 과정에서 S의 size가 변하기 때문에 고정
				
				while (temp--) {
					sum += S.top();
					S.pop();
				}
			}

			cout << sum << '\n';
		}
	}
}
