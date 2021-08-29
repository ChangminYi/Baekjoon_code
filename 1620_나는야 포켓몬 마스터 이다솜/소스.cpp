#include <iostream>
#include <map>
#include <deque>
#include <string>

using namespace std;

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);
	cout.tie(nullptr);
	cout.sync_with_stdio(false);

	int N = 0, M = 0;
	cin >> N >> M;
	deque<string> args(N + 1);
	map<string, int> argi;

	for (int i = 1; i <= N; i++) {
		cin >> args[i];
		argi.insert({ args[i], i });
	}

	for (int i = 0; i < M; i++) {
		string temp;
		cin >> temp;

		if (isalpha(temp.front())) {
			cout << argi[temp] << '\n';
		}
		else {
			cout << args[stoi(temp)] << '\n';
		}
	}

	return 0;
}