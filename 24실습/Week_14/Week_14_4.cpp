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

void DFS(int a) {
	int cur = a;

	for (int i = 0; i < graph[cur].size(); i++) {
		int next = graph[cur][i];

		if (visited[next])
			continue;

		cnt++;
		visited[next] = true;
		DFS(next);
	}
}

int main() {
	int N, M, Q; cin >> N >> M >> Q;

	for (int i = 0; i < M; i++) {
		int A, B; cin >> A >> B;
		graph[A].push_back(B);
		graph[B].push_back(A);
	}

	for (int i = 0; i < Q; i++) {
		int C; cin >> C;
		setup();
		visited[C] = true;
		DFS(C);

		cout << cnt << '\n';
	}
}
