#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);
	cout.tie(nullptr);
	cout.sync_with_stdio(false);

	int n;
	cin >> n;
	vector<int> argi(n);
	for (int& i : argi) {
		cin >> i;
	}
	sort(argi.begin(), argi.end());

	int min_sum = 0;
	for (int& i : argi) {
		if (min_sum + 2 <= i) {
			break;
		}
		else {
			min_sum += i;
		}
	}

	cout << min_sum + 1;

	return 0;
}