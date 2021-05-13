//set 크기가 너무 커짐

#include <iostream>
#include <algorithm>
#include <string>
#include <set>
using namespace std;

int main() {
	set<string> map;
	string tofind, tosearch;
	int count = 0;

	cin >> tofind >> tosearch;
	for (int i = 0; i < tosearch.size() - tofind.size() + 1; i++) {
		map.insert(string(tosearch.begin() + i, tosearch.begin() + i + tofind.size()));
	}

	sort(tofind.begin(), tofind.end());
	do {
		if (map.find(tofind) != map.end()) {
			count++;
		}
	} while (next_permutation(tofind.begin(), tofind.end()));

	cout << count;

	return 0;
}