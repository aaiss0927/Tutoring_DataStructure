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

	void insert(int e) {
		seq.push_back(e);
	}

	int remove() {
		int max_idx = 0;

		for (int i = 0; i < seq.size(); i++) {
			if (seq[i] > seq[max_idx]) {
				max_idx = i;
			}
		}

		int remove_value = seq[max_idx];
		seq.erase(seq.begin() + max_idx);
		return remove_value;
	}

	void print() {
		for (int i = 0; i < seq.size(); i++) {
			cout << seq[i] << ' ';
		}
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

		int k; cin >> k;

		if (k <= N) {
			for (int i = 0; i < k; i++) {
				pq.insert(s.front());
				s.erase(s.begin());
			}
		}

		else {
			for (int i = 0; i < N; i++) {
				pq.insert(s.front());
				s.erase(s.begin());
			}

			for (int i = 0; i < k - N; i++) {
				s.push_back(pq.remove());
			}
		}

		cout << "S : ";
		for (int i = 0; i < s.size(); i++) {
			cout << s[i] << ' ';
		}
		cout << '\n';

		cout << "PQ : ";
		pq.print();
		cout << '\n';
	}
}
