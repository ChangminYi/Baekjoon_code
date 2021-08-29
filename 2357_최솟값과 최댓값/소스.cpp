#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <functional>
#include <string>

using namespace std;

typedef pair<int, int> pint;

template <>
struct std::hash<pint> {
	std::hash<string> hasher;
	std::size_t operator() (const pint& p) const {
		string to_hash = to_string(p.first) + "0" + to_string(p.second);
		return hasher(to_hash);
	}
};

bool in_range(pint& small, pint& large) {
	if (large.first <= small.first && small.second <= large.second) {
		return true;
	}
	return false;
}

int init_segTree(unordered_map<pint, int> &segtree, vector<int>& argi, pint& max_range, bool is_maxSeg) {
	if (max_range.first == max_range.second) {
		return argi[max_range.first];
	}
	else {
		int mid = (max_range.first + max_range.second) / 2;
		pint lft = make_pair(max_range.first, mid);
		pint rgt = make_pair(mid + 1, max_range.second);

		int val_lft = init_segTree(segtree, argi, lft, is_maxSeg);
		int val_rgt = init_segTree(segtree, argi, rgt, is_maxSeg);

		if (is_maxSeg) {
			segtree.insert(make_pair(max_range, max(val_lft, val_rgt)));
		}
		else {
			segtree.insert(make_pair(max_range, min(val_lft, val_rgt)));
		}

		return segtree[max_range];
	}
}

int search_segTree(pint range, unordered_map<pint, int>& segtree, vector<int> &argi, pint max_range, bool is_maxSeg) {
	if (range == max_range) {
		if (range.first == range.second) {
			return argi[range.first];
		}
		else {
			return segtree[range];
		}
	}
	else {
		int mid = (max_range.first + max_range.second) / 2;
		pint lft = make_pair(max_range.first, mid);
		pint rgt = make_pair(mid + 1, max_range.second);

		if (in_range(range, lft)) {
			return search_segTree(range, segtree, argi, lft, is_maxSeg);
		}
		else if (in_range(range, rgt)) {
			return search_segTree(range, segtree, argi, rgt, is_maxSeg);
		}
		else {
			pint ran_lft = make_pair(range.first, mid);
			pint ran_rgt = make_pair(mid + 1, range.second);

			int sch_lft = search_segTree(ran_lft, segtree, argi, lft, is_maxSeg);
			int sch_rgt = search_segTree(ran_rgt, segtree, argi, rgt, is_maxSeg);

			if (is_maxSeg) {
				return max(sch_lft, sch_rgt);
			}
			else {
				return min(sch_lft, sch_rgt);
			}
		}
	}
}

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);
	cout.tie(nullptr);
	cout.sync_with_stdio(false);

	int n, m;
	cin >> n >> m;
	vector<int> argi(n);
	for (int& i : argi) {
		cin >> i;
	}

	pint seg_range = make_pair(0, n - 1);
	unordered_map<pint, int> max_seg, min_seg;
	init_segTree(max_seg, argi, seg_range, true);
	init_segTree(min_seg, argi, seg_range, false);

	for (int i = 0; i < m; i++) {
		pint ran;
		cin >> ran.first >> ran.second;
		ran.first--, ran.second--;
		int max_val = search_segTree(ran, max_seg, argi, seg_range, true);
		int min_val = search_segTree(ran, min_seg, argi, seg_range, false);

		cout << min_val << ' ' << max_val << '\n';
	}

	return 0;
}