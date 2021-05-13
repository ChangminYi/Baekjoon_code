//예제는 다 맞았는데 틀렸음


#include <iostream>
#include <vector>
#include <deque>
using namespace std;

typedef struct {
	int row;
	int col;
}dir;


void turnRight(int &index) {
	index = (index + 1) % 4;
}

void turnLeft(int &index) {
	index = (index + 3) % 4;
}

bool hasTouchedBody(pair<int, int> &head, deque<pair<int, int>> &snake) {
	for (int i = 1; i < snake.size(); i++) {
		if (head.first == snake[i].first && head.second == snake[i].second) {
			return true;
		}
	}
	return false;
}

bool isInBoard(pair<int, int> &head, int boardSize) {
	if (head.first < 0 || head.second < 0 || head.first >= boardSize || head.second >= boardSize) {
		return false;
	}
	return true;
}

int main() {
	dir move[4] = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} };
	int boardSize = 0, appleNum = 0, behaveNum = 0, count = 0;
	deque<pair<int, int>> snake = { {0, 0} }; //front: head
	int moveIndex = 0;

	cin >> boardSize;
	vector<vector<bool>> board = vector<vector<bool>>(boardSize);
	for (int i = 0; i < boardSize; i++) {
		board[i] = vector<bool>(boardSize, false);
	}

	cin >> appleNum;
	for (int i = 0, temp[2]; i < appleNum; i++) {
		cin >> temp[0] >> temp[1];
		board[temp[0] - 1][temp[1] - 1] = true;
	}

	cin >> behaveNum;
	deque<pair<int, char>> behave = deque<pair<int, char>>(behaveNum);
	for (int i = 0; i < behaveNum; i++) {
		cin >> behave[i].first >> behave[i].second;
	}

	while (true) {
		count++;
		pair<int, int> nowHead = { snake.front().first + move[moveIndex].row, snake.front().second + move[moveIndex].col };

		if (hasTouchedBody(nowHead, snake) || !isInBoard(nowHead, boardSize)) {
			cout << count;
			break;
		}
		else {
			snake.push_front(nowHead);
			if (board[nowHead.first][nowHead.second] == false) {
				snake.pop_back();
			}
			else {
				board[nowHead.first][nowHead.second] == false;
			}

			if (behave.size() != 0 && behave.front().first == count) {
				if (behave.front().second == 'L') {
					turnLeft(moveIndex);
				}
				else if(behave.front().second == 'D'){
					turnRight(moveIndex);
				}

				behave.pop_front();
			}
		}
	}


	return 0;
}