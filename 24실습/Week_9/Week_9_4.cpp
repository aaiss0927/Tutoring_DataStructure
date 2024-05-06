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
			int p_idx_value = seq[p_idx];
			int i_value = seq[i];

			int p_idx_digit = 0;
			int i_digit = 0;

			while (p_idx_value) {
				p_idx_value /= 10;
				p_idx_digit++;
			}

			while (i_value) {
				i_value /= 10;
				i_digit++;
			}

			if (p_idx_digit < i_digit) {
				p_idx = i;
			}

			else if (p_idx_digit == i_digit) {
				if (seq[p_idx] > seq[i]) {
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

	for (int k = 1; k <= T; k++) {
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

		cout << "Case #" << k << ".\n";

		for (int i = 0; i < s.size(); i++) {
			cout << s[i] << ' ';
		}

		cout << '\n';
	}
}
