#include <iostream>
using namespace std;

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

        else if (cmd == "eraseVertex") {
            int s; cin >> s;

            for (int i = 1; i <= max_num; i++) {
                graph[s][i] = false;
                graph[i][s] = false;
            }
        }

        else if (cmd == "isAdjacentEven") {
            int s;  cin >> s;
            int cnt = 0;

            for (int i = 1; i <= max_num; i++) {
                if (graph[s][i]) {
                    cnt++;
                }
            }

            string result = (cnt % 2) ? "False" : "True";
            cout << result << ' ' << cnt << '\n';
        }

        else if (cmd == "maxEdgeVertex") {
            int num = 10001;
            int max = -1;

            for (int i = 1; i <= max_num; i++) {
                if (!vertex[i])
                    continue;

                int cnt = 0;

                for (int j = 1; j <= max_num; j++) {
                    if (graph[i][j])
                        cnt++;
                }

                if (cnt > max) {
                    num = i;
                    max = cnt;
                }

                if (cnt == max) {
                    if (i < num)
                        num = i;
                }
            }

            if (max == 0 || num == 10001)
                cout << "-1\n";

            else
                cout << num << '\n';
        }
    }
}
