#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void print(int start, int last, vector<int> &argi) {
	static vector<bool> visit(argi.size(), false);
	static vector<int> arr(last);

	if (start == last) {
		for (int i = 0; i < last; i++) {
			cout << arr[i] << ' ';
		}
		cout << '\n';
		return;
	}
	else {
		for (uint32_t i = 0; i < argi.size(); i++) {
			if (!visit[i]) {
				visit[i] = true;
				arr[start] = argi[i];
				print(start + 1, last, argi);

				visit[i] = false;
			}
		}
	}
}

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);
	cout.tie(nullptr);
	cout.sync_with_stdio(false);

	int N = 0, M = 0;
	cin >> N >> M;

	vector<int> argi(N);
	for (int &i : argi) {
		cin >> i;
	}
	sort(argi.begin(), argi.end());

	print(0, M, argi);

	return 0;
}