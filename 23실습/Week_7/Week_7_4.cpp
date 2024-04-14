#include <iostream>
#include <vector>
using namespace std;

int temp;
bool flag;

class Node {
private:
	int value;
	Node* parent;
	vector<Node*> child_list;

public:
	int cnt;

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

	void cal_cnt(Node* cur_node) {
		while (cur_node != root) {
			cur_node = cur_node->parent;
			temp++;
		}
	}

	void preorder(Node* cur_node, int x) {
		if (cur_node->child_list.empty() && cur_node->cnt == x) {
			cout << cur_node->value << ' ';
			flag = true;
		}

		for (int i = 0; i < cur_node->child_list.size(); i++) {
			preorder(cur_node->child_list[i], x);
		}
	}

};

int main() {
	Tree TR;
	int N, M; cin >> N >> M;

	for (int i = 0; i < N - 1; i++) {
		int x, y; cin >> x >> y;
		TR.insert_node(x, y);
	}

	for (int i = 0; i < TR.node_list.size(); i++) {
		temp = 0;
		TR.cal_cnt(TR.node_list[i]);
		TR.node_list[i]->cnt = temp;
	}

	for (int i = 0; i < M; i++) {
		flag = false;
		int x; cin >> x;
		TR.preorder(TR.root, x);

		if (!flag) {
			cout << -1;
		}

		cout << '\n';
	}
}
