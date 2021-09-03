#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

typedef long long lli;

int n;
vector<int> argi;
vector<int> segtree;

/*
* 세그먼트 트리 초기화 함수
* 배열의 최소값의 인덱스 저장
*/
void init_segtree(int root, int lo, int hi) {
	if (lo == hi) {
		segtree[root] = lo;
	}
	else {
		int mid = (lo + hi) / 2;

		init_segtree(2 * root, lo, mid);
		init_segtree(2 * root + 1, mid + 1, hi);

		if (argi[segtree[2 * root]] <= argi[segtree[2 * root + 1]]) {
			segtree[root] = segtree[2 * root];
		}
		else {
			segtree[root] = segtree[2 * root + 1];
		}
	}
}

/*
* 세그먼트 트리 탐색 함수
*/
int find_segtree(int root, int lo, int hi, int left, int right) {
	if (lo == left && hi == right) {
		return segtree[root];
	}
	else {
		int mid = (lo + hi) / 2;

		if (right <= mid) {
			return find_segtree(2 * root, lo, mid, left, right);
		}
		else if (mid < left) {
			return find_segtree(2 * root + 1, mid + 1, hi, left, right);
		}
		else{
			int left_idx = find_segtree(2 * root, lo, mid, left, mid);
			int right_idx = find_segtree(2 * root + 1, mid + 1, hi, mid + 1, right);

			return (argi[left_idx] <= argi[right_idx] ? left_idx : right_idx);
		}
	}
}

/*
* 일종의 분할 정복
* 현재 범위의 최대 넓이를 구한 후,
* 만약 최저 인덱스가 범위 사이에 있다면
* 그 인덱스를 제외한 양 옆의 넓이를 계산
*/
lli find_rect(int lo, int hi) {
	int min_idx = find_segtree(1, 0, n - 1, lo, hi);
	lli max_area = ((lli)hi - lo + 1) * argi[min_idx];

	if (lo < min_idx) {
		lli left_area = find_rect(lo, min_idx - 1);
		max_area = max(max_area, left_area);
	}
	if (hi > min_idx) {
		lli right_area = find_rect(min_idx + 1, hi);
		max_area = max(max_area, right_area);
	}

	return max_area;
}

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);

	while (true) {
		cin >> n;

		if (n == 0) {
			break;
		}
		else {
			argi.resize(n);
			/*
			* 세그먼트 트리의 예상 가능한 최대 크기
			* 2 ^ (ceil(log2(n)) + 1)
			* ceil(log2(n)) + 1은 예상 가능한 최대 높이
			*/
			segtree.resize(1 << ((int)ceil(log2(n)) + 1));
			for (int& i : argi) {
				cin >> i;
			}

			init_segtree(1, 0, n - 1);

			cout << find_rect(0, n - 1) << '\n';
		}
	}

	return 0;
}