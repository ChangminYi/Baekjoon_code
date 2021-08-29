#include <iostream>
#include <array>
#include <string>

#define LEN 21

using namespace std;

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);
	cout.tie(nullptr);
	cout.sync_with_stdio(false);

	array<bool, LEN> argb;
	for (bool &b : argb) {
		b = false;
	}
	int inst_size = 0;
	cin >> inst_size;
	for (int i = 0; i < inst_size; i++) {
		string inst;
		int dat = 0;
		
		cin >> inst;
		if (inst == "all") {
			for (bool &b : argb) {
				b = true;
			}
		}
		else if (inst == "empty") {
			for (bool &b : argb) {
				b = false;
			}
		}
		else {
			cin >> dat;
			if (inst == "add") {
				argb[dat] = true;
			}
			else if (inst == "remove") {
				argb[dat] = false;
			}
			else if (inst == "check") {
				cout << (argb[dat] == true ? 1 : 0) << '\n';
			}
			else if (inst == "toggle") {
				argb[dat] = !argb[dat];
			}
		}
	}

	return 0;
}