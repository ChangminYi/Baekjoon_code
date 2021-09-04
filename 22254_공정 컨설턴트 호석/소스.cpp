#include <iostream>
#include <vector>
#include <queue>
#include <functional>

using namespace std;

int n, max_time;
vector<int> argi;
priority_queue<int, vector<int>, greater<int>> pq;

bool line_match(int line_num) {
	//���� ����ŭ �ʱⰪ 0 ����
	for (int i = 0; i < line_num; i++) {
		pq.push(0);
	}

	//�켱���� ť�� ����Ͽ� ���� ���� ������ ���� �ڵ� ��Ī
	for (int i = 0; i < n; i++) {
		int cur = pq.top();
		pq.pop();

		cur += argi[i];
		pq.push(cur);
	}

	//�켱���� ť�� ���� ������ ���� �ִ� �ҿ� �ð�
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
	* ���� �ּ� ���� ��, �ִ� ���� ��
	* ���� ���� �̺�Ž��
	*/
	int lo = 1, hi = n;
	while (lo < hi) {
		int mid = (lo + hi) / 2;
		line_match(mid) ? hi = mid : lo = mid + 1;
	}

	cout << lo;

	return 0;
}