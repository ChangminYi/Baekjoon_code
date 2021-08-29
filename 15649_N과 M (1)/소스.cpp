#include <iostream>
#define MAX 9
using namespace std;

int arr[MAX] = { 0 };
bool visited[MAX] = { 0 };

void dfs(int cnt, int n, int m) {
	if (cnt == m) {
		for (int i = 0; i < m; i++) {
			cout << arr[i] << ' ';
		}
		cout << '\n';
		return;
	}

	for (int i = 1; i <= n; i++) {
		if (!visited[i]) {
			visited[i] = true;
			arr[cnt] = i;
			dfs(cnt + 1, n, m);
			visited[i] = false;
		}
	}
}

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);
	cout.tie(nullptr);
	cout.sync_with_stdio(false);

	int n = 0, m = 0;
	cin >> n >> m;
	
	dfs(0, n, m);

	return 0;
}