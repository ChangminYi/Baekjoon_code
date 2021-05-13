#include <iostream>
#include <cmath>

using namespace std;

typedef struct DIRECTION {
public:
	DIRECTION() : upleft({ 0, 0 }), leng(0) {};
	DIRECTION(pair<int, int> _pair, int _leng) : upleft(_pair), leng(_leng) {};
	pair<int, int> upleft;
	int leng;
}dir;

int count = 0, r = 0, c = 0;

void getCount(dir current) {
	if (current.leng > 1) {
		getCount({ current.upleft, current.leng / 2 });
		getCount({ {current.upleft.first, current.upleft.second + current.leng / 2}, current.leng / 2 });
		getCount({ {current.upleft.first + current.leng / 2, current.upleft.second}, current.leng / 2 });
		getCount({ {current.upleft.first + current.leng / 2, current.upleft.second + current.leng / 2}, current.leng / 2 });
	}
	else {
		if (current.upleft.first == ::r && current.upleft.second == ::c) {
			cout << ::count;
		}
		::count++;
	}
}

int main() {
	int N = 0;
	cin >> N >> ::r >> ::c;

	getCount(dir({ 0, 0 }, pow(2, N)));

	return 0;
}