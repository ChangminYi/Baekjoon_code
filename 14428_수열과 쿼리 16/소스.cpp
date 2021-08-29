#include <iostream>
#include <vector>

using namespace std;

typedef pair<int, int> pint;
typedef class NODE {
public:
	pint range;
	pint child_left, child_right;
	int value;
} node;

const pint TERMINAL = make_pair(-1, -1);

vector<int> argi;
vector<int> argi_to_seg;
vector<node> segtree;

int init_segtree(int root, pint& range) {
	if (range.first == range.second) {
		segtree[root].range = range;
		segtree[root].child_left = TERMINAL;
		segtree[root].child_right = TERMINAL;
		segtree[root].value = range.first;
		argi_to_seg[range.first] = root;
		return range.first;
	}
	else {
		int mid = (range.first + range.second) / 2;

		segtree[root].range = range;
		segtree[root].child_left = make_pair(range.first, mid);
		segtree[root].child_right = make_pair(mid + 1, range.second);

		int val_left = argi[init_segtree(2 * root, segtree[root].child_left)];
		int val_right = argi[init_segtree(2 * root + 1, segtree[root].child_right)];

		segtree[root].value = (val_left <= val_right ? segtree[2 * root].value : segtree[2 * root + 1].value);

		return segtree[root].value;
	}
}

void replace_segtree(int rep_idx, int rep_val) {
	argi[rep_idx] = rep_val;

	int par = argi_to_seg[rep_idx] / 2;
	while (par > 0) {
		int val_lft = argi[segtree[2 * par].value];
		int val_rgt = argi[segtree[2 * par + 1].value];

		segtree[par].value = (val_lft <= val_rgt ? segtree[2 * par].value : segtree[2 * par + 1].value);
		par /= 2;
	}

	return;
}

bool in_range(pint& small, pint& large) {
	if (large.first <= small.first && small.second <= large.second) {
		return true;
	}
	return false;
}

int seek_segtree(int root, pint& seek_range) {
	if (segtree[root].range == seek_range) {
		return segtree[root].value;
	}
	else {
		if (in_range(seek_range, segtree[root].child_left)) {
			return seek_segtree(2 * root, seek_range);
		}
		else if (in_range(seek_range, segtree[root].child_right)) {
			return seek_segtree(2 * root + 1, seek_range);
		}
		else {
			pint range_left = make_pair(seek_range.first, segtree[root].child_left.second);
			pint range_right = make_pair(segtree[root].child_right.first, seek_range.second);

			int val_lft = seek_segtree(2 * root, range_left);
			int val_rgt = seek_segtree(2 * root + 1, range_right);

			return (argi[val_lft] <= argi[val_rgt] ? val_lft : val_rgt);
		}
	}
}

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);
	cout.tie(nullptr);
	cout.sync_with_stdio(false);

	int n;
	cin >> n;
	argi = vector<int>(n + 1);
	argi_to_seg = vector<int>(n + 1);
	segtree = vector<node>(4 * (n + 1) + 1);
	for (int i = 1; i <= n; i++) {
		cin >> argi[i];
	}
	pint max_range = make_pair(1, n);
	init_segtree(1, max_range);


	int m;
	cin >> m;
	do {
		int inst;
		pint arg;
		cin >> inst >> arg.first >> arg.second;

		switch (inst) {
		case 1:
			replace_segtree(arg.first, arg.second);
			break;
		case 2:
			cout << seek_segtree(1, arg) << '\n';
			break;
		}
	} while (--m > 0);



	return 0;
}