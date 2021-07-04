#include <iostream>
#include <vector>

using namespace std;

typedef pair<int, int> pint;
typedef long long lli;
typedef struct NODE {
	pint range;
	lli value;
} node;

vector<lli> argi;
vector<int> argi_to_seg;
vector<node> segtree;

lli init_segtree(int index, pint& root) {
	if (root.first == root.second) {
		segtree[index].range = root;
		segtree[index].value = argi[root.first];
		argi_to_seg[root.first] = index;
		return segtree[index].value;
	}
	else {
		int mid = (root.first + root.second) / 2;
		pint child_left = make_pair(root.first, mid);
		pint child_right = make_pair(mid + 1, root.second);

		segtree[index].range = root;
		segtree[index].value = init_segtree(2 * index, child_left) + init_segtree(2 * index + 1, child_right);
		return segtree[index].value;
	}
}

void replace_segtree(int rep_index, int rep_value) {
	int seg_idx = argi_to_seg[rep_index];
	segtree[seg_idx].value = rep_value;

	int cur = seg_idx / 2;
	while (cur >= 1) {
		segtree[cur].value = segtree[cur * 2].value + segtree[cur * 2 + 1].value;
		cur /= 2;
	}
	
	return;
}

bool in_range(pint& small, pint& large) {
	if (large.first <= small.first && small.second <= large.second) {
		return true;
	}
	return false;
}

lli seek_segtree(int index, pint& to_seek) {
	if (segtree[index].range == to_seek) {
		return segtree[index].value;
	}
	else {
		int mid = (segtree[index].range.first + segtree[index].range.second) / 2;
		pint seek_left = make_pair(segtree[index].range.first, mid);
		pint seek_right = make_pair(mid + 1, segtree[index].range.second);

		if (in_range(to_seek, seek_left)) {
			return seek_segtree(index * 2, to_seek);
		}
		else if (in_range(to_seek, seek_right)) {
			return seek_segtree(index * 2 + 1, to_seek);
		}
		else {
			pint split_left = make_pair(to_seek.first, mid);
			pint split_right = make_pair(mid + 1, to_seek.second);

			return seek_segtree(index * 2, split_left) + seek_segtree(index * 2 + 1, split_right);
		}
	}
}

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);
	cout.tie(nullptr);
	cout.sync_with_stdio(false);

	int n, q;
	cin >> n >> q;
	argi = vector<lli>(n + 1);
	argi_to_seg = vector<int>(n + 1);
	segtree = vector<node>(4 * (n + 1) + 1);
	for (int i = 1; i <= n; i++) {
		cin >> argi[i];
	}
	pint seg_root = make_pair(1, n);
	init_segtree(1, seg_root);

	do {
		pint to_sum;
		int r_idx, r_val;
		cin >> to_sum.first >> to_sum.second >> r_idx >> r_val;
		if (to_sum.first > to_sum.second) {
			swap(to_sum.first, to_sum.second);
		}

		cout << seek_segtree(1, to_sum) << '\n';

		replace_segtree(r_idx, r_val);
	} while (--q > 0);

	return 0;
}