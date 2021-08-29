#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <numeric>

using namespace std;

typedef pair<string, string> pstr;
typedef pair<pstr, int> dat;

int n, m;
string prefix = "Kingdom of ";
string tmp;
vector<string> kingdom;
vector<int> parent;
unordered_map<string, int> s_to_idx;

int _find(int x) {
	if (parent[x] == x) {
		return x;
	}
	return parent[x] = _find(parent[x]);
}

void _union(int x, int y, bool front_parent) {
	int f_x = _find(x), f_y = _find(y);
	if (front_parent) {
		if (f_x == f_y) {
			parent[x] = x;
			parent[f_y] = x;
		}
		else {
			parent[f_y] = f_x;
		}
	}
	else {
		if (f_x == f_y) {
			parent[y] = y;
			parent[f_x] = y;
		}
		else {
			parent[f_x] = f_y;
		}
	}
}

string get_kingdom_name(string &str) {
	return str.substr(prefix.length());
}

dat parse_to_dat(string &str) {
	vector<int> com_idx;
	for (int i = 0; i < (int)str.length(); i++) {
		if (str[i] == ',') {
			com_idx.push_back(i + 1);
		}
	}

	string k_1 = str.substr(0, com_idx.front() - 1);
	string k_2 = str.substr(com_idx.front(), com_idx.back() - com_idx.front() - 1);
	return make_pair(
		make_pair(
			get_kingdom_name(k_1),
			get_kingdom_name(k_2)
		),
		stoi(str.substr(com_idx.back()))
	);
}

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);

	cin >> n >> m;
	cin.ignore();
	kingdom = vector<string>(n);
	parent = vector<int>(n);
	iota(parent.begin(), parent.end(), 0);
	for (int i = 0; i < n; i++) {
		getline(cin, tmp);
		kingdom[i] = get_kingdom_name(tmp);
	}
	sort(kingdom.begin(), kingdom.end());
	for (int i = 0; i < n; i++) {
		s_to_idx.insert(make_pair(kingdom[i], i));
	}

	for (int i = 0; i < m; i++) {
		getline(cin, tmp);
		dat tmp_dat = parse_to_dat(tmp);

		_union(
			s_to_idx[tmp_dat.first.first],
			s_to_idx[tmp_dat.first.second],
			tmp_dat.second == 1
		);
	}

	vector<int> par_no;
	for (int i = 0; i < n; i++) {
		if (_find(i) == i) {
			par_no.push_back(i);
		}
	}

	cout << par_no.size() << '\n';
	for (int& i : par_no) {
		cout << prefix << kingdom[i] << '\n';
	}

	return 0;
}