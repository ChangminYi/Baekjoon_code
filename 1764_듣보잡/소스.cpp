#include <iostream>
#include <string>
#include <deque>
#include <map>
#include <algorithm>

using namespace std;

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);
	cout.tie(nullptr);
	cout.sync_with_stdio(false);

	map<string, int> args;
	int N = 0, M = 0;
	cin >> N >> M;

	for (int i = 0; i < N; i++) {
		string temp;
		cin >> temp;
		args.insert({ temp, 0 });
	}

	deque<string> ans;
	for (int i = 0; i < M; i++) {
		string temp;
		cin >> temp;

		if (args.find(temp) != args.end()) {
			ans.push_back(temp);
		}
	}

	sort(ans.begin(), ans.end());

	cout << ans.size() << '\n';
	for (string &s : ans) {
		cout << s << '\n';
	}

	return 0;
}