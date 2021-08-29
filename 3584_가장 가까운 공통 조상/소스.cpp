#include <iostream>
#include <deque>
#include <algorithm>

using namespace std;

deque<int> getRoute(deque<int> &tree, int start) {
	deque<int> route;
	int cur = start;
	while (cur != -1) {
		route.push_front(cur);
		cur = tree[cur];
	}
	return route;
}

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);
	
	int T = 0;
	cin >> T;
	for (; T > 0; T--) {
		int N = 0;
		cin >> N;
		deque<int> tree(N + 1, -1);
		for (int i = 0, par, chi; i < N - 1; i++) {
			cin >> par >> chi;
			tree[chi] = par;
		}

		int node1, node2;
		cin >> node1 >> node2;

		deque<int> route1 = getRoute(tree, node1), route2 = getRoute(tree, node2);

		uint32_t minLeng = min(route1.size(), route2.size());
		for (uint32_t i = 0; i < minLeng; i++) {
			if (route1[i] != route2[i]){
				cout << route1[i - 1] << '\n';
				break;
			}
			else if (i == minLeng - 1) {
				cout << route1[i] << '\n';
			}
		}
	}

	return 0;
}