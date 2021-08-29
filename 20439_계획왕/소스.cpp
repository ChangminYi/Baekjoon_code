#include <iostream>
#include <vector>

using namespace std;

typedef pair<int, int> pint;

const int MAX = 1440;
const int NOT_VISIT = -1;
const int ACCEPT = 1;
const int EJECT = 0;

int n, k;
vector<pint> time_set;
vector<pint> free_set;
vector<int> task;
vector<vector<int>> dp;

bool has_visit(int a, int b) {
	return a & b;
}

int find_ans(int visit, int time) {
	if (visit == (1 << k) - 1) {
		return ACCEPT;
	}
	else {
		for (pint& p : time_set) {
			if (p.first <= time && time < p.second) {
				time = p.second;
			}
			else if (time < p.first) {
				break;
			}
		}

		if (dp[visit][time] == NOT_VISIT) {
			int tmp_time;

			for (int i = 0; i < k; i++) {
				if (!has_visit(visit, 1 << i)) {
					tmp_time = time;

					for (int j = 0; j < (int)free_set.size(); j++) {
						pint cur_free = free_set[j];

						if (cur_free.first <= tmp_time && tmp_time + task[i] <= cur_free.second) {
							if (find_ans(visit | (1 << i), tmp_time + task[i]) == ACCEPT) {
								return dp[visit][time] = ACCEPT;
							}

						}
						else if (tmp_time <= cur_free.second) {
							if (j < (int)free_set.size() - 1) {
								tmp_time = free_set[j + 1].first;
							}
						}
					}
				}
			}

			dp[visit][time] = EJECT;
		}

		return dp[visit][time];
	}
}

void init_free_set() {
	if (time_set.front().first != 0) {
		free_set.push_back(make_pair(0, time_set.front().first));
	}
	for (int i = 0; i < (int)time_set.size() - 1; i++) {
		free_set.push_back(make_pair(time_set[i].second, time_set[i + 1].first));
	}
	if (time_set.back().second != MAX) {
		free_set.push_back(make_pair(time_set.back().second, MAX));
	}
}

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);

	cin >> n >> k;
	task = vector<int>(k);
	dp = vector<vector<int>>(1 << k, vector<int>(MAX + 1, NOT_VISIT));
	for (int i = 0; i < n; i++) {
		pint tmp;
		cin >> tmp.first >> tmp.second;

		if (!time_set.empty() && time_set.back().second == tmp.first) {
			time_set.back().second = tmp.second;
		}
		else {
			time_set.push_back(tmp);
		}
	}
	for (int& i : task) {
		cin >> i;
	}
	init_free_set();

	cout << (find_ans(0, 0) == ACCEPT ? "GOOD" : "BAD");

	return 0;
}