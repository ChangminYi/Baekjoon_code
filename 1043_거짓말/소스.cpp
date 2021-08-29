#include <iostream>
#include <vector>

using namespace std;
#define MAX 51

int parent[MAX]; 

int find(int i) {
	if (parent[i] == i) {
		return i;
	}
	else {
		return parent[i] = find(parent[i]);
	}
}

void Union(int i, int j) {
	i = find(i);
	j = find(j);
	parent[j] = i;
}

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);
	cout.tie(nullptr);
	cout.sync_with_stdio(false);

	int n = 0, m = 0;
	int t = 0, cnt = 0;
	int temp = 0, t_person = 0;

	cin >> n >> m;
	cin >> t;

	cnt = m;
	vector<vector<int>> party(m + 1);
	vector<int> truth(t);
	for (int &i: truth){
		cin >> i;
	}

	for (int i = 1; i <= m; i++) {
		cin >> t_person;
		party[i] = vector<int>(t_person);

		for (int& j : party[i]) {
			cin >> j;
		}
	}

	for (int i = 1; i <= n; i++) {
		parent[i] = i;
	}

	for (int i = 1; i <= m; i++) {
		int cur = party[i][0];

		for (int j = 1; j < party[i].size(); j++) {
			Union(cur, party[i][j]);
		}
	}

	for (int i = 1; i <= m; i++) {
		int cur = party[i][0];

		for (int& j : truth) {
			if (find(cur) == find(j)) {
				cnt--;
				break;
			}
		}
	}

	cout << cnt;

	return 0;
}