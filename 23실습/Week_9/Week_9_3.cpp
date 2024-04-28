#include <iostream>
#include <vector>
using namespace std;

class unsortedSeqPQ {
private:
	vector<int> seq;

public:
	int size() {
		return seq.size();
	}

	bool empty() {
		return (seq.size() == 0);
	}

	void insert(int e) {
		seq.push_back(e);
	}

	int max() {
		if (empty()) {
			return -1;
		}

		int maxi = seq[0];

		for (int i = 0; i < seq.size(); i++) {
			if (seq[i] > maxi) {
				maxi = seq[i];
			}
		}

		return maxi;
	}

	void removeMax() {
		if (empty()) {
			return;
		}

		int max_idx = 0;

		for (int i = 0; i < seq.size(); i++) {
			if (seq[i] > seq[max_idx]) {
				max_idx = i;
			}
		}

		seq.erase(seq.begin() + max_idx);
	}
};

int main() {
	int T; cin >> T;

	while (T--) {
		vector<int> s;
		unsortedSeqPQ pq;
		vector<int> sub;
		int N; cin >> N;

		for (int i = 0; i < N; i++) {
			int n; cin >> n;
			pq.insert(n);
		}

		for (int i = 0; i < N; i++) {
			s.push_back(pq.max());
			pq.removeMax();
			
			if (s.size() > 1) {
				sub.push_back(s.front() - s.back());
			}
		}

		for (int i = 0; i < s.size(); i++) {
			cout << s[i] << ' ';
		}

		cout << '\n';

		for (int i = 0; i < sub.size(); i++) {
			cout << sub[i] << ' ';
		}

		cout << '\n';
	}
}
