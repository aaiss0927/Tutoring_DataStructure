#include <iostream>
#include <vector>
using namespace std;

int temp;

class Node {
private:
	int value;
	Node* parent;
	vector<Node*> child_list;

public:
	int w;
	int cap;

	Node(int value, Node* parent) {
		w = 0;
		cap = 0;
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

	void set_w(int x, int w) {
		int idx = find(x, node_list);
		Node* cur_node = node_list[idx];
		cur_node->w = w;
	}

	void cal_cap(Node* cur_node) {
		temp += cur_node->w;

		for (int i = 0; i < cur_node->child_list.size(); i++) {
			cal_cap(cur_node->child_list[i]);
		}
	}

	void print(int value) {
		int idx = find(value, node_list);
		Node* cur_node = node_list[idx];
		cout << cur_node->cap << '\n';
	}
};

int main() {
	Tree TR;
	int N, M; cin >> N >> M;

	for (int i = 0; i < N - 1; i++) {
		int x, y; cin >> x >> y;
		TR.insert_node(x, y);
	}

	for (int i = 0; i < N; i++) {
		int u, w; cin >> u >> w;
		TR.set_w(u, w);
	}

	for (int i = 0; i < TR.node_list.size(); i++) {
		temp = 0;
		TR.cal_cap(TR.node_list[i]);
		TR.node_list[i]->cap = temp;
	}

	for (int i = 0; i < M; i++) {
		int v; cin >> v;
		TR.print(v);
	}
}
