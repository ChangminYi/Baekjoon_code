#include <iostream>
#include <vector>
#include <queue>

using namespace std;

typedef pair<int, int> pos;
typedef struct NODE {
	NODE() :dir({ 0, 0 }), jumpCount(0), moveCount(0) {};
	NODE(pos _dir, int _jump, int _move) : dir(_dir), jumpCount(_jump), moveCount(_move) {};
	pos dir;
	int jumpCount = 0;
	int moveCount = 0;
}node;

vector<pos> knight = { {-1, -2}, {-2, -1}, {+2, -1}, {+1, -2}, {+1, +2}, {+2, +1}, {-2, +1}, {-1, +2} };
vector<pos> common = { {0, +1}, {0, -1}, {-1, 0}, {+1, 0} };

bool isInRange(int row, int col, int jumpCount, vector<vector<bool>> &table, int maxJump) {
	if (0 <= row && row < table.size() && 0 <= col && col < table.front().size() && jumpCount < maxJump) {
		return true;
	}
	return false;
}

int getNum(vector<vector<bool>> &table, int maxJump) {
	vector<vector<vector<bool>>> check(maxJump + 1, vector<vector<bool>>(table.size(), vector<bool>(table.front().size(), false)));
	queue<node> togo;

	togo.push(node({0, 0}, 0, 0));
	while (!togo.empty()) {
		pos curDir = togo.front().dir;
		int curJumpCount = togo.front().jumpCount;
		int curMoveCount = togo.front().moveCount;
		togo.pop();

		if (curDir.first == table.size() - 1 && curDir.second == table.front().size() - 1) {
			return curMoveCount;
		}
		else {
			if (!check[curJumpCount][curDir.first][curDir.second]) {
				check[curJumpCount][curDir.first][curDir.second] = true;

				if (curJumpCount < maxJump) {
					for (uint32_t i = 0; i < knight.size(); i++) {
						pos temp = { curDir.first + knight[i].first, curDir.second + knight[i].second };
						if (isInRange(temp.first, temp.second, curJumpCount + 1, table, maxJump + 1) && table[temp.first][temp.second] && !check[curJumpCount + 1][temp.first][temp.second]) {
							togo.push(node(temp, curJumpCount + 1, curMoveCount + 1));
						}
					}
				}
				for (uint32_t i = 0; i < common.size(); i++) {
					pos temp = { curDir.first + common[i].first, curDir.second + common[i].second };
					if (isInRange(temp.first, temp.second, curJumpCount, table, maxJump + 1) && table[temp.first][temp.second] && !check[curJumpCount][temp.first][temp.second]) {
						togo.push(node(temp, curJumpCount, curMoveCount + 1));
					}
				}
			}
		}
	}

	return -1;
}

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);

	int K = 0, W = 0, H = 0;
	cin >> K >> W >> H;

	vector<vector<bool>> table(H, vector<bool>(W, true));
	for (int i = 0, temp = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			cin >> temp;
			if (temp == 1) {
				table[i][j] = false;
			}
		}
	}

	cout << getNum(table, K);

	return 0;
}