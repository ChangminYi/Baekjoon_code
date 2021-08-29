#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

const int MAX_SIZE = 10;

typedef class NODE {
public:
	bool finish = false;
	vector<NODE *> child = vector<NODE *>(MAX_SIZE, nullptr);

	NODE() {}
	bool insert(const string& s, size_t idx) {
		if (this->finish) {
			return false;
		}
		else {
			if (idx == s.length()) {
				this->finish = true;
				return true;
			}
			else {
				int c_idx = s[idx] - '0';

				if (child[c_idx] == nullptr) {
					child[c_idx] = new NODE();
				}

				return child[c_idx]->insert(s, idx + 1);
			}
		}
	}
} node;

bool str_cmp(const string& a, const string& b) {
	if (a.length() == b.length()) {
		return a < b;
	}
	else {
		return a.length() < b.length();
	}
}

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);
	cout.tie(nullptr);
	cout.sync_with_stdio(false);

	int iter;
	cin >> iter;
	do {
		int n;
		cin >> n;
		vector<string> args(n);
		for (string& s : args) {
			cin >> s;
		}
		sort(args.begin(), args.end(), str_cmp);

		node tree;
		bool complete = true;
		for (string& s : args) {
			if (!tree.insert(s, 0)) {
				complete = false;
				break;
			}
		}

		cout << (complete ? "YES\n" : "NO\n");
	} while (--iter > 0);

	return 0;
}