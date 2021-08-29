#include <iostream>
#include <vector>
#include <queue>
#include <functional>

using namespace std;

#define INF 0x7fffFFFF

typedef pair<int, int> p_int;
typedef class NODE {
public:
	int desti = 0, val = 0;
	NODE() {};
	NODE(int _destination, int _value) : desti(_destination), val(_value) {};
}node;

p_int longestPath(vector<vector<node>> &tree, int start) {
	priority_queue<p_int, vector<p_int>, less<p_int>> pq;
	vector<int> cost(tree.size(), INF);

	cost[start] = 0;
	pq.push({ 0, start });
	while (!pq.empty()) {
		int current = pq.top().second;
		pq.pop();

		for (uint32_t i = 0; i < tree[current].size(); i++) {
			int newCost = cost[current] + tree[current][i].val;
			int oldCost = cost[tree[current][i].desti];

			if (newCost < oldCost) {
				cost[tree[current][i].desti] = newCost;
				pq.push({ newCost, tree[current][i].desti });
			}
		}
	}

	int maxIndex = 0;
	for (uint32_t i = 0; i < cost.size(); i++) {
		if (cost[i] != INF && cost[maxIndex] < cost[i]) {
			maxIndex = i;
		}
	}

	return { cost[maxIndex], maxIndex };
}

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);

	int n = 0;
	cin >> n;
	vector<vector<node>> tree(n);
	for (int i = 0, nodeNum, destNum, cost; i < n; i++) {
		cin >> nodeNum;
		nodeNum--;
		while (true) {
			cin >> destNum;
			if (destNum == -1) {
				break;
			}
			else {
				destNum--;
				cin >> cost;

				tree[nodeNum].push_back(node(destNum, cost));
			}
		}
	}

	cout << longestPath(tree, longestPath(tree, 0).second).first;

	return 0;
}