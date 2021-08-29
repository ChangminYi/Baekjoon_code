#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <algorithm>

using namespace std;

typedef struct NODE {
	string name;
	string extension;
} node;

unordered_set<string> ext;
vector<node> argf;
int n, m;

bool comp_file(const node& a, const node& b) {
	if (a.name == b.name) {
		bool a_ext_find = (ext.find(a.extension) != ext.end());
		bool b_ext_find = (ext.find(b.extension) != ext.end());

		if (a_ext_find && !b_ext_find) {
			return true;
		}
		else if (!a_ext_find && b_ext_find){
			return false;
		}
		else {
			return a.extension < b.extension;
		}
	}
	else {
		return a.name < b.name;
	}
}

int main() {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);

	cin >> n >> m;
	argf.resize(n);

	string temp;
	int dot_idx;
	for (node& f : argf) {
		cin >> temp;
		dot_idx = temp.find_first_of('.');
		f.name = temp.substr(0, dot_idx);
		f.extension = temp.substr(dot_idx + 1);
	}
	for (int i = 0; i < m; i++) {
		cin >> temp;
		ext.insert(temp);
	}

	sort(argf.begin(), argf.end(), comp_file);
	for (node& f : argf) {
		cout << f.name << '.' << f.extension << '\n';
	}

	return 0;
}