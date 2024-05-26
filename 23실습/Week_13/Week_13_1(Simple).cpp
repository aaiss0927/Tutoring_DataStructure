#include <iostream>
using namespace std;

int vertex, s, d;
int max_num;

bool graph[10001][10001];

int main() {
    int T; cin >> T;
    bool vertex[10001] = { false, };
    max_num = 0;

    while (T--) {
        string cmd; cin >> cmd;

        if (cmd == "insertVertex") {
            int s; cin >> s;

            if (vertex[s]) {
                cout << "Exist\n";
                continue;
            }

            vertex[s] = true;
            max_num = (s > max_num) ? s : max_num;
        }

        else if (cmd == "insertEdge") {
            int s, d; cin >> s >> d;

            if (graph[s][d] || graph[d][s]) {
                cout << "Exist\n";
                continue;
            }

            graph[s][d] = true;
            graph[d][s] = true;
        }

        else if (cmd == "eraseEdge") {
            int s, d; cin >> s >> d;

            if (!graph[s][d] || !graph[d][s]) {
                cout << "None\n";
                continue;
            }
            
            graph[s][d] = false;
            graph[d][s] = false;
        }

        else if (cmd == "isAdjacentOdd") {
            int s;  cin >> s;
            int cnt = 0;

            for (int i = 1; i <= max_num; i++) {
                if (graph[s][i]) {
                    cnt++;
                }
            }

            string result = (cnt % 2) ? "True" : "False";
            cout << result << ' ' << cnt << '\n';
        }

        else if (cmd == "minEdgeVertex") {
            int num = 10001;
            int min = 10000;

            for (int i = 1; i <= max_num; i++) {
                if (!vertex[i])
                    continue;

                int cnt = 0;

                for (int j = 1; j <= max_num; j++) {
                    if (graph[i][j])
                        cnt++;
                }

                if (cnt < min) {
                    num = i;
                    min = cnt;
                }

                if (cnt == min) {
                    if (i < num)
                        num = i;
                }
            }

            if (min == 0 || num == 10001)
                cout << "-1\n";

            else
                cout << num << '\n';
        }
    }
}
