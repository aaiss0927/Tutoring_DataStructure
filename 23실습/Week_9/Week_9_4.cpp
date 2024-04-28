#include <iostream>
#include <vector>
using namespace std;

class unsortedSeqPQ {
private:
	vector<int> seq;

public:
	void insert(int e) {
		seq.push_back(e);
	}

	int remove() {
		int p_idx = 0;

		for (int i = 0; i < seq.size(); i++) {
			if ((seq[p_idx] % 5 == 0) && (seq[i] % 5 == 0)) {
				if (seq[i] < seq[p_idx]) {
					p_idx = i;
				}
			}

			else if ((seq[p_idx] % 5 == 0) && (seq[i] % 5 != 0)) {
				p_idx = i;
			}

			/*else if ((seq[p_idx] % 5 == 1) && (seq[i] % 5 == 0)) {
				
			}*/

			else if ((seq[p_idx] % 5 != 0) && (seq[i] % 5 != 0)) {
				if (seq[i] < seq[p_idx]) {
					p_idx = i;
				}
			}
		}

		int remove_value = seq[p_idx];
		seq.erase(seq.begin() + p_idx);
		return remove_value;
	}
};

int main() {
	int T; cin >> T;

	while (T--) {
		vector<int> s;
		unsortedSeqPQ pq;
		int N; cin >> N;

		for (int i = 0; i < N; i++) {
			int n; cin >> n;
			s.push_back(n);
		}

		for (int i = 0; i < N; i++) {
			pq.insert(s.front());
			s.erase(s.begin());
		}

		for (int i = 0; i < N; i++) {
			s.push_back(pq.remove());
		}

		for (int i = 0; i < s.size(); i++) {
			cout << s[i] << ' ';
		}

		cout << '\n';
	}
}
