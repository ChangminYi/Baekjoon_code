#include <iostream>
#include <queue>
#include <string>
#include <vector>

using namespace std;

string getAns(int start, int toFind) {
	queue<pair<int, string>> q;
	vector<bool> visited(10000, false);

	q.push(make_pair(start, ""));
	visited[start] = true;
	while (!q.empty()) {
		int now = q.front().first;
		string way = q.front().second;
		q.pop();

		if (now == toFind) {
			return way;
		}
		else {
			int next = (now * 2) % 10000;

			if (!visited[next]) {
				visited[next] = true;
				q.push(make_pair(next, way + 'D'));
			}
			if (now == 0) {
				next = 9999;
			}
			else {
				next = now - 1;
			}
			if (!visited[next]) {
				visited[next] = true;
				q.push(make_pair(next, way + 'S'));
			}
			if (now != 0) {
				next = (now % 1000) * 10 + now / 1000;

				if (!visited[next]) {
					visited[next] = true;
					q.push(make_pair(next, way + 'L'));
				}

				next = (now / 10) + (now % 10) * 1000;
				if (!visited[next]) {
					visited[next] = true;
					q.push(make_pair(next, way + 'R'));
				}
			}
		}
	}

	return "";
}

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);

	int N;
	cin >> N;

	for (int i = 0, temp[2]; i < N; i++) {
		cin >> temp[0] >> temp[1];
		cout << getAns(temp[0], temp[1]) << '\n';
	}

	return 0;
}