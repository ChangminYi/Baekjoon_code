#include <iostream>
#include <string>
#include <deque>
using namespace std;

int main() {
	cin.tie(NULL);
	cin.sync_with_stdio(false);

	int N = 0;
	cin >> N;
	deque<int> d;
	for (; N > 0; N--) {
		string inst;
		cin >> inst;
		if (inst == "push_front") {
			int data = 0;
			cin >> data;
			d.push_front(data);
		}
		else if (inst == "push_back") {
			int data = 0;
			cin >> data;
			d.push_back(data);
		}
		else if (inst == "pop_front") {
			if (d.empty()) {
				cout << -1 << '\n';
			}
			else {
				cout << d.front() << '\n';
				d.pop_front();
			}
		}
		else if (inst == "pop_back") {
			if (d.empty()) {
				cout << -1 << '\n';
			}
			else {
				cout << d.back() << '\n';
				d.pop_back();
			}
		}
		else if (inst == "size") {
			cout << d.size() << '\n';
		}
		else if (inst == "empty") {
			if (d.empty()) {
				cout << 1 << '\n';
			}
			else {
				cout << 0 << '\n';
			}
		}
		else if (inst == "front") {
			if (d.empty()) {
				cout << -1 << '\n';
			}
			else {
				cout << d.front() << '\n';
			}
		}
		else if (inst == "back") {
			if (d.empty()) {
				cout << -1 << '\n';
			}
			else {
				cout << d.back() << '\n';
			}
		}
	}

	return 0;
}