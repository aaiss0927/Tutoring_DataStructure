#include <iostream>
#include <string>
using namespace std;

int t;

class Stack {
private:
	int arr[100]{};
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

	int top() {
		return arr[tos - 1];
	}

	void push(int x) {
		arr[tos++] = x;
	}

	void pop() {
		tos--;
	}
};

// 숫자는 스택에 저장, 연산자가 나올 시 스택에서 top 2개 꺼내서 계산 후 push

int main() {
	int t; cin >> t;

	while (t--) {
		Stack S;
		string str; cin >> str;

		for (int i = 0; i < str.length(); i++) {
			if (isdigit(str[i])) {
				S.push(str[i] - '0');
			}

			else {
				if (str[i] == '+') {
					int first = S.top(); S.pop();
					int second = S.top(); S.pop();
					int result = second + first;
					S.push(result);
				}

				else if (str[i] == '-') {
					int first = S.top(); S.pop();
					int second = S.top(); S.pop();
					int result = second - first; // 순서 중요!
					S.push(result);
				}

				else if (str[i] == '*') {
					int first = S.top(); S.pop();
					int second = S.top(); S.pop();
					int result = second * first;
					S.push(result);
				}
			}
		}

		int temp = S.top();

		if (temp < 0) {
			temp = temp * (-1);
		}

		int sum = 0;
		
		while (temp) { // 각 자리 수의 합 계산
			sum += (temp % 10);
			temp /= 10;
		}

		cout << sum << '\n';
	}
}
