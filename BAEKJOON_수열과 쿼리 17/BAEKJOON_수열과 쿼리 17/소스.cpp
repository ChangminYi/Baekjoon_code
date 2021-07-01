#include <iostream>
#include <vector>
#include <unordered_map>
#include <functional>

using namespace std;

typedef pair<int, int> pint;

template <>
struct std::hash<pint> {
	std::hash<long long> hasher;
	std::size_t operator() (const pint& p) const {
		long long to_hash = ((long long)p.first << 32) | p.second;
		return hasher(to_hash);
	}
};

pint NO_PARENT = make_pair(-1, -1);
vector<int> argi;
unordered_map<pint, int> segtree;	//min_segtree
unordered_map<pint, pint> parent;

int init_segtree(pint &root) {
	if (root.first == root.second) {
		segtree.insert(make_pair(root, argi[root.first]));
		return argi[root.first];
	}
	else {
		int mid = (root.first + root.second) / 2;
		pint lft = make_pair(root.first, mid);
		pint rgt = make_pair(mid + 1, root.second);

		int val_lft = init_segtree(lft);
		int val_rgt = init_segtree(rgt);
		segtree.insert(make_pair(root, min(val_lft, val_rgt)));

		return segtree[root];
	}
}

void init_parent_umap(pint &root){
	int mid = (root.first + root.second) / 2;
	pint lft = make_pair(root.first, mid);
	pint rgt = make_pair(mid + 1, root.second);

	parent.insert(make_pair(lft, root));
	parent.insert(make_pair(rgt, root));

	if (lft.first < lft.second) {
		init_parent_umap(lft);
	}
	if (rgt.first < rgt.second) {
		init_parent_umap(rgt);
	}
}

bool in_range(pint& child, pint& mother) {
	if (mother.first <= child.first && child.second <= mother.second) {
		return true;
	}
	return false;
}

int search_segtree(pint& search_range, pint &root) {
	if (search_range == root) {
		return segtree[search_range];
	}
	else {
		int mid = (root.first + root.second) / 2;
		pint lft = make_pair(root.first, mid);
		pint rgt = make_pair(mid + 1, root.second);

		if (in_range(search_range, lft)) {
			return search_segtree(search_range, lft);
		}
		else if (in_range(search_range, rgt)) {
			return search_segtree(search_range, rgt);
		}
		else {
			pint sch_lft = make_pair(search_range.first, mid);
			pint sch_rgt = make_pair(mid + 1, search_range.second);

			int val_lft = search_segtree(sch_lft, lft);
			int val_rgt = search_segtree(sch_rgt, rgt);

			return min(val_lft, val_rgt);
		}
	}
}

void replace_segtree(int idx, int rep_val) {
	pint rep_idx = make_pair(idx, idx);
	segtree[rep_idx] = rep_val;

	pint chi = rep_idx, par = parent[chi];
	while (par != NO_PARENT) {
		pint another_chi;
		if (chi.first == par.first) {
			another_chi = make_pair(chi.second + 1, par.second);
		}
		else {
			another_chi = make_pair(par.first, chi.first - 1);
		}

		int val_one = segtree[chi];
		int val_two = segtree[another_chi];

		segtree[par] = min(val_one, val_two);
		chi = par;
		par = parent[par];
	}
}

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);
	cout.tie(nullptr);
	cout.sync_with_stdio(false);

	int n, m;
	cin >> n;
	argi = vector<int>(n + 1);
	for (int i = 1; i <= n; i++) {
		cin >> argi[i];
	}
	
	pint seg_root = make_pair(1, n);
	init_segtree(seg_root);
	parent.insert(make_pair(seg_root, NO_PARENT));
	init_parent_umap(seg_root);
	
	cin >> m;
	while (m-- > 0) {
		pint arg;
		int inst;
		cin >> inst >> arg.first >> arg.second;

		switch (inst) {
		case 1:
			replace_segtree(arg.first, arg.second);
			break;
		case 2:
			cout << search_segtree(arg, seg_root) << '\n';
			break;
		}
	}

	return 0;
}