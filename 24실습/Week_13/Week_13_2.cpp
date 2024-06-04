#include <iostream>
#include <vector>
using namespace std;

int graph[501][501];
int score;

void maskAdjacentVertices(int vertexId, vector<bool>& v) {
	for (int i = 1; i < 501; i++) {
		if (graph[vertexId][i] == 1) {
			v[i] = true;
		}
	}
}

int main() {
	int N, M, D; cin >> N >> M >> D;

	vector<pair<int, int>> connected;

	for (int i = 0; i < D; i++) {
		int s, d; cin >> s >> d;
		connected.push_back({ s, d });
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
		score = 0;
		vector<int> score_table(N + 1, 1);
		vector<bool> result_table(N + 1, false);

		maskAdjacentVertices(K, result_table);

		for (int i = 1; i <= N; i++) {
			if (result_table[i])
				score_table[i] = 3;
		}

		if (S == 2) {
			for (int i = 1; i <= N; i++) {
				if (result_table[i]) {
					maskAdjacentVertices(i, result_table);

					for (int i = 1; i <= N; i++) {
						if (result_table[i] && score_table[i] == 1)
							score_table[i] = 2;
					}
				}
			}
		}
		result_table[K] = false;

		for (int i = 0; i < D; i++) {
			if (connected[i].first == K)
				result_table[connected[i].second] = false;

			else if (connected[i].second == K)
				result_table[connected[i].first] = false;

			else if (connected[i].second != K && result_table[connected[i].first])
				result_table[connected[i].second] = true;

			else if (connected[i].first != K && result_table[connected[i].second])
				result_table[connected[i].first] = true;
		}

		int cnt = 0;

		for (int i = 1; i <= N; i++) {
			if (result_table[i]) {
				cnt++;
				score += score_table[i];
			}
		}

		if (cnt == 0) {
			cout << "-1\n";
			continue;
		}
			
		cout << cnt << ' ' << score << '\n';
	}
}
