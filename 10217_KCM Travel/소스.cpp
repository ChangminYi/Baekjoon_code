#include <iostream>
#include <vector>
#include <queue>
#include <functional>

using namespace std;

class edge {
public:
	int next = 0;
	int cost = 0;
	int time = 0;
	edge() {}
	edge(int _next, int _cost, int _time) :next(_next), cost(_cost), time(_time) {}
};

class pq_node {
public:
	int node = 0;
	int cost = 0;
	int time = 0;
	pq_node() {}
	pq_node(int _node, int _cost, int _time) :node(_node), cost(_cost), time(_time) {}
};

bool operator> (const pq_node& a, const pq_node& b){
	return a.time > b.time;
}

const int INF = 1000000000;
const int MAX = 101;
const int START = 1;

int testcase;
int n, m, k;
vector<vector<edge>> graph;
vector<vector<int>> time_spend;
priority_queue<pq_node, vector<pq_node>, greater<pq_node>> pq;

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);

	cin >> testcase;
	do {
		cin >> n >> m >> k;
		graph = vector<vector<edge>>(n + 1);
		time_spend = vector<vector<int>>(MAX, vector<int>(m + 1, INF));

		for (int i = 0, arg1, arg2, arg3, arg4; i < k; i++) {
			cin >> arg1 >> arg2 >> arg3 >> arg4;
			graph[arg1].push_back(edge(arg2, arg3, arg4));
		}

		time_spend[START][0] = 0;
		pq.push(pq_node(START, 0, time_spend[START][0]));
		while (!pq.empty()) {
			pq_node cur = pq.top();
			pq.pop();

			if (cur.time <= time_spend[cur.node][cur.cost]) {
				for (edge &e : graph[cur.node]) {
					int nxt_node = e.next;
					int nxt_cost = cur.cost + e.cost;
					int nxt_time = time_spend[cur.node][cur.cost] + e.time;

					if (nxt_cost <= m && nxt_time < time_spend[nxt_node][nxt_cost]) {
						time_spend[nxt_node][nxt_cost] = nxt_time;
						pq.push(pq_node(nxt_node, nxt_cost, nxt_time));
					}
				}
			}
		}

		int min_time = INF;
		for (int& i : time_spend[n]) {
			min_time = min(min_time, i);
		}

		min_time == INF ? cout << "Poor KCM" : cout << min_time;
		cout << '\n';

	} while (--testcase > 0);

	return 0;
}