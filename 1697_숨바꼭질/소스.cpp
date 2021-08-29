#include <iostream>
#include <queue>
using namespace std;

bool isInRange(int i) {
	return ((0 <= i) && (i <= 100000));
}

int bfs(int start, int toFind) {
	bool check[1000001] = { false };
	queue<pair<int, int>> q;
	q.push({ start, 0 });

	while (!q.empty()) {
		int current = q.front().first;
		int sec = q.front().second;
		q.pop();
		if (check[current]) {
			continue;
		}
		check[current] = true;

		if (current == toFind) {
			return sec;
		}
		else {
			if (isInRange(current * 2) && !check[current * 2]) {
				q.push({ current * 2, sec + 1 });
			}
			if (isInRange(current + 1) && !check[current + 1]) {
				q.push({ current + 1, sec + 1 });
			}
			if (isInRange(current - 1) && !check[current - 1]) {
				q.push({ current - 1 , sec + 1 });
			}
		}
	}
	return -1;
}

int main() {
	cin.tie(NULL);
	cin.sync_with_stdio(false);

	int su = 0, bro = 0;
	cin >> su >> bro;

	cout << bfs(su, bro);

	return 0;
}