#include <iostream>
using namespace std;

bool graph[10001][10001];

int main() {
    int T; cin >> T;
    bool vertex[10001] = { false, };

    while (T--) { 
        string cmd; cin >> cmd;

        if (cmd == "insertVertex") {
            int s; cin >> s;

            if (vertex[s]) {
                cout << "Exist\n";
                continue;
            }

            vertex[s] = true;
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

            for (int i = 1; i <= 10000; i++) {
                graph[s][i] = false;
                graph[i][s] = false;
            }

            vertex[s] = false;
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

        else if (cmd == "isAdjacent") {
            int s, d;  cin >> s >> d;
            int cnt_1 = 0, cnt_2 = 0;

            if (graph[s][d])
                cout << "True ";

            else
                cout << "False ";

            for (int i = 1; i <= 10000; i++) {
                if (graph[s][i])
                    cnt_1++;

                if (graph[d][i])
                    cnt_2++;
            }

            if (cnt_1 > cnt_2)
                cout << s;

            else if (cnt_1 < cnt_2)
                cout << d;

            else {
                if (s > d)
                    cout << s;

                else
                    cout << d;
            }
            cout << '\n';
        }

        else if (cmd == "maxVertexInfo") {
            int max = 10001;
            
            for (int i = 10000; i >= 1; i--) {
                if (vertex[i]) {
                    max = i;
                    break;
                }
            }

            if (max == 10001) {
                cout << "-1\n";
                continue;
            }

            int cnt = 0;

            for (int i = 1; i <= 10000; i++) {
                if (graph[max][i])
                    cnt++;
            }

            cout << max << ' ' << cnt << '\n';
        }
    }
}
