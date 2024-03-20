#include <iostream>
using namespace std;

int t;

class Stack {
private:
	int arr[20]{};
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

	void top() {
		if (empty()) {
			cout << "-1\n";
			return;
		}

		cout << arr[tos - 1] << '\n';
	}

	void push(int x) {
		if (full()) {
			cout << "FULL\n";
			return;
		}

		arr[tos++] = x;
	}

	void pop() {
		top();
		tos--;
	}
};

int main() {
	cin >> t;
	Stack S;
	int N; cin >> N;

	while (N--) {
		string str; cin >> str;

		if (str == "size") {
			cout << S.size_() << '\n';
		}

		else if (str == "empty") {
			cout << S.empty() << '\n';
		}

		else if (str == "full") {
			cout << S.full() << '\n';
		}

		else if (str == "top") {
			S.top();
		}

		else if (str == "push") {
			int x; cin >> x;
			S.push(x);
		}

		else if (str == "pop") {
			S.pop();
		}
	}
}