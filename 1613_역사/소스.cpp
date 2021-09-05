#include <iostream>
#include <vector>

using namespace std;

int n, k, s;
vector<vector<int>> board;

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);

	cin >> n >> k;
	board.resize(n + 1, vector<int>(n + 1, 0));
	for (int i = 0, older, newer; i < k; i++) {
		cin >> older >> newer;

		board[older][newer] = -1;
		board[newer][older] = 1;
	}

	/*
	* 미리 받은 정보들로 나머지 빈칸 유추
	* i-j간 정보가 없지만 i-k-j간 정보가 있다면
	* i-j도 유추 가능
	* for문을 돌려서 가능한 모든 쌍 연결
	*/
	for (int k = 1; k <= n; k++) {
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				if (board[i][j] == 0) {
					/*
					* 가운데 구간이 같은 순서로 이어져야 정보 유추 가능
					* 세 구간 다 정보가 없는 경우는 제외 
					*/
					if (board[i][k] == board[k][j] && board[i][k] != 0) {
						board[i][j] = board[i][k];
					}
				}
			}
		}
	}

	cin >> s;
	do {
		int n1, n2;
		cin >> n1 >> n2;

		cout << board[n1][n2] << '\n';
	} while (--s > 0);

	return 0;
}