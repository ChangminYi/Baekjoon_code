#include <iostream>
#include <vector>

using namespace std;

typedef pair<int, int> pint;
typedef class SEGMENT_TREE {
private:
	int len = 0;
	vector<vector<int>> seg = vector<vector<int>>();

	int get_sum_1d(int cur, int lo_y, int hi_y) {
		int ret = 0;

		for (int i = lo_y + len, j = hi_y + len + 1; i < j; i /= 2, j /= 2) {
			if (i % 2 == 1) {
				ret += seg[cur][i++];
			}
			if (j % 2 == 1) {
				ret += seg[cur][--j];
			}
		}

		return ret;
	}
public:
	SEGMENT_TREE() {}
	SEGMENT_TREE(const vector<vector<int>>& argi) {
		this->len = (int)argi.size();
		this->seg = vector<vector<int>>(2 * len, vector<int>(2 * len));

		for (int i = 0; i < len; i++) {
			for (int j = 0; j < len; j++) {
				seg[i + len][j + len] = argi[i][j];
			}
		}
		for (int i = len; i < 2 * len; i++) {
			for (int j = len - 1; j > 0; j--) {
				seg[i][j] = seg[i][2 * j] + seg[i][2 * j + 1];
			}
		}
		for (int i = len - 1; i > 0; i--) {
			for (int j = 1; j < 2 * len; j++) {
				seg[i][j] = seg[2 * i][j] + seg[2 * i + 1][j];
			}
		}
	}

	void update(pint p, int new_value) {
		seg[p.first + len][p.second + len] = new_value;

		for (int i = p.second + len; i > 1; i /= 2) {
			seg[p.first + len][i / 2] = seg[p.first + len][i] + seg[p.first + len][i ^ 1];
		}
		for (int i = p.first + len; i > 1; i /= 2) {
			for (int j = p.second + len; j >= 1; j /= 2) {
				seg[i / 2][j] = seg[i][j] + seg[i ^ 1][j];
			}
		}
	}

	int get_sum_2d(pint lo, pint hi) {
		int ret = 0;

		for (int i = lo.first + len, j = hi.first + len + 1; i < j; i /= 2, j /= 2) {
			if (i % 2 == 1) {
				ret += get_sum_1d(i++, lo.second, hi.second);
			}
			if (j % 2 == 1) {
				ret += get_sum_1d(--j, lo.second, hi.second);
			}
		}

		return ret;
	}

} seg_2d;

const pint operator--(const pint& p) {
	return make_pair(p.first - 1, p.second - 1);
}

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);

	int n, m;
	cin >> n >> m;
	vector<vector<int>> argi(n, vector<int>(n));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> argi[i][j];
		}
	}

	seg_2d segtree(argi);
	do {
		int inst;
		cin >> inst;

		if (inst == 0) {
			pint arg1;
			int arg2;
			cin >> arg1.first >> arg1.second >> arg2;

			segtree.update(--arg1, arg2);
		}
		else if (inst == 1) {
			pint arg1, arg2;
			cin >> arg1.first >> arg1.second >> arg2.first >> arg2.second;
			if (arg1 > arg2) {
				swap(arg1, arg2);
			}
			cout << segtree.get_sum_2d(--arg1, --arg2) << '\n';
		}
	} while (--m > 0);

	return 0;
}