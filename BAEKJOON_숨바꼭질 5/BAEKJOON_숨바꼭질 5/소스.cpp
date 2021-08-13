#include <iostream>
#include <vector>
#include <queue>

using namespace std;

typedef pair<int, int> pint;

const int MAX = 500001;
const int NOT_VISIT = -1;

int n, k;
vector<vector<int>> min_time(2, vector<int>(MAX, NOT_VISIT));
queue<pint> que;

bool in_range(int x) {
	return (0 <= x && x < MAX);
}

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);

	cin >> n >> k;

	int res = MAX;
	min_time[0][n] = 0;
	que.push(make_pair(n, 0));
	while (!que.empty()) {
		int cur = que.front().first;
		int time = que.front().second;
		int cur_idx = (time + 1) % 2;
		que.pop();

		if (in_range(cur + 1) && min_time[cur_idx][cur + 1] == NOT_VISIT) {
			min_time[cur_idx][cur + 1] = time + 1;
			que.push(make_pair(cur + 1, time + 1));
		}
		if (in_range(cur - 1) && min_time[cur_idx][cur - 1] == NOT_VISIT) {
			min_time[cur_idx][cur - 1] = time + 1;
			que.push(make_pair(cur - 1, time + 1));
		}
		if (in_range(2 * cur) && min_time[cur_idx][2 * cur] == NOT_VISIT) {
			min_time[cur_idx][2 * cur] = time + 1;
			que.push(make_pair(2 * cur, time + 1));
		}
	}

	int time_cnt = 0;
	int bro_pos = k;
	while (in_range(bro_pos)) {
		if (min_time[time_cnt % 2][bro_pos] != NOT_VISIT && min_time[time_cnt % 2][bro_pos] <= time_cnt) {
			res = min(res, time_cnt);
		}

		time_cnt++;
		bro_pos += time_cnt;
	}

	cout << (res == MAX ? -1 : res);

	return 0;
}