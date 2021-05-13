/*트리의 지름 구하기
	1. 임의의 노드에서 가장 먼 노드 x
	2. x에서 가장 먼 노드 y
	3. 트리의 지름은 dist(x, y)
*/
#include <iostream>
#include <vector>
#include <queue>
#include <functional>

#define INT_MAX 0x7fffFFFF

using namespace std;

typedef pair<int, int> pint;
typedef struct NODE {
public:
	int destination = 0, value = 0;
	NODE() {};
	NODE(int _destin, int _val) :destination(_destin), value(_val) {};
} node;

pint getLength(vector<vector<node>> &tree, int start) {
	int longestIndex = 0;
	vector<int> cost(tree.size(), INT_MAX);
	priority_queue<pint> pq;

	cost[start] = 0;
	pq.push({ 0, start });

	while (!pq.empty()) {
		int cur = pq.top().second;
		pq.pop();

		for (uint32_t i = 0; i < tree[cur].size(); i++) {
			int newCost = cost[cur] + tree[cur][i].value;
			int oldCost = cost[tree[cur][i].destination];

			if (newCost < oldCost) {
				cost[tree[cur][i].destination] = newCost;
				pq.push({newCost, tree[cur][i].destination});
			}
		}
	}

	for (uint32_t i = 0; i < cost.size(); i++) {
		if (cost[i] > cost[longestIndex]) {
			longestIndex = i;
		}
	}

	return { cost[longestIndex], longestIndex };
}

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);

	int n = 0;
	cin >> n;
	vector<vector<node>> tree(n);
	for (int i = 0, temp[3]; i < n - 1; i++) {
		cin >> temp[0] >> temp[1] >> temp[2];
		temp[0]--, temp[1]--;
		tree[temp[0]].push_back(node(temp[1], temp[2]));
		tree[temp[1]].push_back(node(temp[0], temp[2]));
	}

	cout << getLength(tree, getLength(tree, 0).second).first;

	return 0;
}