//시간초과

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

bool isAdjacent(vector<int> &argi) {
	for (int i = 0; i < argi.size() - 1; i++) {
		if (argi[i] == 1 && argi[i + 1] == 1) {
			return true;
		}
	}
	return false;
}

//nCr
vector<vector<int>> combination(int n, int r) {
	vector<int> toprint = vector<int>(n, 1);
	vector<vector<int>> comb;
	for (int i = 0; i < r; i++) {
		toprint[i] = 0;
	}

	do {
		if (isAdjacent(toprint)) {
			continue;
		}
		else {
			vector<int> temp;
			for (int i = 0; i < toprint.size(); i++) {
				if (toprint[i] == 1) {
					temp.push_back(i);
				}
			}
			comb.push_back(temp);
		}
	} while (next_permutation(toprint.begin(), toprint.end()));

	return comb;
}

int main() {
	cin.tie(NULL);
	cin.sync_with_stdio(false);

	int num = 0, cableNum = 0;
	cin >> num >> cableNum;
	
	//건물과 나 사이의 절대거리
	vector<int> absDist;
	for (int i = 0, temp = 0; i < num; i++) {
		cin >> temp;
		absDist.push_back(temp);
	}

	vector<vector<int>> poss = combination(num - 1, cableNum);
	int min = 0x7fffffff;
	for (int i = 0, sum = 0; i < poss.size(); i++) {
		for (int j = 0; j < poss[i].size(); j++) {
			sum += absDist[poss[i][j] + 1] - absDist[poss[i][j]];
		}
		if (sum < min) {
			min = sum;
		}
		sum = 0;
	}

	cout << min;
	return 0;
}