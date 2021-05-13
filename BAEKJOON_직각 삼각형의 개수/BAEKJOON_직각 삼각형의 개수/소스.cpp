//시간초과

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef pair<int, int> dir;

bool isPerpendi(vector<dir> argi) {
	dir vector[3] = {
		{argi[0].first - argi[1].first, argi[0].second - argi[1].second},
		{argi[1].first - argi[2].first, argi[1].second - argi[2].second},
		{argi[2].first - argi[0].first, argi[2].second - argi[0].second}
	};

	long long inner[3] = {
		vector[0].first*vector[1].first + vector[0].second*vector[1].second,
		vector[1].first*vector[2].first + vector[1].second*vector[2].second,
		vector[2].first*vector[0].first + vector[2].second*vector[0].second
	};

	for (uint32_t i = 0; i < 3; i++) {
		if (inner[i] == 0) { return true; }
	}
	return false;
}

vector<dir> getdir(vector<dir> argi, vector<bool> &argb) {
	vector<dir> coordinates;
	for (uint32_t i = 0; i < argi.size(); i++) {
		if (argb[i]) { coordinates.push_back(argi[i]); }
	}
	return coordinates;
}

int main() {
	cin.tie(NULL);
	cin.sync_with_stdio(false);

	uint32_t N = 0;
	cin >> N;
	vector<dir> dot = vector<dir>(N);
	for (uint32_t i = 0; i < N; i++) {
		cin >> dot[i].first >> dot[i].second;
	}

	vector<bool> table = vector<bool>(N, false);
	for (uint32_t i = 0; i < 3; i++) {
		table[i] = true;
	}

	int count = 0;
	do {
		if (isPerpendi(getdir(dot, table))) { count++; }
	} while (prev_permutation(table.begin(), table.end()));

	cout << count;

	return 0;
}