#include <iostream>
#include <string>
using namespace std;

typedef class TIME{
public:
	TIME():sec(0), min(0), hour(0) {}
	TIME(int h, int m, int s) :hour(h), min(m), sec(s) {}
	TIME(string &s) {
		this->hour = stoi(string(s.begin(), s.begin() + 2));
		this->min = stoi(string(s.begin() + 3, s.begin() + 5));
		this->sec = stoi(string(s.begin() + 6, s.end()));
	}
	TIME operator+(TIME &T){
		int tempHour = this->hour + T.hour;
		int tempMin = this->min + T.min;
		int tempSec = this->sec + T.sec;
		if (tempSec > 60) {
			tempMin++;
			tempSec %= 60;
		}
		if (tempMin > 60) {
			tempHour++;
			tempMin %= 60;
		}
		if (tempHour > 24) {
			tempHour %= 24;
		}

		return TIME(tempHour, tempMin, tempSec);
	}
	TIME operator-(TIME &T) {
		int tempHour = this->hour - T.hour;
		int tempMin = this->min - T.min;
		int tempSec = this->sec - T.sec;
		if (tempSec < 0) {
			tempSec += 60;
			tempMin--;
		}
		if (tempMin < 0) {
			tempMin += 60;
			tempHour--;
		}
		if (tempHour < 0) {
			tempHour += 24;
		}

		return TIME(tempHour, tempMin, tempSec);
	}
	TIME operator=(TIME &T) {
		return TIME(T.hour, T.min, T.sec);
	}
	void printTime() {
		if (this->hour < 10) {
			cout << '0' << this->hour;
		}
		else {
			cout << this->hour;
		} cout << ':';
		if (this->min < 10) {
			cout << '0' << this->min;
		}
		else {
			cout << this->min;
		} cout << ':';
		if (this->sec < 10) {
			cout << '0' << this->sec;
		}
		else {
			cout << this->sec;
		}
	}
private:
	int sec, min, hour;
} time;


int main() {
	cin.tie(NULL);
	cin.sync_with_stdio(false);

	string st[2];
	cin >> st[0] >> st[1];

	TIME start = TIME(st[0]);
	TIME end = TIME(st[1]);

	TIME dist = end - start;

	dist.printTime();

	return 0;
}