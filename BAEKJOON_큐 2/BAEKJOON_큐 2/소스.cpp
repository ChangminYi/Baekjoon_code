#include <queue>
#include <iostream>
#include <string>
using namespace std;

int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	cin.sync_with_stdio(false);
	cout.sync_with_stdio(false);

	int num = 0;
	queue<int> q;

	cin >> num;
	for (int i = 0; i < num; i++) {
		string inst;
		cin >> inst;
		if (inst == "push") {
			int data = 0;
			cin >> data;
			q.push(data);
		}
		else if (inst == "pop") {
			if (q.empty()) {
				cout << -1;
			}
			else {
				cout << q.front();
				q.pop();
			}
			cout << '\n';
		}
		else if (inst == "size") {
			cout << q.size() << '\n';
		}
		else if (inst == "empty") {
			if (q.empty()) {
				cout << 1;
			}
			else {
				cout << 0;
			}
			cout << '\n';
		}
		else if (inst == "front") {
			if (q.empty()) {
				cout << -1;
			}
			else {
				cout << q.front();
			}
			cout << '\n';
		}
		else if (inst == "back") {
			if (q.empty()) {
				cout << -1;
			}
			else {
				cout << q.back();
			}
			cout << '\n';
		}
	}


	return 0;
}