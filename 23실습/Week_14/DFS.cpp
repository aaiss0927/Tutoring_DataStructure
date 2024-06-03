#include <iostream>
#include <vector>
using namespace std;

vector<int> graph[1001];
bool visited[1001];

void setup() {
	for (int i = 0; i < 1001; i++) {
		visited[i] = false;
	}
}

void DFS(int a) {
	int cur = a;

	for (int i = 0; i < graph[cur].size(); i++) {
		int next = graph[cur][i];

		if (visited[next])
			continue;

		visited[next] = true;
		DFS(next);
	}
}
