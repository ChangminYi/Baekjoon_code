#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
	cin.tie(NULL);
	cin.sync_with_stdio(false);
	cout.tie(NULL);
	cout.sync_with_stdio(false);

	int size = 0;
	cin >> size;
	vector<int> argi = vector<int>(size);
	for (int &i : argi) {
		cin >> i;
	}
	sort(argi.begin(), argi.end());

	int iter = 0;
	cin >> iter;
	for (int i = 0; i < iter; i++) {
		int toFind = 0;
		cin >> toFind;
		if (binary_search(argi.begin(), argi.end(), toFind)) {
			cout << 1 << '\n';
		}
		else {
			cout << 0 << '\n';
		}
	}

	return 0;
}