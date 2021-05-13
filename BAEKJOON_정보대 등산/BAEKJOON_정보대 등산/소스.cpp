#include <iostream>
#include <vector>
using namespace std;

int main() {
	cin.sync_with_stdio(0);
	cin.tie(0);

	int num = 0;
	cin >> num;

	vector<long long> leftsum, rightsum, cross = vector<long long>(num);
	for (int i = 0; i < num; i++) {
		cin >> cross[i];
	}
	int tmp = 0;
	leftsum.push_back(0), rightsum.push_back(0);
	for (int i = 1; i < num; i++) {
		cin >> tmp;
		leftsum.push_back(leftsum.back() + tmp);
	}
	for (int i = 1; i < num; i++) {
		cin >> tmp;
		rightsum.push_back(rightsum.back() + tmp);
	}

	long long ans = 0x7FFFFFFFFFFFFFFF;
	int pos = 0;
	for (int i = 0; i < num; ++i) {
		long long ret = cross[i] + leftsum[i] + rightsum.back() - rightsum[i];
		if (ret < ans) {
			ans = ret;
			pos = i;
		}
	}
	cout << pos + 1 << ' ' << ans;
	return 0;
}