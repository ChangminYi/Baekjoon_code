#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

bool cmp(string &a, string &b) {
	if (a.size() == b.size()) { return a < b; }
	else { return a.size() < b.size(); }
}

int main() {
	cin.tie(NULL);
	cin.sync_with_stdio(false);
	cout.tie(NULL);
	cout.sync_with_stdio(false);

	int size = 0;
	cin >> size;
	vector<string> args;
	for (int i = 0; i < size; i++) {
		string temp;
		cin >> temp;
		args.push_back(temp);
	}
	sort(args.begin(), args.end(), cmp);
	cout << args.front();
	for (int i = 1, last = 0; i < size; i++) {
		if (args[last] != args[i]) {
			last = i;
			cout << '\n' << args[i];
		}
	}


	return 0;
}