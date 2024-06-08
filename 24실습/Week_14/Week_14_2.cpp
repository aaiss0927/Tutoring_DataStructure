#include <iostream>
#include <vector>
using namespace std;

vector<int> graph[1001];
bool visited[1001];
bool flag;

void setup() {
	for (int i = 0; i < 1001; i++) {
		visited[i] = false;
	}
	flag = false;
}

void DFS(int a, int b) {
	int cur = a;

	if (cur == b) {
		flag = true;
		return;
	}

	for (int i = 0; i < graph[cur].size(); i++) {
		int next = graph[cur][i];

		if (visited[next])
			continue;

		visited[next] = true;
		DFS(next, b);
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
		int A, B; cin >> A >> B;
		setup();
		visited[A] = true;
		DFS(A, B);

		if (flag)
			cout << "True\n";
		else
			cout << "False\n";
	}
}
