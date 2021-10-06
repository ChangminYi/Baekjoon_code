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

// �ڽŰ� �ֺ� �� ĭ ��� ���� �ٲٱ�
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
	// ������ ������ üũ
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
	* ù ��° ����� ������ ���� ����� ���� ���� ���� ���� ���� ����,
	* ������ �� ���� ��� ���� �����ٴ� ���� ����ȴ�.
	*/
	if (cur.first == 0) {
		// ù° ���̹Ƿ� �����ų� �Ȳ��� �� �� ����.
		simulate(pint(cur.first, cur.second + 1), cnt);

		change(cur);
		simulate(pint(cur.first, cur.second + 1), cnt + 1);
		change(cur);
	}
	else {
		// ���� ������ ���� �ٲ㺸��, �ƴϸ� �Ѿ
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
	* ù° ��, ù° ĭ���� ���� ���¸� �ٲ۴�.
	*/
	simulate(pint(0, 0), 0);

	cout << (res == INT32_MAX ? -1 : res);

	return 0;
}