#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;
typedef pair<string, string> pstr;

unordered_map<string, string> parent;

string _find(string& s) {
	if (parent[s] == s) {
		return s;
	}
	else {
		return parent[s] = _find(parent[s]);
	}
}

void _union(string& x, string& y) {
	string f_x = _find(x);
	string f_y = _find(y);

	if (f_x < f_y) {
		parent[f_y] = f_x;
	}
	else {
		parent[f_x] = f_y;
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
		unordered_map<string, int> str_count;
		vector<pstr> dat(n);
		for (int i = 0; i < n; i++) {
			cin >> dat[i].first >> dat[i].second;
			str_count.insert(make_pair(dat[i].first, 1));
			str_count.insert(make_pair(dat[i].second, 1));
		}
		for (unordered_map<string, int>::iterator i = str_count.begin(); i != str_count.end(); i++) {
			parent.insert(make_pair(i->first, i->first));
		}

		for (pstr& p : dat) {
			string f_x = _find(p.first);
			string f_y = _find(p.second);

			_union(f_x, f_y);
			if (f_x != f_y) {
				if (f_x > f_y) {
					swap(f_x, f_y);
				}
				str_count[f_x] += str_count[f_y];
			}

			cout << str_count[f_x] << '\n';
		}

		dat.clear();
		str_count.clear();
		parent.clear();
	} while (--iter > 0);

	return 0;
}