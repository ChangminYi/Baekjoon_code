#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
	cin.tie(NULL);
	cin.sync_with_stdio(false);
	cout.tie(NULL);
	cout.sync_with_stdio(false);

	int t = 0;
	cin >> t;
	for (; t > 0; t--) {
		int n = 0;
		cin >> n;
		vector<int> shop = vector<int>(n);
		for (int &i : shop) {
			cin >> i;
		}
		sort(shop.begin(), shop.end());
		cout << (shop.back() - shop.front()) * 2 << '\n';
	}

	return 0;
}