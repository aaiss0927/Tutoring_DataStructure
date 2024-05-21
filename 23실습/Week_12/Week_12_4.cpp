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
	int room;
	bool is_absent;

	entry() {
		key = "";
		value = "";
		valid = NOITEM;
		room = 0;
		is_absent = true;
	}

	entry(string key, string value, int c) {
		this->key = key;
		this->value = value;
		valid = ISITEM;
		room = c;
		is_absent = true;
	}

	void erase() {
		valid = AVAILABLE;
		is_absent = true;
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

	void put(string key, string value, int c) {
		int idx = HashFnc(key);
		int probe = 1;

		while (table[idx].valid == ISITEM && probe <= cap) {
			idx = (idx + 1) % cap;
			probe++;
		}

		if (probe > cap)
			return;

		table[idx] = entry(key, value, c);
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

	int erase(string key) {
		int idx = HashFnc(key);
		int probe = 1;

		while (table[idx].valid != NOITEM && probe <= cap) {
			if (table[idx].valid == ISITEM && table[idx].key == key) {
				int temp = table[idx].room;
				table[idx].erase();
				return temp;
			}

			idx = (idx + 1) % cap;
			probe++;
		}

		return -1;
	}

	void change(string key, int c) {
		int idx = find(key);
		table[idx].room = c;
	}

	int present(string key) {
		int idx = find(key);

		table[idx].is_absent = false;
		return table[idx].room;
	}

	int absent(string key) {
		int idx = find(key);

		table[idx].is_absent = true;
		return table[idx].room;
	}

	int cnt_present() {
		int cnt = 0;

		for (int i = 0; i < 500001; i++) {
			if (table[i].is_absent == false) {
				cnt++;
			}
		}

		return cnt;
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int T; cin >> T;
	HashTable* ht1 = new HashTable(500001);
	HashTable* ht2 = new HashTable(500001);

	while (T--) {
		string cmd; cin >> cmd;

		if (cmd == "add") {
			string x, s; int c; cin >> x >> c >> s;

			ht1->put(s, x, c); // (key, value) = (이름, 학번)
			ht2->put(x, s, c); // (key, value) = (학번, 이름)
		}

		else if (cmd == "delete") {
			string x; cin >> x;
			string s = ht2->find_(x);

			int temp = ht1->erase(s);
			temp = ht2->erase(x);

			cout << s << ' ' << temp << '\n';
		}

		else if (cmd == "name") {
			string x; cin >> x;
			string s = ht2->find_(x);

			cout << ht2->find_(x) << '\n';
		}

		else if (cmd == "change") {
			string x; int c; cin >> x >> c;
			string s = ht2->find_(x);

			ht1->change(s, c);
			ht2->change(x, c);
		}

		else if (cmd == "present") {
			string s; cin >> s;
			string x = ht1->find_(s);

			if (x == "") {
				cout << "Invalid\n";
				continue;
			}

			int temp = ht1->present(s);
			temp = ht2->present(x);

			cout << x << ' ' << temp << '\n';
		}

		else if (cmd == "absent") {
			string s; cin >> s;
			string x = ht1->find_(s);

			if (x == "") {
				cout << "Invalid\n";
				continue;
			}

			int temp = ht1->absent(s);
			temp = ht2->absent(x);

			cout << x << ' ' << temp << '\n';
		}
	}

	cout << ht1->cnt_present();
}
