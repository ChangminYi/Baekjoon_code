#include <iostream>
#include <vector>

using namespace std;

typedef long long lli;
typedef pair<int, int> pint;

const lli DIV = 1000000007;
vector<lli> argi;
vector<int> argi_to_seg;
vector<lli> segtree;

lli init_segtree(int root, int left, int right) {
	if (left == right) {
		argi_to_seg[left] = root;
		return segtree[root] = argi[left];
	}
	else {
		int mid = (left + right) / 2;
		return segtree[root] = (init_segtree(2 * root, left, mid) * init_segtree(2 * root + 1, mid + 1, right)) % DIV;
	}
}

void replace_segtree(int rep_idx, lli rep_val) {
	int seg_idx = argi_to_seg[rep_idx];
	segtree[seg_idx] = rep_val;

	while ((seg_idx /= 2) > 0) {
		segtree[seg_idx] = (segtree[2 * seg_idx] * segtree[2 * seg_idx + 1]) % DIV;
	}
}

lli get_mult(int root, int root_left, int root_right, int s_left, int s_right) {
	if (root_left == s_left && root_right == s_right) {
		return segtree[root];
	}
	else {
		int mid = (root_left + root_right) / 2;

		if (s_right <= mid) {
			return get_mult(2 * root, root_left, mid, s_left, s_right);
		}
		else if (mid < s_left) {
			return get_mult(2 * root + 1, mid + 1, root_right, s_left, s_right);
		}
		else {
			lli left_val = get_mult(2 * root, root_left, mid, s_left, mid);
			lli right_val = get_mult(2 * root + 1, mid + 1, root_right, mid + 1, s_right);

			return (left_val * right_val) % DIV;
		}
	}
}

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);
	cout.tie(nullptr);
	cout.sync_with_stdio(false);

	int n, m, k;
	cin >> n >> m >> k;

	argi = vector<lli>(n + 1);
	argi_to_seg = vector<int>(n + 1);
	segtree = vector<lli>(4 * (n + 1) + 1);

	for (int i = 1; i <= n; i++) {
		cin >> argi[i];
	}
	init_segtree(1, 1, n);

	for (int i = 0; i < m + k; i++) {
		int inst, arg1, arg2;
		cin >> inst >> arg1 >> arg2;

		switch (inst) {
		case 1:
			replace_segtree(arg1, arg2);
			break;
		case 2:
			cout << get_mult(1, 1, n, arg1, arg2) << '\n';
			break;
		}
	}

	return 0;
}