#include <iostream>
#include <string>
using namespace std;

#define NOITEM 0
#define ISITEM 1
#define AVAILABLE 2

struct entry {
	string key;
	string value;
	int valid;
	int cnt_present;

	entry() {
		key = "";
		value = "";
		valid = NOITEM;
		cnt_present = 0;
	}

	entry(string key, string value) {
		this->key = key;
		this->value = value;
		valid = ISITEM;
		cnt_present = 0;
	}

	void erase() {
		valid = AVAILABLE;
		cnt_present = 0;
	}
};

class HashTable {
private:
	entry* table;
	int cap;
	int HashFnc(string key) {
		int result = 0;

		if (isalpha(key[0])) {
			for (int i = 0; i < key.length(); i++) {
				int temp = 1;

				for (int j = 0; j < i; j++) {
					temp = (temp * 26) % cap;
				}

				result = (result + (key[i] - 'a') * temp) % cap;
			}
		}

		else {
			for (int i = 0; i < key.length(); i++) {
				int temp = 1;

				for (int j = 0; j < i; j++) {
					temp = (temp * 26) % cap;
				}

				result = (result + (key[i] - '0') * temp) % cap;
			}
		}

		return result;
	}

public:
	HashTable(int N) {
		cap = N;
		table = new entry[cap];
	}

	void put(string key, string value) {
		int idx = HashFnc(key);
		int probe = 1;

		while (table[idx].valid == ISITEM && probe <= cap) {
			idx = (idx + 1) % cap;
			probe++;
		}

		if (probe > cap)
			return;

		table[idx] = entry(key, value);
	}

	string find_(string key) {
		int idx = HashFnc(key);
		int probe = 1;

		while (table[idx].valid != NOITEM && probe <= cap) {
			if (table[idx].valid == ISITEM && table[idx].key == key) {
				return table[idx].value;
			}

			idx = (idx + 1) % cap;
			probe++;
		}

		return "";
	}

	int find(string key) {
		int idx = HashFnc(key);
		int probe = 1;

		while (table[idx].valid != NOITEM && probe <= cap) {
			if (table[idx].valid == ISITEM && table[idx].key == key) {
				return idx;
			}

			idx = (idx + 1) % cap;
			probe++;
		}

		return -1;
	}

	void erase(string key) {
		int idx = HashFnc(key);
		int probe = 1;

		while (table[idx].valid != NOITEM && probe <= cap) {
			if (table[idx].valid == ISITEM && table[idx].key == key) {
				table[idx].erase();
			}

			idx = (idx + 1) % cap;
			probe++;
		}
	}

	int present(string key) {
		int idx = find(key);

		table[idx].cnt_present++;
		return table[idx].cnt_present;
	}

	int count(string key) {
		int idx = find(key);

		return table[idx].cnt_present;
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int T; cin >> T;
	HashTable* ht1 = new HashTable(200000);
	HashTable* ht2 = new HashTable(200000);

	while (T--) {
		string cmd; cin >> cmd;

		if (cmd == "add") {
			string x, s; cin >> x >> s;

			ht1->put(s, x); // (key, value) = (이름, 학번)
			ht2->put(x, s); // (key, value) = (학번, 이름)
		}

		else if (cmd == "delete") {
			string x; cin >> x;
			string s = ht2->find_(x);

			ht1->erase(s);
			ht2->erase(x);
		}

		else if (cmd == "name") {
			string x; cin >> x;
			string s = ht2->find_(x);

			cout << s << '\n';
		}

		else if (cmd == "number") {
			string s; cin >> s;
			string x = ht1->find_(s);

			if (x == "") {
				cout << "0\n";
				continue;
			}
				
			cout << x << '\n';
		}

		else if (cmd == "present") {
			string s; cin >> s;
			string x = ht1->find_(s);

			if (x == "") {
				cout << "-1\n";
				continue;
			}

			int temp = ht1->present(s);
			temp = ht2->present(x);

			cout << temp << '\n';
		}

		else if (cmd == "count") {
			string x; cin >> x;
			string s = ht2->find_(x);

			if (s == "") {
				cout << "-1\n";
				continue;
			}

			int temp = ht1->count(s);
			temp = ht2->count(x);

			cout << temp << '\n';
		}
	}
}
