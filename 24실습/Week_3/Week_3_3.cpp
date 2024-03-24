#include <iostream>
using namespace std;

class Node {
private:
    int value;
    Node* next;

public:
    Node(int v) {
        value = v;
        next = nullptr;
    }
    friend class Linkedlist;
    friend class Stack;
};

class Linkedlist {
private:
    int size;
    Node* head;
    Node* tail;

public:
    Linkedlist() {
        size = 0;
        head = nullptr;
        tail = nullptr;
    }

    bool empty() {
        return (size == 0);
    }

    void append(int x) {
        Node* new_node = new Node(x);

        if (empty()) {
            head = tail = new_node;
        }

        else {
            tail->next = new_node;
            tail = new_node;
        }

        size++;
    }

    int delete_back() {
        int del_value = tail->value;

        if (size == 1) {
            delete head;
            head = tail = nullptr;
        }

        else {
            Node* cur_node = head;

            while (cur_node->next != tail) {
                cur_node = cur_node->next;
            }

            delete cur_node->next;
            cur_node->next = nullptr;
            tail = cur_node;
        }

        size--;
        return del_value;
    }

    friend class Stack;
};

class Stack {
private:
    Linkedlist ll;
    int size;

public:
    Stack() {
        ll = Linkedlist();
        size = 0;
    }

    int size_() {
        return size;
    }

    bool empty() {
        return (size == 0);
    }

    int top() {
        if (empty()) {
            return - 1;
        }

        return ll.tail->value;
    }

    void push(int x) {
        ll.append(x);
        size++;
    }

    void pop() {
        if (empty()) {
            return;
        }

        ll.delete_back();
        size--;
    }
};

int main() {
    Stack S;
    int N;  cin >> N;

    while (N--) {
        string cmd; cin >> cmd;

        if (cmd == "size") {
            cout << S.size_() << '\n';
        }

        else if (cmd == "empty") {
            cout << S.empty() << "\n";
        }

        else if (cmd == "top") {
            cout << S.top() << '\n';
        }

        else if (cmd == "push") {
            int x; cin >> x;
            S.push(x);
        }

        else if (cmd == "pop") {
            int x; cin >> x;
            
            if (S.empty()) {
                cout << "-1\n";
                continue;
            }

            if (S.size_() >= x) {
                while (x--) {
                    cout << S.top() << ' ';
                    S.pop();
                }

                cout << '\n';
            }

            else {
                int temp = S.size_();

                while (temp--) {
                    cout << S.top() << ' ';
                    S.pop();
                }

                cout << '\n';
            }
        }
    }
}
