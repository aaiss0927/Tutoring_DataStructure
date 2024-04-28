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

	int removeMax() {
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
			s.push_back(n);
		}

		for (int i = 0; i < N; i++) {
			pq.insert(s.front());
			s.erase(s.begin());
		}

		for (int i = 0; i < N; i++) {
			s.push_back(pq.removeMax());
			
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
