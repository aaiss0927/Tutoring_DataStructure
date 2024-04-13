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
private:
	Node* root;
	vector<Node*> node_list;

public:
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
			cout << "-1\n";
			return;
		}

		int par_idx = find(par_value, node_list);

		if (par_idx == -1) {
			cout << "-1\n";
			return;
		}

		/*
		if (find(par_value, node_list) == -1) {
			return;
		}
		*/

		Node* par_node = node_list[par_idx];
		Node* new_node = new Node(value, par_node);

		par_node->child_list.push_back(new_node);
		node_list.push_back(new_node);
	}

	void delete_node(int value) {
		int idx = find(value, node_list);

		if (idx == -1) {
			cout << "-1\n";
			return;
		}

		Node* del_node = node_list[idx];

		if (del_node == root) {
			return;
		}

		Node* par_node = del_node->parent;

		for (int i = 0; i < del_node->child_list.size(); i++) {
			par_node->child_list.push_back(del_node->child_list[i]);
			del_node->child_list[i]->parent = par_node;
		}

		vector<Node*>& child = par_node->child_list;

		child.erase(child.begin() + find(value, child));
		/*
		par_node->child_list.erase(par_node->child_list.begin() +
			find(value, par_node->child_list));
		*/
		node_list.erase(node_list.begin() + idx);
		delete del_node;
	}

	void print_parent(int value) {
		int idx = find(value, node_list);

		if (idx == -1) {
			cout << "-1\n";
			return;
		}

		Node* cur_node = node_list[idx];
		cout << cur_node->parent->value << '\n';
	}

	void print_child(int value) {
		int idx = find(value, node_list);

		if (idx == -1) {
			cout << "-1\n";
			return;
		}

		vector<Node*>& child = node_list[idx]->child_list;

		if (child.empty()) {
			cout << "-1\n";
			return;
		}

		for (int i = 0; i < child.size(); i++) {
			cout << child[i]->value << " ";
		}
		cout << '\n';
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

	void get_depth_sub(int value1, int value2) {
		int idx1 = find(value1, node_list);
		int idx2 = find(value2, node_list);

		if (idx1 == -1 || idx2 == -1) {
			cout << "error\n";
			return;
		}

		int depth1 = get_depth(value1);
		int depth2 = get_depth(value2);
		int add = depth1 + depth2;

		cout << depth1 << ' ' << depth2 << ' ' << add << '\n';
	}
};

int main() {
	Tree TR;
	int N, M; cin >> N >> M;

	while (N--) {
		int x, y; cin >> x >> y;
		TR.insert_node(x, y);
	}

	while (M--) {
		int v, w; cin >> v >> w;
		TR.get_depth_sub(v, w);
	}
}
