#include <iostream>
#include <vector>

using namespace std;

vector<int> to_go;
vector<vector<vector<int>>> dp;

/*
* 출발, 도착이 같으면 1의 힘을 사용,
* 0에서 가는 모든 도착은 2의 힘을 사용,
* 도착이 출발의 반대편이면 4의 힘을 사용,
* 나머지는 3의 힘을 사용
*/
int get_move(int from, int dest) {
	if (from == dest) {
		return 1;
	}
	else {
		switch (from) {
		case 0: return 2;
		case 1: return (dest == 3 ? 4 : 3);
		case 2: return (dest == 4 ? 4 : 3);
		case 3: return (dest == 1 ? 4 : 3);
		case 4: return (dest == 2 ? 4 : 3);
		}
	}
}

/*
* 왼발을 움직였을 때와 오른발을 움직였을 때를 모두 계산
* 그 중에서 더 작은 값을 현재 값으로 설정
*/
int get_min_val(int left, int right, int idx) {
	if (idx == to_go.size()) {
		return 0;
	}
	else {
		if (dp[left][right][idx] == 0) {
			int cand_left = get_move(left, to_go[idx]) + get_min_val(to_go[idx], right, idx + 1);
			int cand_right = get_move(right, to_go[idx]) + get_min_val(left, to_go[idx], idx + 1);
			dp[left][right][idx] = min(cand_left, cand_right);
		}

		return dp[left][right][idx];
	}
}

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);

	for (int tmp;;) {
		cin >> tmp;
		if (tmp == 0) {
			break;
		}
		else {
			to_go.push_back(tmp);
		}
	}

	dp.resize(5, vector<vector<int>>(5, vector<int>(to_go.size(), 0)));
	cout << get_min_val(0, 0, 0);

	return 0;
}