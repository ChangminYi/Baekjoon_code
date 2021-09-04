#include <iostream>
#include <vector>
#include <queue>
#include <functional>

using namespace std;

int n, max_time;
vector<int> argi;
priority_queue<int, vector<int>, greater<int>> pq;

bool line_match(int line_num) {
	//공정 수만큼 초기값 0 삽입
	for (int i = 0; i < line_num; i++) {
		pq.push(0);
	}

	//우선순위 큐를 사용하여 가장 빨리 끝나는 공정 자동 매칭
	for (int i = 0; i < n; i++) {
		int cur = pq.top();
		pq.pop();

		cur += argi[i];
		pq.push(cur);
	}

	//우선순위 큐의 가장 마지막 값이 최대 소요 시간
	while (true) {
		int cur = pq.top();
		pq.pop();

		if (pq.empty()) {
			return cur <= max_time;
		}
	}
}

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);

	cin >> n >> max_time;
	argi.resize(n);
	for (int& i : argi) {
		cin >> i;
	}

	/*
	* 각각 최소 공정 수, 최대 공정 수
	* 공정 수로 이분탐색
	*/
	int lo = 1, hi = n;
	while (lo < hi) {
		int mid = (lo + hi) / 2;
		line_match(mid) ? hi = mid : lo = mid + 1;
	}

	cout << lo;

	return 0;
}