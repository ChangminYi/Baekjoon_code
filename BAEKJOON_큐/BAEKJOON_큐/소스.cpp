#include <iostream>
#include <string>
#include <queue>
using namespace std;

int main() {
	cin.tie(NULL);
	cin.sync_with_stdio(false);
	int N = 0;
	queue<int> q;
	cin >> N;
	for (; N > 0; N--) {
		string inst;
		cin >> inst;
		if (inst == "push") {
			int data = 0;
			cin >> data;
			q.push(data);
			continue;
		}
		else if (inst == "pop"){
			if (!q.empty()) {
				cout << q.front();
				q.pop();
			}
			else {
				cout << -1;
			}
			cout << '\n';
			continue;
		}
		else if (inst == "size") {
			cout << q.size() << '\n';
			continue;
		}
		else if (inst == "empty") {
			if (q.empty()) { cout << 1; }
			else { cout << 0; }
			cout << '\n';
			continue;
		}
		else if (inst == "front") {
			if (!q.empty()) { cout << q.front(); }
			else { cout << -1; }
			cout << '\n';
			continue;
		}
		else if (inst == "back") {
			if (!q.empty()) { cout << q.back(); }
			else { cout << -1; }
			cout << '\n';
			continue;
		}
	}
	return 0;
}
