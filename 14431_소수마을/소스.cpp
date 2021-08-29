#include <iostream>
#include <vector>
#include <limits>
#include <queue>
#include <cmath>
#include <functional>

using namespace std;

typedef pair<int, int> pint;

const int INF = INT32_MAX / 2;

vector<int> prime = { 2 };
vector<pint> coor;
vector<vector<pint>> graph;

void init_prime() {
	for (int i = 3; i <= 10000; i+=2) {
		bool yes = true;
		for (int j = 0; prime[j] * prime[j] <= i; j++) {
			if (i % prime[j] == 0) {
				yes = false;
			}
		}
		if (yes) {
			prime.push_back(i);
		}
	}
}

bool is_prime(const int n) {
	if (n <= 1) {
		return false;
	}
	else if (n == 2) {
		return true;
	}
	else {
		for (int& p : prime) {
			if (p * p > n) {
				break;
			}
			else if (n % p == 0) {
				return false;
			}
		}
		return true;
	}
}

int get_dist(const pint &a, const pint &b) {
	int x_dist = a.first - b.first;
	int y_dist = a.second - b.second;
	return (int)sqrt(x_dist * x_dist + y_dist * y_dist);
}

void init_graph() {
	for (size_t i = 0; i < coor.size(); i++) {
		for (size_t j = i + 1; j < coor.size(); j++) {
			int tmp_dist = get_dist(coor[i], coor[j]);

			if (is_prime(tmp_dist)) {
				graph[i].push_back(make_pair(j, tmp_dist));
				graph[j].push_back(make_pair(i, tmp_dist));
			}
		}
	}
}

int dijkstra(int depart, int desti) {
	vector<int> dist = vector<int>(graph.size(), INF);
	priority_queue<pint, vector<pint>, greater<pint>> pq;

	dist[depart] = 0;
	pq.push(make_pair(dist[depart], depart));
	while (!pq.empty()) {
		int cur = pq.top().second;
		int cur_dist = pq.top().first;
		pq.pop();

		if (cur_dist <= dist[cur]) {
			for (pint& edge : graph[cur]) {
				int new_val = cur_dist + edge.second;
				int old_val = dist[edge.first];

				if (new_val < old_val) {
					dist[edge.first] = new_val;
					pq.push(make_pair(new_val, edge.first));
				}
			}
		}
	}

	return (dist[desti] == INF ? -1 : dist[desti]);
}

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);

	init_prime();
	int n;
	pint start, end;
	cin >> start.first >> start.second >> end.first >> end.second;
	
	cin >> n;
	n += 2;
	coor = vector<pint>(n);
	graph = vector<vector<pint>>(n);
	coor[0] = start;
	for (int i = 1; i < n - 1; i++) {
		cin >> coor[i].first >> coor[i].second;
	}
	coor[n - 1] = end;
	init_graph();

	cout << dijkstra(0, n - 1);

	return 0;
}