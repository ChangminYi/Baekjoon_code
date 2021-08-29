#include <iostream>
#include <vector>

using namespace std;

class node {
public:
	int range_lo, range_hi;
	node* left, * right;
	int idx;

	node() : range_lo(0), range_hi(0), left(nullptr), right(nullptr), idx(0) {};
	int init(vector<int>& argi, int lo, int hi) {
		this->range_lo = lo;
		this->range_hi = hi;
		if (lo == hi) {
			this->idx = lo;
			return this->idx;
		}
		else {
			int mid = (lo + hi) / 2;
			this->left = new node;
			this->right = new node;

			int res_left = left->init(argi, lo, mid);
			int res_right = right->init(argi, mid + 1, hi);
			this->idx = (argi[res_left] <= argi[res_right] ? res_left : res_right);
			return this->idx;
		}
	}
	void update(vector<int>& argi, int idx, int new_val) {
		if (this->range_lo == this->range_hi && range_lo == idx) {
			argi[idx] = new_val;
		}
		else {
			int mid = (this->range_lo + this->range_hi) / 2;
			if (idx <= mid) {
				this->left->update(argi, idx, new_val);
			}
			else {
				this->right->update(argi, idx, new_val);
			}
			int l_val = this->left->idx;
			int r_val = this->right->idx;

			this->idx = (argi[l_val] <= argi[r_val] ? l_val : r_val);
		}
	}
};

int n, m;
vector<int> argi;

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);

	cin >> n;
	argi = vector<int>(n + 1);
	for (int i = 1; i <= n; i++) {
		cin >> argi[i];
	}
	node segtree;
	segtree.init(argi, 1, n);

	cin >> m;
	do {
		int inst;
		cin >> inst;

		if (inst == 1) {
			int arg1, arg2;
			cin >> arg1 >> arg2;
			segtree.update(argi, arg1, arg2);
		}
		else if (inst == 2) {
			cout << segtree.idx << '\n';
		}
	} while (--m > 0);

	return 0;
}