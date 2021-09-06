#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

typedef pair<int, int> pint;

int n, max_day = 0, score_sum = 0;
vector<pint> task;
priority_queue<int> pq;

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);

	cin >> n;
	task.resize(n);
	for (pint& p : task) {
		cin >> p.first >> p.second;
		max_day = max(max_day, p.first);
	}

	// 날짜 기준으로 역순 정렬
	sort(task.rbegin(), task.rend());

	/*
	* 날짜를 최대한 뒤로 미뤄서 앞에 많은 일들이 들어가도록
	* 마지막 날부터 역순으로 센다.
	*/ 
	for (int i = max_day, idx = 0; i >= 1; i--) {
		/*
		* 현재 마감일 i보다 마감일이 크거나 같은 모든 일을 우선순위 큐에 삽입한다.
		* 우선순위 큐 안에는 마감일이 오늘과 같거나 더 뒤인 일들의 점수만 들어있다.
		* 그 중에서 가장 큰 점수를 가지는 일을 하면 점수의 총합이 가장 크다.
		*/
		while (idx < n && task[idx].first >= i) {
			pq.push(task[idx++].second);
		}

		if (!pq.empty()) {
			score_sum += pq.top();
			pq.pop();
		}
	}

	cout << score_sum;

	return 0;
}