#include <iostream>
#include <unordered_set>
#include <string>

using namespace std;

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);

	int N = 0, M = 0;
	string temp;
	unordered_set<string> strset;

	cin >> N >> M;

	for (int i = 0; i < N; i++) {
		cin >> temp;
		strset.insert(temp);
	}

	int counter = 0;
	for (int i = 0; i < M; i++) {
		cin >> temp;
		if (strset.find(temp) != strset.end()) {
			counter++;
		}
	}

	cout << counter;

	return 0;
}