#include <iostream>
#include <string>
using namespace std;

int t;

class Stack {
private:
	char arr[100]{};
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

	char top() {
		return arr[tos - 1];
	}

	void push(char x) {
		arr[tos++] = x;
	}

	void pop() {
		tos--;
	}
};

// 숫자는 바로 출력, 연산자는 스택에 저장 후 조건에 맞게 처리

int main() {
	int t; cin >> t;

	while (t--) {
		Stack S;
		string str; cin >> str;
		int count = 0;

		for (int i = 0; i < str.length(); i++) {
            if (isdigit(str[i])) {
                cout << str[i];
            }

            else if (str[i] == '*') { // '*'라면 스택의 top이 '*'일 동안 모두 pop
                while (!S.empty() && (S.top() == '*')) {
                    cout << S.top(); S.pop();
                }

                if (S.empty()) {
                    count++;
                }

                S.push(str[i]);
            }

            else if (str[i] == '+' || str[i] == '-') { // '*' 아니라면 모두 pop
                while (!S.empty()) {
                    cout << S.top(); S.pop();
                }

                if (S.empty()) {
                    count++;
                }

                S.push(str[i]);
            }
        }

        while (!S.empty()) {
            cout << S.top(); S.pop(); // 이전의 처리 이후 스택에 남아있는 요소 출력(까먹지 말 것!)
        }

        cout << " " << count << '\n';
    }
}
