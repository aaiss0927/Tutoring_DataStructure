#include <iostream>
using namespace std;

int temp;

class Node {
public:
	int key;
	Node* parent;
	Node* left;
	Node* right;

	Node(int key) {
		this->key = key;
		parent = left = right = nullptr;
	}
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

		if (curNode->key == key)
			return curNode;

		else if (curNode->key < key)
			return search(curNode->right, key);

		else
			return search(curNode->left, key);
	}

	void insert(int key) {
		if (search(root, key) != nullptr)
			return;

		Node* newNode = new Node(key);

		if (root == nullptr) {
			root = newNode;
			return;
		}

		Node* curNode = root;
		Node* parNode = nullptr;

		while (curNode != nullptr) {
			parNode = curNode;

			if (curNode->key < key)
				curNode = curNode->right;

			else
				curNode = curNode->left;
		}

		newNode->parent = parNode;

		if (parNode->key < key)
			parNode->right = newNode;

		else
			parNode->left = newNode;
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
			root->parent = nullptr;
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

	int get_subtree_size(Node* node) {
		if (node == nullptr)
			return 0;

		if (node->left == nullptr && node->right == nullptr)
			return 1;

		else if (node->left == nullptr && node->right != nullptr)
			return get_subtree_size(node->right) + 1;

		else if (node->left != nullptr && node->right == nullptr)
			return get_subtree_size(node->left) + 1;

		else {
			return get_subtree_size(node->right) + get_subtree_size(node->left) + 1;
		}
	}
};

int main() {
	BST bst;
	int n, m; cin >> n >> m;

	for (int i = 0; i < n; i++) {
		int x; cin >> x;
		bst.insert(x);
	}

	for (int i = 0; i < m; i++) {
		int x, y; cin >> x >> y;
		int first = bst.get_subtree_size(bst.search(bst.root, x)->right);
		int second = bst.get_subtree_size(bst.search(bst.root, y)->right);

		int result = (first > second) ? (first - second) : (second - first);
		cout << result << '\n';
	}
}
