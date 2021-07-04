#include <iostream>
#include <vector>

using namespace std;

vector<int> parent;

int _find(int x) {
	if (parent[x] == x) {
		return x;
	}
	else {
		return parent[x] = _find(parent[x]);
	}
}

bool in_same_set(int x, int y) {
	return _find(x) == _find(y);
}

void _union(int x, int y) {
	int p_x = _find(x), p_y = _find(y);

	if (p_x < p_y) {
		parent[p_y] = p_x;
	}
	else {
		parent[p_x] = p_y;
	}
}

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);
	cout.tie(nullptr);
	cout.sync_with_stdio(false);

	int n, m;
	cin >> n >> m;

	parent = vector<int>(n + 1);
	for (int i = 0; i <= n; i++) {
		parent[i] = i;
	}

	int inst;
	pair<int, int> arg;
	do {
		cin >> inst >> arg.first >> arg.second;

		switch (inst) {
		case 0:
			_union(arg.first, arg.second);
			break;
		case 1:
			if (in_same_set(arg.first, arg.second)) {
				cout << "YES\n";
			}
			else {
				cout << "NO\n";
			}
			break;
		}
	} while (--m > 0);

	return 0;
}