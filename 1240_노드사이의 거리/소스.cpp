#include <iostream>
#include <vector>
#include <queue>
#include <functional>

#define INF 0x7FFFffff

using namespace std;

typedef pair<int, int> pint;
typedef class NODE {
public:
	int destination, cost;
	NODE() {};
	NODE(int _d, int _c):destination(_d), cost(_c) {};
} node;

int getCost(vector<vector<node>> &tree, int depart, int arrive) {
	priority_queue<pint, vector<pint>, less<pint>> pq;
	vector<int> costTable(tree.size(), INF);

	costTable[depart] = 0;
	pq.push({ 0, depart });
	while (!pq.empty()) {
		int current = pq.top().second;
		pq.pop();

		for (uint32_t i = 0; i < tree[current].size(); i++) {
			int newCost = costTable[current] + tree[current][i].cost;
			int oldCost = costTable[tree[current][i].destination];

			if (newCost < oldCost) {
				costTable[tree[current][i].destination] = newCost;
				pq.push({ newCost, tree[current][i].destination });
			}
		}
	}

	return costTable[arrive];
}

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);

	int N = 0, M = 0;
	cin >> N >> M;
	vector<vector<node>> tree(N);
	for (int i = 0, temp[3]; i < N - 1; i++) {
		cin >> temp[0] >> temp[1] >> temp[2];
		temp[0]--, temp[1]--;

		tree[temp[0]].push_back(node(temp[1], temp[2]));
		tree[temp[1]].push_back(node(temp[0], temp[2]));
	}

	for (int i = 0, temp[2]; i < M; i++) {
		cin >> temp[0] >> temp[1];
		temp[0]--, temp[1]--;
		cout << getCost(tree, temp[0], temp[1]) << '\n';
	}

	return 0;
}