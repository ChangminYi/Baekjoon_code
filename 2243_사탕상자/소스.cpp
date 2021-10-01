#include <iostream>
#include <vector>

using namespace std;

constexpr int MAX_NUM = 1000000;

int n;
vector<int> segtree((MAX_NUM + 1) << 2, 0);

/*
* ��ü ������ ���ؼ� ���� �� ������Ʈ.
* target�� ������ ��, val�� �߰�(Ȥ�� ����)�� ������ ��
* ���� ������ ������Ʈ�� �ϰ�, �ڽ� ������ �߿��� �ش��ϴ� ��������
* ��������� �Լ� ȣ���ϸ鼭 ������ ������Ʈ�Ѵ�.
*/
void update_seg(int idx, int target, int val, int lo, int hi) {
	segtree[idx] += val;

	if (lo == hi) {
		return;
	}
	else {
		int mid = (lo + hi) / 2;

		if (lo <= target && target <= mid) {
			update_seg(2 * idx, target, val, lo, mid);
		}
		else {
			update_seg(2 * idx + 1, target, val, mid + 1, hi);
		}
	}
}

/*
* ���� ������ �� ������ �Լ�. target�� ������ �����̴�.
* ���� �������� ���� ������ ���� �ڽĺ��� �۰ų� ���ٸ� ���� �ڽ����� Ž���� �ϰ� �ȴ�.
* ������ �ڽ����� ���� �Ǵ� ���, ���� �ڽ��� ������ �����ϰ� Ž���� �ؾ� �ϱ� ������
* target���� ���� �ڽ��� ����ŭ �� ���� ���ڷ� �Ѱ��־� Ž���� �Ѵ�.
*/
int get_query(int idx, int target, int lo, int hi) {
	if (lo == hi) {
		return lo;
	}
	else {
		int mid = (lo + hi) / 2;
		int pivot = segtree[2 * idx];

		if (target <= pivot) {
			return get_query(2 * idx, target, lo, mid);
		}
		else {
			return get_query(2 * idx + 1, target - pivot, mid + 1, hi);
		}
	}
}

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);

	cin >> n;
	do {
		int inst, arg1, arg2;
		cin >> inst;

		if (inst == 1) {
			cin >> arg1;
			int res_num = get_query(1, arg1, 1, MAX_NUM);

			cout << res_num << '\n';
			/*
			* ã�� ������ �ϳ� �� �־�� �Ѵ�.
			*/
			update_seg(1, res_num, -1, 1, MAX_NUM);
		}
		else if (inst == 2) {
			cin >> arg1 >> arg2;
			update_seg(1, arg1, arg2, 1, MAX_NUM);
		}
	} while (--n > 0);

	return 0;
}