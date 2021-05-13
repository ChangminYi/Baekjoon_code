#include <iostream>

using namespace std;

int main() {
	int A, B, C;
	cin >> A >> B >> C;

	cout << ((C % 2 == 1 )? A ^ B : A);

	return 0;
}