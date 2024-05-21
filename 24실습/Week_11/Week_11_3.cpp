#include <iostream>
using namespace std;

int temp;

class Node {
private:
	int key;
	Node* parent;
	Node* left;
	Node* right;

public:
	Node(int key) {
		this->key = key;
		parent = left = right = nullptr;
	}

	friend class BST;
};

class BST {
public:
	Node* root;

	BST() {
		root = nullptr;
	}

	Node* search(Node* curNode, int key) {
		if (curNode == nullptr)
			return nullptr;

		if (curNode->key == key) {
			temp++;
			return curNode;
		}

		else if (curNode->key < key) {
			temp++;
			return search(curNode->right, key);
		}

		else {
			temp++;
			return search(curNode->left, key);
		}
	}

	void insert(int key) {
		Node* newNode = new Node(key);

		if (root == nullptr) {
			cout << "0\n";
			root = newNode;
			return;
		}

		Node* curNode = root;
		Node* parNode = nullptr;

		int cnt = 0;

		while (curNode != nullptr) {
			parNode = curNode;

			if (curNode->key < key) {
				cnt++;
				curNode = curNode->right;
			}
				
			else {
				cnt++;
				curNode = curNode->left;
			}	
		}

		newNode->parent = parNode;

		if (parNode->key < key)
			parNode->right = newNode;

		else
			parNode->left = newNode;

		cout << cnt << '\n';
	}

	void remove(int key) {
		Node* delNode = search(root, key);

		if (delNode == nullptr)
			return;

		Node* parNode = delNode->parent;
		Node* childNode;

		if (delNode->left == nullptr && delNode->right == nullptr)
			childNode = nullptr;

		else if (delNode->left == nullptr && delNode->right != nullptr)
			childNode = delNode->right;

		else if (delNode->left != nullptr && delNode->right == nullptr)
			childNode = delNode->left;

		else {
			childNode = delNode->right;

			while (childNode->left != nullptr)    // successor 찾기
				childNode = childNode->left;

			delNode->key = childNode->key;
			delNode = childNode;
			parNode = delNode->parent;
			childNode = delNode->right;
		}

		if (parNode == nullptr) {
			root = childNode;

			if (root != nullptr) {
				root->parent = nullptr;
			}
		}

		else if (delNode == parNode->left) {
			parNode->left = childNode;

			if (childNode != nullptr)
				childNode->parent = parNode;
		}

		else {
			parNode->right = childNode;

			if (childNode != nullptr)
				childNode->parent = parNode;
		}

		delete delNode;
	}

	void get_parent(int x) {
		Node* curNode = search(root, x);

		if (curNode == nullptr) {
			cout << "-1\n";
			return;
		}

		if (curNode->parent == nullptr) {
			cout << "-2\n";
			return;
		}

		cout << curNode->parent->key << '\n';
	}

	void get_right_child(int x) {
		Node* curNode = search(root, x);

		if (curNode == nullptr) {
			cout << "-1\n";
			return;
		}

		if (curNode->right == nullptr) {
			cout << "-2\n";
			return;
		}

		cout << curNode->right->key << '\n';
	}
};

int main() {
	int T; cin >> T;

	while (T--) {
		BST bst;
		int N; cin >> N;

		while (N--) {
			string cmd; cin >> cmd;

			if (cmd == "insert") {
				int x; cin >> x;
				bst.insert(x);
			}

			else if (cmd == "search") {
				int x; cin >> x;
				temp = 0;
				bst.search(bst.root, x);

				if (temp == 0) 
					cout << "empty\n";
				
				else 
					cout << temp << '\n';
			}

			else if (cmd == "parent") {
				int x; cin >> x;
				bst.get_parent(x);
			}

			else if (cmd == "child") {
				int x; cin >> x;
				bst.get_right_child(x);
			}
		}
	}
}
