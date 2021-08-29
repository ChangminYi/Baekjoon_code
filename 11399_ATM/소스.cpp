#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);

	int n = 0;
	cin >> n;
	vector<int> time(n);
	for (int &i : time) {
		cin >> i;
	}
	sort(time.begin(), time.end());

	long long sum = 0;
	for (int i = 0; i < n; i++) {
		sum += (n - i) * time[i];
	}

	cout << sum;

	return 0;
}