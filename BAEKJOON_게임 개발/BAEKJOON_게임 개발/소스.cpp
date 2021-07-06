#include <iostream>
#include <vector>

using namespace std;

const int NOT_VISIT = -1;

vector<int> spend;
vector<vector<int>> graph;
vector<bool> ancestor;
vector<int> total_spend;

int get_time(int idx) {
	if (total_spend[idx] == NOT_VISIT) {
		int max_val = 0;
		for (int& to_go : graph[idx]) {
			max_val = max(max_val, get_time(to_go));
		}

		return total_spend[idx] = max_val + spend[idx];
	}
	else {
		return total_spend[idx];
	}
}

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);
	cout.tie(nullptr);
	cout.sync_with_stdio(false);

	int n;
	cin >> n;
	spend = vector<int>(n + 1);
	ancestor = vector<bool>(n + 1, false);
	total_spend = vector<int>(n + 1, NOT_VISIT);
	graph = vector<vector<int>>(n + 1);
	for (int i = 1; i <= n; i++) {
		cin >> spend[i];

		while(true){
			int tmp;
			cin >> tmp;

			if (tmp == -1) {
				break;
			}
			else {
				graph[i].push_back(tmp);
				ancestor[tmp] = true;;
			}
		}
	}

	for (int i = 1; i <= n; i++) {
		if (!ancestor[i]) {
			get_time(i);
		}
	}

	for (int i = 1; i <= n; i++) {
		cout << total_spend[i] << '\n';
	}

	return 0;
}