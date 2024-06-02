#include <iostream>
#include <vector>
#include <queue>
using namespace std;

vector<int> graph[1001];
bool visited[1001];
queue<int> q;
int cnt;

void setup() {
	for (int i = 0; i < 1001; i++) {
		visited[i] = false;
	}

	q = queue<int>();
	cnt = 1;
}

void BFS(int a, int b) {
	while (!q.empty()) {
		int cur = q.front(); q.pop();

		for (int i = 0; i < graph[cur].size(); i++) {
			int next = graph[cur][i];

			if (visited[next])
				continue;

			cnt++;
			if (next == b) {
				cout << cnt << '\n';
				return;
			}

			visited[next] = true;
			q.push(next);
		}
	}
}

int main() {
	int N, M, Q; cin >> N >> M >> Q;

	for (int i = 0; i < M; i++) {
		int u, v; cin >> u >> v;
		graph[u].push_back(v);
		graph[v].push_back(u);
	}

	for (int i = 0; i < Q; i++) {
		int a, b; cin >> a >> b;

		setup();
		visited[a] = true;
		q.push(a);
		BFS(a, b);
	}
}
