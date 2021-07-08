#include <iostream>
#include <vector>

using namespace std;

typedef long long lli;
typedef pair<int, int> pint;
typedef pair<lli, lli> plli;
typedef struct NODE {
	pint range;
	pint c_left, c_right;
	lli value;
} node;

const pint NO_CHILD = make_pair(-1, -1);
vector<lli> argi;
vector<node> segtree;
vector<int> argi_to_seg;

lli init_segtree(int idx, pint& range) {
	if (range.first == range.second) {
		segtree[idx].range = range;
		segtree[idx].c_left = NO_CHILD;
		segtree[idx].c_right = NO_CHILD;
		argi_to_seg[range.first] = idx;
		return segtree[idx].value = argi[range.first];
	}
	else {
		segtree[idx].range = range;

		int mid = (range.first + range.second) / 2;
		segtree[idx].c_left = make_pair(range.first, mid);
		segtree[idx].c_right = make_pair(mid + 1, range.second);
		return segtree[idx].value = init_segtree(2 * idx, segtree[idx].c_left) + init_segtree(2 * idx + 1, segtree[idx].c_right);
	}
}

void replace_segtree(int rep_idx, lli rep_val) {
	int seg_idx = argi_to_seg[rep_idx];
	segtree[seg_idx].value = rep_val;

	seg_idx /= 2;
	while (seg_idx > 0) {
		segtree[seg_idx].value = segtree[2 * seg_idx].value + segtree[2 * seg_idx + 1].value;
		seg_idx /= 2;
	}

	return;
}

bool in_range(pint& small, pint& large) {
	if (large.first <= small.first && small.second <= large.second) {
		return true;
	}
	return false;
}

lli get_sum(int idx, pint seek_range) {
	if (segtree[idx].range == seek_range) {
		return segtree[idx].value;
	}
	else {		
		if (in_range(seek_range, segtree[idx].c_left)) {
			return get_sum(2 * idx, seek_range);
		}
		else if (in_range(seek_range, segtree[idx].c_right)) {
			return get_sum(2 * idx + 1, seek_range);
		}
		else {
			int mid = (segtree[idx].range.first + segtree[idx].range.second) / 2;
			pint seek_left = make_pair(seek_range.first, mid);
			pint seek_right = make_pair(mid + 1, seek_range.second);
			return get_sum(2 * idx, seek_left) + get_sum(2 * idx + 1, seek_right);
		}
	}
}

int main(){
	cin.tie(nullptr);
	cin.sync_with_stdio(false);
	cout.tie(nullptr);
	cout.sync_with_stdio(false);

	int n, m, k;
	cin >> n >> m >> k;

	pint root_range = make_pair(1, n);
	argi = vector<lli>(n + 1);
	argi_to_seg = vector<int>(n + 1);
	segtree = vector<node>(4 * (n + 1) + 1);

	for (int i = 1; i <= n; i++) {
		cin >> argi[i];
	}
	init_segtree(1, root_range);

	for (int i = 0; i < m + k; i++) {
		int inst;
		pair<int, lli> arg;
		cin >> inst >> arg.first >> arg.second;

		switch (inst) {
		case 1:
			replace_segtree(arg.first, arg.second);
			break;
		case 2:
			cout << get_sum(1, make_pair(arg.first, (int)arg.second)) << '\n';
			break;
		}
	}

	return 0;
}