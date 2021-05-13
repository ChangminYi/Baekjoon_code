//뭔가 틀렸다는데 모르겠음

#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
using namespace std;

int main() {
	cin.tie(NULL);
	cin.sync_with_stdio(false);

	int N = 0, K = 0;
	cin >> N >> K;

	vector<pair<int, int>> timetable = vector<pair<int, int>>(N);
	for (pair<int, int> &p : timetable) {
		cin >> p.first >> p.second;
	}
	sort(timetable.begin(), timetable.end());

	vector<int> toAdd = vector<int>(K);
	for (int &i : toAdd) {
		cin >> i;
		i--;
	}
	sort(toAdd.begin(), toAdd.end(), less<int>());



	return 0;
}