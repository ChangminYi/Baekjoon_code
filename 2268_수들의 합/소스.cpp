#include <iostream>
#include <vector>

using namespace std;


typedef pair<int, int> pint;
typedef long long lli;
typedef struct NODE {
	pint bound;
	lli value;
}node;

vector<lli> argi;
vector<node> segtree;
vector<int> argi_to_seg;

lli init_segtree(int root, pint boundary) {
	if (boundary.first == boundary.second) {
		segtree[root].bound = boundary;
		segtree[root].value = argi[boundary.first];
		argi_to_seg[boundary.first] = root;
		return segtree[root].value;
	}
	else {
		int mid = (boundary.first + boundary.second) / 2;
		pint left = make_pair(boundary.first, mid);
		pint right = make_pair(mid + 1, boundary.second);

		lli sum_left = init_segtree(2 * root, left);
		lli sum_right = init_segtree(2 * root + 1, right);

		segtree[root].bound = boundary;
		segtree[root].value = sum_left + sum_right;
		return segtree[root].value;
	}
}

void replace_segtree(int rep_idx, int rep_val) {
	int seg_idx = argi_to_seg[rep_idx];
	segtree[seg_idx].value = rep_val;

	int cur = seg_idx / 2;
	while(cur >= 1){
		segtree[cur].value = segtree[2 * cur].value + segtree[2 * cur + 1].value;
		cur /= 2;
	}

	return;
}

bool in_range(pint& child, pint& mother) {
	if (mother.first <= child.first && child.second <= mother.second) {
		return true;
	}
	return false;
}

lli search_segtree(int root, pint search_bound) {
	if (segtree[root].bound == search_bound) {
		return segtree[root].value;
	}
	else {
		int mid = (segtree[root].bound.first + segtree[root].bound.second) / 2;
		pint left = make_pair(segtree[root].bound.first, mid);
		pint right = make_pair(mid + 1, segtree[root].bound.second);

		if (in_range(search_bound, left)) {
			return search_segtree(root * 2, search_bound);
		}
		else if (in_range(search_bound, right)) {
			return search_segtree(root * 2 + 1, search_bound);
		}
		else {
			pint search_left = make_pair(search_bound.first, mid);
			pint search_right = make_pair(mid + 1, search_bound.second);

			lli sum_left = search_segtree(root * 2, search_left);
			lli sum_right = search_segtree(root * 2 + 1, search_right);

			return sum_left + sum_right;
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
	argi = vector<lli>(n + 1, 0);
	argi_to_seg = vector<int>(n + 1);
	segtree = vector<node>(5 * n + 1);
	init_segtree(1, make_pair(1, n));

	while (m-- > 0) {
		int inst;
		pint arg;
		cin >> inst >> arg.first >> arg.second;

		switch (inst) {
		case 0:
			if (arg.first > arg.second) {
				swap(arg.first, arg.second);
			}
			cout << search_segtree(1, arg) << '\n';
			break;
		case 1:
			replace_segtree(arg.first, arg.second);
			break;
		}
	}

	return 0;
}