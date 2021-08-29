#include <iostream>
using namespace std;

int ovenNum = 0, doughNum = 0, result = 0;
int oven[300000] = { 0 };
int dough[300000] = { 0 };
int visited[300000] = { 0 };

int main() {
	cin >> ovenNum >> doughNum;
	for (int i = 0; i < ovenNum; i++) {
		cin >> oven[i];
		if (i > 0 && oven[i - 1] < oven[i]) {
			oven[i] = oven[i - 1];
		}
	}
	for (int i = 0; i < doughNum; i++) {
		cin >> dough[i];
	}

	int count = 0;
	for (int i = ovenNum - 1; i >= 0; i--) {
		if (dough[count] <= oven[i]) {
			visited[count] = i + 1;
			count++;
		}
		if (count == doughNum) {
			break;
		}
	}

	if (count == doughNum) {
		cout << visited[count - 1] << endl;
	}
	else {
		cout << 0 << endl;
	}

	return 0;
}
