#include <iostream>

using namespace std;

const int MAX_ARG = 250'000;
const int MAX_RANGE = (1 << 16) + 1;
const int MAX_SEG = 4 * MAX_RANGE + 1;

int n, k;
int arg[MAX_ARG], segtree[MAX_SEG];
long long sum = 0;

void update_seg(int idx, int lo, int hi, int new_idx, int new_val) {
	if (lo == hi) {
		segtree[idx] += new_val;
	}
	else {
		int mid = (lo + hi) / 2;
		if (new_idx <= mid) update_seg(2 * idx, lo, mid, new_idx, new_val);
		else update_seg(2 * idx + 1, mid + 1, hi, new_idx, new_val);
		segtree[idx] = segtree[2 * idx] + segtree[2 * idx + 1];
	}
}

int get_query(int idx, int lo, int hi, int val) {
	if (lo == hi) {
		return lo;
	}
	else {
		int mid = (lo + hi) / 2;
		if (val <= segtree[2 * idx]) return get_query(2 * idx, lo, mid, val);
		else return get_query(2 * idx + 1, mid + 1, hi, val - segtree[2 * idx]);
	}
}

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);

	/*
	* 세그먼트 트리. 일정 범위 내에서, 값의 분포를 세그먼트 트리로 나타낸다.
	* 문제에서 값의 범위는 (0, 65536)이므로, 각 값이 몇 번 나오는지를
	* 세그먼트 트리에 저장하고, 중간에 존재하는 값을 탐색하면 된다.
	*/

	cin >> n >> k;
	for (int i = 0; i < n; i++) {
		cin >> arg[i];
	}

	for (int i = 0; i < k - 1; i++) {
		update_seg(1, 0, MAX_RANGE - 1, arg[i], 1);
	}
	for (int i = k - 1, lb = 0; i < n; i++, lb++) {
		update_seg(1, 0, MAX_RANGE - 1, arg[i], 1);
		sum += get_query(1, 0, MAX_RANGE - 1, (k + 1) / 2);
		update_seg(1, 0, MAX_RANGE - 1, arg[lb], -1);
	}
	cout << sum;

	return 0;
}