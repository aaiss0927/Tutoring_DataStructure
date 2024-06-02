#include <iostream>
#include <vector>
using namespace std;

vector<int> graph[1001];
bool visited[1001];
int cnt;

void setup() {
	for (int i = 0; i < 1001; i++) {
		visited[i] = false;
	}

	cnt = 1;
}

void DFS(int a, int b) {
	int cur = a;
	
	if (cur == b) {
		cout << cnt << '\n';
		return;
	}

	for (int i = 0; i < graph[cur].size(); i++) {
		int next = graph[cur][i];

		if (visited[next])
			continue;

		cnt++;
		visited[next] = true;
		DFS(next, b);
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
		DFS(a, b);
	}
}
