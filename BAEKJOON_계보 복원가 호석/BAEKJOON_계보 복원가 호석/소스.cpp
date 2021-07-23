#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <set>
#include <algorithm>
#include <queue>

using namespace std;

int n, m;
vector<string> args;
unordered_map<string, vector<string>> graph;
unordered_map<string, set<string>> child;
unordered_map<string, int> degree;
unordered_map<string, bool> is_first;

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);
	cout.tie(nullptr);
	cout.sync_with_stdio(false);

	cin >> n;
	args = vector<string>(n);
	for (string& s : args) {
		cin >> s;
		child.insert(make_pair(s, set<string>()));
		degree.insert(make_pair(s, 0));
		is_first.insert(make_pair(s, true));
	}
	sort(args.begin(), args.end());

	cin >> m;
	for (int i = 0; i < m; i++) {
		string des, ans;
		cin >> des >> ans;
		is_first[des] = false;
		degree[des]++;
		graph[ans].push_back(des);
	}

	queue<string> que;
	vector<string> family;
	for (string& s : args) {
		if (is_first[s]) {
			family.push_back(s);
			que.push(s);
		}
	}
	while (!que.empty()) {
		string cur = que.front();
		que.pop();

		for (string& nxt : graph[cur]) {
			if (--degree[nxt] == 0) {
				child[cur].insert(nxt);
				que.push(nxt);
			}
		}
	}

	cout << family.size() << '\n';
	for (string& s : family) {
		cout << s << ' ';
	}
	cout << '\n';
	for (string& s : args) {
		cout << s << ' ' << child[s].size() << ' ';
		for (set<string>::iterator i = child[s].begin(); i != child[s].end(); i++) {
			cout << *i << ' ';
		}
		cout << '\n';
	}

	return 0;
}