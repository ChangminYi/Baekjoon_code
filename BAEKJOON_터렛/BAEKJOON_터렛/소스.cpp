#include <iostream>
#include <vector>
using namespace std;

long long int getDistance(pair<long long int, long long int> &a, pair<long long int, long long int> &b) {
	long long int x_coor = b.first - a.first;
	long long int y_coor = b.second - a.second;

	return ((x_coor * x_coor) + (y_coor * y_coor));
}

int main() {
	vector<int> aftermath;
	int iter = 0;
	
	cin >> iter;
	for (; iter > 0; iter--) {
		pair<long long int, long long int> jo, baek;
		long long int r1 = 0, r2 = 0;

		cin >> jo.first >> baek.first >> r1 >> jo.second >> baek.second >> r2;

		long long int circleDist = getDistance(jo, baek);
		long long int subDist = (r2 - r1)*(r2 - r1);
		long long int addDist = (r2 + r1)*(r2 + r1);

		if (subDist < circleDist && circleDist < addDist) { aftermath.push_back(2); }
		else if (circleDist == addDist) { aftermath.push_back(1); }
		else if (circleDist == subDist && circleDist != 0) { aftermath.push_back(1); }
		else if (circleDist<subDist || circleDist>addDist) { aftermath.push_back(0); }
		else if (circleDist == 0) {
			if (r1 == r2) { aftermath.push_back(-1); }
			else (aftermath.push_back(0));
		}		
	}

	for (int i = 0; i < aftermath.size(); i++) {
		cout << aftermath[i] << endl;
	}

	return 0;
}