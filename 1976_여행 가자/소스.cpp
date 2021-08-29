#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>

using namespace std;

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);
	cout.tie(nullptr);
	cout.sync_with_stdio(false);

	int city = 0, togo = 0;
	cin >> city >> togo;

	vector<vector<int>> graph(city, vector<int>());
	vector<int> schedule(togo);
	for (int i = 0, temp = 0; i < city; i++) {
		for (int j = 0; j < city; j++) {
			cin >> temp;

			if (temp == 1) {
				graph[i].push_back(j);
			}
		}
	}
	for (int& i : schedule) {
		cin >> i;
		i--;
	}

	vector<unordered_set<int>> div_graph;
	vector<bool> visit(city, false);
	for (int i = 0; i < city; i++) {
		if (!visit[i]) {
			unordered_set<int> chunk;
			queue<int> nxt;

			nxt.push(i);
			visit[i] = true;
			while (!nxt.empty()) {
				int cur = nxt.front();
				chunk.insert(cur);
				nxt.pop();

				for (int& candidate : graph[cur]) {
					if (!visit[candidate]) {
						visit[candidate] = true;
						nxt.push(candidate);
					}
				}
			}

			div_graph.push_back(chunk);
		}
	}

	bool find = true;
	for (unordered_set<int>& st : div_graph) {
		find = true;
		for (int& i: schedule) {
			if (st.find(i) == st.end()) {
				find = false;
				break;
			}
		}

		if (find) {
			cout << "YES";
			break;
		}
	}

	if (!find) {
		cout << "NO";
	}

	return 0;
}