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
			return curNode;
		}

		else if (curNode->key < key) {
			return search(curNode->right, key);
		}

		else {
			return search(curNode->left, key);
		}
	}

	void insert(int key) {
		Node* newNode = new Node(key);

		if (root == nullptr) {
			root = newNode;
			return;
		}

		Node* curNode = root;
		Node* parNode = nullptr;

		while (curNode != nullptr) {
			parNode = curNode;

			if (curNode->key < key) {
				curNode = curNode->right;
			}
				
			else {
				curNode = curNode->left;
			}	
		}

		newNode->parent = parNode;

		if (parNode->key < key)
			parNode->right = newNode;

		else
			parNode->left = newNode;
	}

	void remove(int key) {
		Node* delNode = search(root, key);

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

	void max(int k) {
		inorder_traversal(root, k);
	}

	void inorder_traversal(Node* node, int k) {
		if (node == nullptr)
			return;

		inorder_traversal(node->right, k);

		if (temp == k) {
			cout << node->key << '\n';
			temp = k + 1;
			return;
		}
		temp++;

		inorder_traversal(node->left, k);
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

			else if (cmd == "delete") {
				int x; cin >> x;
				bst.remove(x);
			}

			else if (cmd == "max") {
				int k; cin >> k;
				temp = 1;
				bst.max(k);
			}
		}
	}
}
