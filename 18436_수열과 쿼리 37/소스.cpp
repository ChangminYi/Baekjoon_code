#include <iostream>
#include <vector>

using namespace std;

class node {
private:
	int range_lo = 0, range_hi = 0;
	int count = 0;
	node* left = nullptr;
	node* right = nullptr;

	bool is_terminal() {
		return this->range_lo == this->range_hi;
	}
public:
	int init(const vector<int>& argi, const int lo, const int hi) {
		this->range_lo = lo, this->range_hi = hi;

		if (lo == hi) {
			return this->count = (argi[lo] % 2 == 0 ? 1 : 0);
		}
		else{
			int mid = (lo + hi) / 2;
			left = new node, right = new node;
			return this->count = left->init(argi, lo, mid) + right->init(argi, mid + 1, hi);
		}
	}
	void update(vector<int> &argi, const int &idx, const int &new_val) {
		if (this->is_terminal() && this->range_lo == idx) {
			argi[idx] = new_val;
			this->count = (argi[idx] % 2 == 0 ? 1 : 0);
		}
		else {
			int mid = (this->range_lo + this->range_hi) / 2;
			if (idx <= mid) {
				this->left->update(argi, idx, new_val);
			}
			else {
				this->right->update(argi, idx, new_val);
			}
			this->count = this->left->count + this->right->count;
		}
	}
	int get_count(const int &s_lo, const int &s_hi) {
		if (this->range_lo == s_lo && this->range_hi == s_hi) {
			return this->count;
		}
		else {
			int mid = (this->range_lo + this->range_hi) / 2;

			if (s_hi <= mid) {
				return this->left->get_count(s_lo, s_hi);
			}
			else if (mid < s_lo) {
				return this->right->get_count(s_lo, s_hi);
			}
			else {
				return this->left->get_count(s_lo, mid) + this->right->get_count(mid + 1, s_hi);
			}
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
	cin >> m;

	node segtree;
	segtree.init(argi, 1, n);

	do {
		int inst, arg1, arg2;
		cin >> inst >> arg1 >> arg2;

		if (inst == 1) {
			segtree.update(argi, arg1, arg2);
		}
		else if(inst == 2){
			cout << segtree.get_count(arg1, arg2) << '\n';
		}
		else if (inst == 3) {
			cout << (arg2 - arg1 + 1) - segtree.get_count(arg1, arg2) << '\n';
		}
	} while (--m > 0);

	return 0;
}