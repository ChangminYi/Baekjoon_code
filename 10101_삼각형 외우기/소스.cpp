#include <iostream>
using namespace std;
int main() {
	int a = 0, b = 0, c = 0;
	cin >> a >> b >> c;
	if (a + b + c == 180) {
		if (a == b && b == c && a == c) {
			cout << "Equilateral";
		}
		else if (a != b && b != c && a != c) {
			cout << "Scalene";
		}
		else {
			cout << "Isosceles";
		}
	}
	else {
		cout << "Error";
	}
	return 0;
}