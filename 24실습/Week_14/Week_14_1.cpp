#include <iostream>
#include <vector>
using namespace std;

class Graph {
private:
	int vertexList[10000];
	int cur = 0;
	vector<int> adjacencyList[10000];

public:
	int find_array_id(int vertex_id) {
		for (int i = 0; i < 10000; i++) {
			if (vertexList[i] == vertex_id)
				return i;
		}

		return -1;
	}

	void insertVertex(int s) {
		if (find_array_id(s) != -1) {
			cout << "ERRORCODE 01\n";
			return;
		}

		vertexList[cur] = s;
		cur++;
	}

	void eraseVertex(int s) {
		if (find_array_id(s) == -1) {
			cout << "ERRORCODE 03\n";
			return;
		}

		int arr_id = find_array_id(s);

		for (int i = 0; i < adjacencyList[arr_id].size(); i++) {
			int dst_arr_id = find_array_id(adjacencyList[arr_id][i]);

			for (int j = 0; j < adjacencyList[dst_arr_id].size(); j++) {
				if (adjacencyList[dst_arr_id][j] == s)
					adjacencyList[dst_arr_id].erase(adjacencyList[dst_arr_id].begin() + j);
			}
		}
		adjacencyList[arr_id].clear();

		vertexList[arr_id] = 0;
	}

	void insertEdge(int s, int d) {
		if (find_array_id(s) == -1 || find_array_id(d) == -1) {
			cout << "ERRORCODE 03\n";
			return;
		}

		int src_arr_id = find_array_id(s);
		int dst_arr_id = find_array_id(d);

		for (int i = 0; i < adjacencyList[src_arr_id].size(); i++) {
			if (adjacencyList[src_arr_id][i] == d) {
				cout << "ERRORCODE 02\n";
				return;
			}
		}

		for (int i = 0; i < adjacencyList[dst_arr_id].size(); i++) {
			if (adjacencyList[dst_arr_id][i] == s) {
				cout << "ERRORCODE 02\n";
				return;
			}
		}

		adjacencyList[src_arr_id].push_back(d);
		adjacencyList[dst_arr_id].push_back(s);
	}

	void eraseEdge(int s, int d) {
		if (find_array_id(s) == -1 || find_array_id(d) == -1) {
			cout << "ERRORCODE 03\n";
			return;
		}

		int src_arr_id = find_array_id(s);
		int dst_arr_id = find_array_id(d);
		int s_idx, d_idx;
		bool flag;

		flag = false;
		for (int i = 0; i < adjacencyList[src_arr_id].size(); i++) {
			if (adjacencyList[src_arr_id][i] == d) {
				flag = true;
				d_idx = i;
			}
		}

		if (!flag) {
			cout << "ERRORCODE 04\n";
			return;
		}

		flag = false;
		for (int i = 0; i < adjacencyList[dst_arr_id].size(); i++) {
			if (adjacencyList[dst_arr_id][i] == s) {
				flag = true;
				s_idx = i;
			}
		}

		if (!flag) {
			cout << "ERRORCODE 04\n";
			return;
		}

		adjacencyList[src_arr_id].erase(adjacencyList[src_arr_id].begin() + d_idx);
		adjacencyList[dst_arr_id].erase(adjacencyList[dst_arr_id].begin() + s_idx);
	}

	void printAdjSum(int s) {
		if (find_array_id(s) == -1) {
			cout << "ERRORCODE 03\n";
			return;
		}

		int arr_id = find_array_id(s);
		if (adjacencyList[arr_id].empty()) {
			cout << "0 0\n";
			return;
		}

		int sum = 0;
		for (int i = 0; i < adjacencyList[arr_id].size(); i++)
			sum += adjacencyList[arr_id][i];

		cout << adjacencyList[arr_id].size() << ' ' << sum << '\n';
	}

	void printAdjMin(int s) {
		if (find_array_id(s) == -1) {
			cout << "ERRORCODE 03\n";
			return;
		}

		int arr_id = find_array_id(s);
		if (adjacencyList[arr_id].empty()) {
			cout << "-1\n";
			return;
		}

		int mini = 1000000;
		for (int i = 0; i < adjacencyList[arr_id].size(); i++) {
			mini = min(mini, adjacencyList[arr_id][i]);
		}

		cout << mini << '\n';
	}
};

int main() {
	Graph* graph = new Graph[100];
	int N; cin >> N;

	while (N--) {
		string cmd; cin >> cmd;

		if (cmd == "Graph") {
			int gid; cin >> gid;
		}

		else if (cmd == "InsertVertex") {
			int gid, s; cin >> gid >> s;
			graph[gid].insertVertex(s);
		}

		else if (cmd == "InsertEdge") {
			int gid, s, d; cin >> gid >> s >> d;
			graph[gid].insertEdge(s, d);
		}

		else if (cmd == "EraseVertex") {
			int gid, s; cin >> gid >> s;
			graph[gid].eraseVertex(s);
		}

		else if (cmd == "EraseEdge") {
			int gid, s, d; cin >> gid >> s >> d;
			graph[gid].eraseEdge(s, d);
		}

		else if (cmd == "PrintAdjSum") {
			int gid, s; cin >> gid >> s;
			graph[gid].printAdjSum(s);
		}

		else if (cmd == "PrintAdjMin") {
			int gid, s; cin >> gid >> s;
			graph[gid].printAdjMin(s);
		}
	}
}
