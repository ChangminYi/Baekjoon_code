#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <numeric>

using namespace std;

struct node{
	int number;
	int left, right;
	int height;
	node(int num = 0, int l = 0, int r = 0, int h = 0) : number(num), left(0), right(0), height(h) {}
};

int n, q;
vector<node> arg;
vector<int> parent;

int _find(int x){
	return parent[x] == x ? x : parent[x] = _find(parent[x]);
}

void _union(int x, int y) {
	int f_x = _find(x), f_y = _find(y);
	if (f_x > f_y) {
		swap(f_x, f_y);
	}
	parent[f_y] = f_x;
}

bool cmp_by_dir(const node& lhs, const node& rhs) {
	return lhs.left == lhs.right ? lhs.right < rhs.right : lhs.left < rhs.left;
}

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);

	cin >> n >> q;
	arg.resize(n);
	parent.resize(n);
	iota(parent.begin(), parent.end(), 0);
	for (int i = 0; i < n; i++) {
		arg[i].number = i;
		cin >> arg[i].left >> arg[i].right >> arg[i].height;
	}

	sort(arg.begin(), arg.end(), cmp_by_dir);
	int max_right = arg[0].right;
	int par_num = arg[0].number;
	for (int i = 1; i < n; i++) {
		node& cur = arg[i];

		if (cur.left <= max_right) {
			max_right = max(max_right, cur.right);
			_union(par_num, cur.number);
		}
		else {
			max_right = cur.right;
			par_num = cur.number;
		}
	}

	do {
		int n1, n2;
		cin >> n1 >> n2;
		n1--, n2--;

		cout << (_find(n1) == _find(n2) ? 1 : 0) << '\n';
	} while (--q > 0);

	return 0;
}