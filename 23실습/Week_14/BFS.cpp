#include <iostream>
#include <vector>
#include <queue>
using namespace std;

vector<int> graph[1001];
bool visited[1001];
queue<int> q;

void setup() {
	for (int i = 0; i < 1001; i++) {
		visited[i] = false;
	}
}

void BFS(int a) {
	while (!q.empty()) {
		int cur = q.front(); q.pop();

		for (int i = 0; i < graph[cur].size(); i++) {
			int next = graph[cur][i];

			if (visited[next])
				continue;

			visited[next] = true;
			q.push(next);
		}
	}
}
