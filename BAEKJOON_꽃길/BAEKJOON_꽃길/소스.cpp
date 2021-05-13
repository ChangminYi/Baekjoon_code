#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool isNotDead(pair<int, int> &seed1, pair<int, int> &seed2) {
	vector<pair<int, int>> flower1 = { {seed1.first, seed1.second}, {seed1.first - 1, seed1.second}, {seed1.first, seed1.second + 1}, {seed1.first + 1, seed1.second}, {seed1.first, seed1.second - 1} };
	vector<pair<int, int>> flower2 = { {seed2.first, seed2.second}, {seed2.first - 1, seed2.second}, {seed2.first, seed2.second + 1}, {seed2.first + 1, seed2.second}, {seed2.first, seed2.second - 1} };
	for (int i = 0; i < flower2.size(); i++) {
		for (int j = 0; j < flower1.size(); j++) {
			if (flower2[i].first == flower1[j].first && flower2[i].second == flower1[j].second) {
				return false;
			}
		}
	}
	return true;
}

void swap(int &a, int &b) { 
	int temp = a;
	a = b;
	b = temp;
}

int getCost(vector<vector<int>> &board, pair<int, int> &seed) {
	return board[seed.first][seed.second] + board[seed.first - 1][seed.second] + board[seed.first][seed.second + 1] + board[seed.first + 1][seed.second] + board[seed.first][seed.second - 1];
}

int main() {
	pair<int, int> seed[3];
	int boardSize = 0;
	cin >> boardSize;

	vector<vector<int>> board = vector<vector<int>>(boardSize);
	vector<int> boardIndex = vector<int>(boardSize * boardSize);
	for (int i = 0; i < boardSize; i++) {
		board[i] = vector<int>(boardSize);
		for (int j = 0; j < boardSize; j++) {
			cin >> board[i][j];
			boardIndex[boardSize*i + j] = boardSize * i + j;
		}
	}

	vector<pair<int, int>> possibleSeed;
	for (int i = 1; i < boardSize - 1; i++) {
		for (int j = 1; j < boardSize - 1; j++) {
			possibleSeed.push_back(make_pair(i, j));
		}
	}

	int mininum = 2147483647;
	for (int i = 0; i < possibleSeed.size(); i++) {				//seed 1
		for (int j = i + 1; j < possibleSeed.size(); j++) {			//seed 2
			for (int k = j + 1; k < possibleSeed.size(); k++) {		//seed 3
				if (isNotDead(possibleSeed[i], possibleSeed[j]) && isNotDead(possibleSeed[j], possibleSeed[k]) && isNotDead(possibleSeed[i], possibleSeed[k])) {
					if (getCost(board, possibleSeed[i]) + getCost(board, possibleSeed[j]) + getCost(board, possibleSeed[k]) < mininum) {
						mininum = getCost(board, possibleSeed[i]) + getCost(board, possibleSeed[j]) + getCost(board, possibleSeed[k]);
					}
				}
			}
		}
	}

	cout << mininum;
	
	return 0;
}