#include <iostream>
using namespace std;

#define NOITEM 0
#define ISITEM 1
#define AVAILABLE 2

int cnt;

struct entry {
	string key;
	string value;
	int valid;
	bool is_login;

	entry() {
		key = "";
		value = "";
		valid = NOITEM;
		is_login = false;
	}

	entry(string key, string value) {
		this->key = key;
		this->value = value;
		valid = ISITEM;
		is_login = false;;
	}
};

class HashTable {
private:
	entry* table;
	int cap;
	int HashFnc(string key) {
		int result = 0;

		for (int i = 0; i < key.length(); i++) {
			int temp = 1;

			for (int j = 0; j < i; j++) {
				temp = (temp * 26) % cap;
			}

			result = (result + (key[i] - 'a') * temp) % cap;
		}

		return result;
	}

public:
	HashTable(int N) {
		cap = N;
		table = new entry[cap];
	}

	void put(string key, string value) {
		if (find(key) != -1) {
			cout << "Invalid\n";
			return;
		}

		int idx = HashFnc(key);
		int probe = 1;

		while (table[idx].valid == ISITEM && probe <= cap) {
			idx = (idx + 1) % cap;
			probe++;
		}

		if (probe > cap)
			return;

		table[idx] = entry(key, value);
		cout << "Submit\n";
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

	void login(string key, string value) {
		int idx = find(key);

		if (idx == -1 || value != table[idx].value) {
			cout << "Invalid\n";
			return;
		}

		else if (idx != -1 && value == table[idx].value && table[idx].is_login) {
			cout << "Already\n";
			return;
		}

		else if (idx != -1 && value == table[idx].value && !table[idx].is_login) {
			cnt++;
			table[idx].is_login = true;
			cout << "Submit\n";
		}
	}

	void logout(string key) {
		int idx = find(key);

		cnt--;
		table[idx].is_login = false;
		cout << "Submit\n";
	}

	void online() {
		cout << cnt << '\n';
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int T; cin >> T;
	HashTable ht(200000);

	while (T--) {
		string cmd; cin >> cmd;

		if (cmd == "signup") {
			string s, p; cin >> s >> p;
			ht.put(s, p);
		}

		else if (cmd == "login") {
			string s, p; cin >> s >> p;
			ht.login(s, p);
		}

		else if (cmd == "logout") {
			string s; cin >> s;
			ht.logout(s);
		}

		else if (cmd == "online") {
			ht.online();
		}
	}
}
