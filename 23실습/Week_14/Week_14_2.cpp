#include <iostream>
#include <vector>
using namespace std;

vector<int> graph[101];
bool visited[101];
int max_num;

void setup() {
	for (int i = 0; i < 101; i++) {
		visited[i] = false;
	}

	max_num = 0;
}

void DFS(int C) {
	int cur = C;

	max_num = (cur > max_num) ? cur : max_num;

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

			setup();
			visited[C] = true;
			DFS(C);
			
			cout << max_num << '\n';
		}

		for (int i = 0; i < 101; i++) {
			graph[i].clear();
		}
	}
}
