#include <iostream>
#include <vector>
using namespace std;

int graph[501][501];

void maskAdjacentVertices(int vertexId, vector<bool>& v) {
	for (int i = 1; i < 501; i++) {
		if (graph[vertexId][i] == 1) {
			v[i] = true;
		}
	}
}

int main() {
	int N, M, D; cin >> N >> M >> D;

	vector<int> denied;

	for (int i = 0; i < D; i++) {
		int s; cin >> s;
		denied.push_back(s);
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			int is_friend; cin >> is_friend;

			if (is_friend) {
				graph[i + 1][j + 1] = true;
				graph[j + 1][i + 1] = true;
			}
		}
	}

	for (int i = 0; i < M; i++) {
		int K, S; cin >> K >> S;
		vector<bool> result_table(N + 1, false);

		maskAdjacentVertices(K, result_table);

		if (S == 2) {
			for (int i = 1; i <= N; i++) {
				if (result_table[i])
					maskAdjacentVertices(i, result_table);
			}
		}
		result_table[K] = false;

		for (int i = 0; i < D; i++) {
			if (result_table[denied[i]])
				result_table[denied[i]] = false;
		}

		bool is_empty = true;

		for (int i = 1; i <= N; i++) {
			if (result_table[i]) {
				cout << i << ' ';
				is_empty = false;
			}
		}

		if (is_empty)
			cout << 0;

		cout << '\n';
	}
}
