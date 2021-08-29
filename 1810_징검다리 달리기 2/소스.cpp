#include <iostream>
#include <queue>
#include <functional>
#include <map>
#include <set>
#include <cmath>

using namespace std;
typedef class direction {
public:
	int x, y;
	direction() : x(0), y(0) {}
	direction(const int _x, const int _y) : x(_x), y(_y) {}
	direction(const pair<int, int> dir) : x(dir.first), y(dir.second) {}
	bool operator< (const direction& to_comp) const {
		if (this->x == to_comp.x) {
			return this->y < to_comp.y;
		}
		else {
			return this->x < to_comp.x;
		}
	}
}dir;

double get_dist(const dir& a, const dir& b) {
	return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

bool in_range(const dir& to_search, const map<dir, double>& graph) {
	return graph.find(to_search) != graph.end();
}

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);
	cout.tie(nullptr);
	cout.sync_with_stdio(false);

	map<dir, double> graph;
	set<dir> final_line;
	int n, F;
	cin >> n >> F;
	for (int i = 0; i < n; i++) {
		dir tmp;
		cin >> tmp.x >> tmp.y;
		graph.insert(make_pair(dir(tmp), INT32_MAX));
		if (tmp.y == F) {
			final_line.insert(tmp);
		}
	}

	priority_queue<pair<double, dir>, vector<pair<double, dir>>, greater<pair<double, dir>>> que;
	que.push(make_pair(0, dir()));
	while (!que.empty()) {
		dir cur = que.top().second;
		que.pop();

		for (int i = 2; i >= -2; i--) {
			for (int j = 2; j >= -2; j--) {
				dir nxt = dir(cur.x + i, cur.y + j);
				double nxt_dist = get_dist(cur, nxt);

				if (in_range(nxt, graph) && graph[cur] + nxt_dist < graph[nxt]) {
					graph[nxt] = graph[cur] + nxt_dist;
					que.push(make_pair(graph[nxt], nxt));
				}
			}
		}
	}

	double ans = INT32_MAX;
	for (set<dir>::iterator i = final_line.begin(); i != final_line.end(); i++) {
		ans = min(ans, graph[*i]);
	}

	if (ans == INT32_MAX) {
		cout << -1;
	}
	else {
		cout << floor(ans + 0.5);
	}

	return 0;
}