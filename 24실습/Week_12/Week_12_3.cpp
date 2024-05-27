#include <iostream>
using namespace std;

#define NOITEM 0
#define ISITEM 1
#define AVAILABLE 2

struct entry {
	int key;
	string value;
	int valid;

	entry() {
		key = 0;
		value = "";
		valid = NOITEM;
	}

	entry(int key, string value) {
		this->key = key;
		this->value = value;
		valid = ISITEM;
	}

	void erase() {
		valid = AVAILABLE;
	}
};

class HashTable {
private:
	entry* table;
	int cap;
	int HashFnc(int key) {
		return key % cap;
	}

public:
	HashTable(int N) {
		cap = N;
		table = new entry[cap];
	}

	void put(int key, string value) {
		int idx = HashFnc(key);
		cout << idx << ' ';
		int probe = 1;

		while (table[idx].valid == ISITEM && probe <= cap) {
			idx = HashFnc(idx + 1);
			probe++;
		}

		if (probe > cap)
			idx = -1;

		cout << idx << '\n';
		table[idx] = entry(key, value);
	}

	void erase(int key) {
		int idx = HashFnc(key);
		int probe = 1;

		while (table[idx].valid != NOITEM && probe <= cap) {
			if (table[idx].valid == ISITEM && table[idx].key == key) {
				cout << table[idx].value << '\n';
				table[idx].erase();
				return;
			}

			idx = HashFnc(idx + 1);
			probe++;
		}

		cout << "None\n";
	}

	string find(int key) {
		int idx = HashFnc(key);
		int probe = 1;

		while (table[idx].valid != NOITEM && probe <= cap) {
			if (table[idx].valid == ISITEM && table[idx].key == key) {
				return table[idx].value;
			}

			idx = HashFnc(idx + 1);
			probe++;
		}

		return "None";
	}

	int vacant(int N) {
		int cnt = 0;

		for (int i = 0; i < N; i++) {
			if (table[i].valid != ISITEM) {
				cnt++;
			}
		}

		return cnt;
	}
};

int main() {
	int T, N; cin >> T >> N;
	HashTable ht(N);

	while (T--) {
		string cmd; cin >> cmd;

		if (cmd == "put") {
			int K; string S; cin >> K >> S;
			ht.put(K, S);
		}

		else if (cmd == "erase") {
			int K; cin >> K;
			ht.erase(K);
		}

		else if (cmd == "find") {
			int K; cin >> K;
			cout << ht.find(K) << '\n';
		}

		else if (cmd == "vacant") {
			cout << ht.vacant(N) << '\n';
		}
	}
}
