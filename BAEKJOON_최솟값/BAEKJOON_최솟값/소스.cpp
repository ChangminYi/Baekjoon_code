#include <iostream>
#include <map>
#include <vector>

using namespace std;

typedef pair<int, int> pint;

int init_segtree(map<pint, int>& segtree, vector<int>& argi, pint& root) {
	if (root.first == root.second) {
		return argi[root.first];
	}
	else {
		int mid = (root.first + root.second) / 2;
		pint lft = make_pair(root.first, mid);
		pint rgt = make_pair(mid + 1, root.second);

		int val_lft = init_segtree(segtree, argi, lft);
		int val_rgt = init_segtree(segtree, argi, rgt);

		segtree.insert(make_pair(root, min(val_lft, val_rgt)));

		return segtree[root];
	}
}

bool in_range(const pint& child, const pint& mother) {
	if (mother.first <= child.first && child.second <= mother.second) {
		return true;
	}
	return false;
}

int search_segtree(pint& to_find, map<pint, int>& segtree, vector<int>& argi, pint& root) {
	if (to_find == root) {
		if (to_find.first == to_find.second) {
			return argi[to_find.first];
		}
		else {
			return segtree[to_find];
		}
	}
	else {
		int mid = (root.first + root.second) / 2;
		pint lft = make_pair(root.first, mid);
		pint rgt = make_pair(mid + 1, root.second);

		if (in_range(to_find, lft)) {
			return search_segtree(to_find, segtree, argi, lft);
		}
		else if(in_range(to_find, rgt)){
			return search_segtree(to_find, segtree, argi, rgt);
		}
		else{
			pint sch_lft = make_pair(to_find.first, mid);
			pint sch_rgt = make_pair(mid + 1, to_find.second);

			int val_lft = search_segtree(sch_lft, segtree, argi, lft);
			int val_rgt = search_segtree(sch_rgt, segtree, argi, rgt);

			return min(val_lft, val_rgt);
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
	vector<int> argi(n + 1);
	for (int i = 1; i <= n; i++) {
		cin >> argi[i];
	}

	//min_segtree
	pint seg_range = make_pair(1, n);
	map<pint, int> segtree;
	init_segtree(segtree, argi, seg_range);

	for (int i = 0; i < m; i++) {
		pint tmp_range;
		cin >> tmp_range.first >> tmp_range.second;
		
		cout << search_segtree(tmp_range, segtree, argi, seg_range) << '\n';
	}

	return 0;
}