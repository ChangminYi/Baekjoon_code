#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

void BFS(vector<vector<unsigned int>> &graph, unsigned int start, vector<unsigned int> &route) {
	vector<bool> checked = vector<bool>(graph.size(), false);
	queue<unsigned int> togo;
	togo.push(start);

	while (!togo.empty()) {
		unsigned int current = togo.front();
		togo.pop();
		if (checked[current]) {
			continue;
		}
		else {
			checked[current] = true;
			route.push_back(current);
			for (int i = 0; i < graph[current].size(); i++) {
				togo.push(graph[current][i]);
			}
		}
	}
}

void DFS(vector<vector<unsigned int>> &graph, unsigned int start, vector<unsigned int> &route) {
	static vector<bool> checked = vector<bool>(graph.size(), false);

	if (checked[start]) {
		return;
	}
	else {
		checked[start] = true;
		route.push_back(start);
		for (int i = 0; i < graph[start].size(); i++) {
			DFS(graph, graph[start][i], route);
		}
	}
}

int main() {
	cin.tie(NULL);
	cin.sync_with_stdio(false);
	cout.tie(NULL);
	cout.sync_with_stdio(false);

	unsigned int VertexNum = 0, edgeNum = 0, startIndex = 0;
	cin >> VertexNum >> edgeNum >> startIndex;
	startIndex--;
	vector<vector<unsigned int>> graph = vector<vector<unsigned int>>(VertexNum);
	for (int i = 0; i < edgeNum; i++) {
		int temp[2];
		cin >> temp[0] >> temp[1];
		temp[0]--; temp[1]--;
		graph[temp[0]].push_back(temp[1]);
		graph[temp[1]].push_back(temp[0]);
	}

	for (int i = 0; i < graph.size(); i++) {
		sort(graph[i].begin(), graph[i].end());
	}

	vector<unsigned int> route_dfs, route_bfs;
	DFS(graph, startIndex, route_dfs);
	BFS(graph, startIndex, route_bfs);

	for (int i = 0; i < route_dfs.size(); i++) {
		cout << route_dfs[i] + 1;
		if (i == route_dfs.size() - 1) {
			cout << '\n';
		}
		else {
			cout << ' ';
		}
	}

	for (int i = 0; i < route_bfs.size(); i++) {
		cout << route_bfs[i] + 1;
		if (i != route_bfs.size() - 1) {
			cout << ' ';
		}
	}


	return 0;
}