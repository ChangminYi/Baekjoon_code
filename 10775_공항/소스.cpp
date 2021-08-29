#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

vector<int> parent;
int G, P;

int _find(int x) {
	if (parent[x] == x) {
		return x;
	}
	return parent[x] = _find(parent[x]);
}

void _union(int x, int y) {
	int p_x = _find(x), p_y = _find(y);
	if (p_x > p_y) {
		swap(p_x, p_y);
	}
	parent[p_y] = p_x;
}

int main() {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);

	cin >> G >> P;
	parent = vector<int>(G + 1);
	iota(parent.begin(), parent.end(), 0);

	int dock_cnt = 0;
	for (int i = 0, plane, dock; i < P; i++) {
		cin >> plane;
		dock = _find(plane);

		if (dock == 0) {
			break;
		}
		else {
			_union(dock, dock - 1);
			dock_cnt++;
		}
	}

	cout << dock_cnt;

	return 0;
}