#include <iostream>
#include <vector>
using namespace std;

class sortedSeqPQ {
private:
	vector<int> seq;

public:
	int size() {
		return seq.size();
	}

	void insert(int e) {
		if (seq.empty()) {
			seq.push_back(e);
			return;
		}

		int idx = seq.size();

		for (int i = 0; i < seq.size(); i++) {
			if (e < seq[i]) {
				idx = i;
				break;
			}
		}

		seq.insert(seq.begin() + idx, e);
	}

	int remove() {
		int remove_value = seq.back();
		seq.pop_back();
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
		sortedSeqPQ pq;
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
