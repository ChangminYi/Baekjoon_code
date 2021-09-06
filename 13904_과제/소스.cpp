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

	// ��¥ �������� ���� ����
	sort(task.rbegin(), task.rend());

	/*
	* ��¥�� �ִ��� �ڷ� �̷Ｍ �տ� ���� �ϵ��� ������
	* ������ ������ �������� ����.
	*/ 
	for (int i = max_day, idx = 0; i >= 1; i--) {
		/*
		* ���� ������ i���� �������� ũ�ų� ���� ��� ���� �켱���� ť�� �����Ѵ�.
		* �켱���� ť �ȿ��� �������� ���ð� ���ų� �� ���� �ϵ��� ������ ����ִ�.
		* �� �߿��� ���� ū ������ ������ ���� �ϸ� ������ ������ ���� ũ��.
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