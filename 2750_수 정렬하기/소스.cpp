#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
	int num = 0;
	cin >> num;
	vector<int> argi = vector<int>(num);
	for (int i = 0; i < num; i++) {
		cin >> argi[i];
	}
	sort(argi.begin(), argi.end());
	for (int i : argi) {
		cout << i << endl;
	}
	return 0;
}