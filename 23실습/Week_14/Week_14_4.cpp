#include <iostream>
#include <vector>
using namespace std;

vector<int> graph[101];
bool visited[101];
int min_num;

void setup(int C) {
	for (int i = 0; i < 101; i++) {
		visited[i] = false;
	}

	min_num = C;
}

void DFS(int C) {
	int cur = C;

	min_num = (cur < min_num) ? cur : min_num;

	for (int i = 0; i < graph[cur].size(); i++) {
		int next = graph[cur][i];

		if (visited[next])
			continue;

		visited[next] = true;
		DFS(next);
	}
}

int main() {
	int T; cin >> T;

	while (T--) {
		int N, M, Q; cin >> N >> M >> Q;

		for (int i = 0; i < M; i++) {
			int A, B; cin >> A >> B;
			graph[A].push_back(B);
		}

		for (int i = 0; i < Q; i++) {
			int C; cin >> C;

			setup(C);
			visited[C] = true;
			DFS(C);
			
			cout << min_num << '\n';
		}

		for (int i = 0; i < 101; i++) {
			graph[i].clear();
		}
	}
}
