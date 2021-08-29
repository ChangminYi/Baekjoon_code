#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<pair<int, int>> parent(1000001, {-1, 0});

int main() {
	int N = 0;
	cin >> N;

	queue<int> togo;
	togo.push(1);
	while (!togo.empty()) {
		int cur = togo.front();
		togo.pop();

		if (cur == N) {
			cout << parent[cur].second << '\n';
			int ind = cur;
			while (true) {
				cout << ind << ' ';
				ind = parent[ind].first;
				if (ind == -1) {
					break;
				}
			}
			break;
		}
		else {
			vector<int> nxt = { cur + 1, cur * 2, cur * 3 };
			for (int i : nxt) {
				if (i <= N && parent[i].second == 0) {
					parent[i].first = cur;
					parent[i].second = parent[cur].second + 1;
					togo.push(i);
				}
			}
		}
	}

	return 0;
}