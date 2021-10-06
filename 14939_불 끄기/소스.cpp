#include <iostream>
#include <vector>
#include <string>
#include <limits>

using namespace std;

typedef pair<int, int> pint;
const vector<pint> poss_dir = {
	pint(0, 1), pint(0, -1),
	pint(1, 0), pint(-1, 0)
};

bool board[10][10];
int res = INT32_MAX;

pint operator+(const pint& lhs, const pint& rhs) {
	return pint(lhs.first + rhs.first, lhs.second + rhs.second);
}

bool in_range(const pint& p) {
	return (0 <= p.first && p.first < 10) && (0 <= p.second && p.second < 10);
}

// 자신과 주변 네 칸 모두 상태 바꾸기
void change(pint cur) {
	board[cur.first][cur.second] = !board[cur.first][cur.second];

	for (const pint& dir : poss_dir) {
		pint nxt = cur + dir;

		if (in_range(nxt)) {
			board[nxt.first][nxt.second] = !board[nxt.first][nxt.second];
		}
	}
}

void simulate(pint cur, int cnt) {
	// 마지막 줄인지 체크
	if (cur.second == 10) {
		if (cur.first == 9) {
			for (int i = 0; i < 10; i++) {
				if (board[9][i]) {
					return;
				}
			}

			res = min(res, cnt);
			return;
		}

		else {
			cur = pint(cur.first + 1, 0);
		}
	}

	/*
	* 첫 번째 행부터 마지막 직전 행까지 현재 행의 위를 보고 불을 끄면,
	* 마지막 줄 빼고 모든 줄이 꺼진다는 것이 보장된다.
	*/
	if (cur.first == 0) {
		// 첫째 줄이므로 꺼보거나 안끄기 두 개 가능.
		simulate(pint(cur.first, cur.second + 1), cnt);

		change(cur);
		simulate(pint(cur.first, cur.second + 1), cnt + 1);
		change(cur);
	}
	else {
		// 켜져 있으면 상태 바꿔보고, 아니면 넘어감
		if (!board[cur.first - 1][cur.second]) {
			simulate(pint(cur.first, cur.second + 1), cnt);
		}
		else  {
			change(cur);
			simulate(pint(cur.first, cur.second + 1), cnt + 1);
			change(cur);
		}
	}
}


int main() {
	cin.tie(nullptr)->sync_with_stdio(false);

	for (int i = 0; i < 10; i++) {
		string input;
		cin >> input;

		for (int j = 0; j < 10; j++) {
			board[i][j] = (input[j] == 'O');
		}
	}

	/*
	* 첫째 줄, 첫째 칸부터 불의 상태를 바꾼다.
	*/
	simulate(pint(0, 0), 0);

	cout << (res == INT32_MAX ? -1 : res);

	return 0;
}