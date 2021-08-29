#include <iostream>

using namespace std;

typedef pair<int, int> pint;

pint p1, p2, p3;

int ccw() {
	int tmp = p1.first * p2.second + p2.first * p3.second + p3.first * p1.second;
	tmp -= p1.second * p2.first + p2.second * p3.first + p3.second * p1.first;

	if (tmp > 0) {
		return 1;
	}
	else if (tmp < 0) {
		return -1;
	}
	else {
		return 0;
	}
}

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);

	cin >> p1.first >> p1.second >> p2.first >> p2.second >> p3.first >> p3.second;

	cout << ccw();

	return 0;
}