#include <iostream>
#include <vector>
using namespace std;

class Node {
private:
	int value;
	Node* parent;
	vector<Node*> child_list;

public:
	Node(int value, Node* parent) {
		this->value = value;
		this->parent = parent;
	}

	friend class Tree;
};

class Tree {
public:
	Node* root;
	vector<Node*> node_list;

	Tree() {
		root = new Node(1, nullptr);
		node_list.push_back(root);
	}

	int find(int value, vector<Node*>& list) {
		for (int i = 0; i < list.size(); i++) {
			if (list[i]->value == value) {
				return i;
			}
		}

		return -1;
	}

	void insert_node(int par_value, int value) {
		if (find(value, node_list) != -1) {
			cout << "-1\n"; return;
		}

		int par_idx = find(par_value, node_list);
		if (par_idx == -1) {
			cout << "-1\n"; return;
		}

		Node* par_node = node_list[par_idx];
		Node* new_node = new Node(value, par_node);

		par_node->child_list.push_back(new_node);
		node_list.push_back(new_node);
	}

	void postorder(Node* cur_node) {
		for (int i = 0; i < cur_node->child_list.size(); i++) {
			postorder(cur_node->child_list[i]);
		}

		if (cur_node->child_list.empty()) {
			cout << get_depth(cur_node->value) << ' ';
		}

		else {
			cout << cur_node->child_list.size() << ' ';
		}
	}

	int get_depth(int value) {
		int depth = 0;
		int idx = find(value, node_list);
		Node* cur_node = node_list[idx];

		while (cur_node->parent != nullptr) {
			depth++;
			cur_node = cur_node->parent;
		}

		return depth;
	}
};

int main() {
	int T; cin >> T;

	while (T--) {
		Tree TR;
		int N; cin >> N;

		for (int i = 0; i < N - 1; i++) {
			int x, y; cin >> x >> y;
			TR.insert_node(x, y);
		}

		TR.postorder(TR.root);
		cout << '\n';
	}
}
