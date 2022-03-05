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
	* ���׸�Ʈ Ʈ��. ���� ���� ������, ���� ������ ���׸�Ʈ Ʈ���� ��Ÿ����.
	* �������� ���� ������ (0, 65536)�̹Ƿ�, �� ���� �� �� ����������
	* ���׸�Ʈ Ʈ���� �����ϰ�, �߰��� �����ϴ� ���� Ž���ϸ� �ȴ�.
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