#include <iostream>
#include <vector>

using namespace std;

constexpr int MAX_NUM = 1000000;

int n;
vector<int> segtree((MAX_NUM + 1) << 2, 0);

/*
* 전체 구간에 대해서 사탕 수 업데이트.
* target이 사탕의 맛, val이 추가(혹은 제거)할 사탕의 수
* 현재 구간에 업데이트를 하고, 자식 구간들 중에서 해당하는 구간으로
* 재귀적으로 함수 호출하면서 끝까지 업데이트한다.
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
* 빼낼 사탕의 값 얻어오는 함수. target이 사탕의 순위이다.
* 현재 구간에서 사탕 순위가 왼쪽 자식보다 작거나 같다면 왼쪽 자식으로 탐색을 하게 된다.
* 오른쪽 자식으로 가게 되는 경우, 왼쪽 자식의 구간을 제외하고 탐색을 해야 하기 때문에
* target에서 왼쪽 자식의 값만큼 뺀 값을 인자로 넘겨주어 탐색을 한다.
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
			* 찾은 사탕을 하나 빼 주어야 한다.
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