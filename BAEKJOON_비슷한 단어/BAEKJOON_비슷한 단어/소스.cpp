#include <iostream>
#include <vector>
#include <string>

using namespace std;

typedef class DATA {
public:
	int zero = 0, one = 0, minus = 0;
}dat;

dat getData(vector<int> &argi) {
	dat temp;
	for (uint32_t i = 0; i < argi.size(); i++) {
		if (argi[i] == 0) {
			temp.zero++;
		}
		else if (argi[i] == 1) {
			temp.one++;
		}
		else if (argi[i] == -1) {
			temp.minus++;
		}
	}
	return temp;
}

int getSum(dat d) {
	return d.zero + d.one + d.minus;
}

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);

	int N = 0;
	cin >> N;
	vector<vector<int>> table = vector<vector<int>>(N, vector<int>(26, 0));
	for (int i = 0; i < N; i++) {
		string temp;
		cin >> temp;

		for (uint32_t j = 0; j < temp.size(); j++) {
			table[i][temp[j] - 'A']++;
		}
	}

	for (uint32_t i = 1; i < table.size(); i++) {
		for (uint32_t j = 0; j < table.front().size(); j++) {
			table[i][j] -= table.front()[j];
		}
	}

	int count = 0;
	for (uint32_t i = 1; i < table.size(); i++) {
		dat temp = getData(table[i]);

		if (temp.zero == 26) {
			count++;
		}
		else if (temp.minus == 1 && temp.one == 1 && getSum(temp) == 26) {
			count++;
		}
		else if (temp.minus == 0 && temp.one == 1 && getSum(temp) == 26) {
			count++;
		}
		else if (temp.minus == 1 && temp.one == 0 && getSum(temp) == 26) {
			count++;
		}
	}

	cout << count;

	return 0;
}