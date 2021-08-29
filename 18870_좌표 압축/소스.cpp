#include <iostream>
#include <deque>
#include <algorithm>

using namespace std;

typedef struct NODE {
	int value, inputOrder, valueOrder;
}node;

bool compByValue(node a, node b) {
	return a.value < b.value;
}

bool compByInput(node a, node b) {
	return a.inputOrder < b.inputOrder;
}

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);

	int N = 0;
	cin >> N;
	deque<node> argi(N);
	for (int i = 0; i < N; i++) {
		cin >> argi[i].value;
		argi[i].inputOrder = i;
	}

	sort(argi.begin(), argi.end(), compByValue);

	argi.front().valueOrder = 0;
	for (int i = 1; i < N; i++) {
		if (argi[i - 1].value == argi[i].value) {
			argi[i].valueOrder = argi[i - 1].valueOrder;
		}
		else {
			argi[i].valueOrder = argi[i - 1].valueOrder + 1;
		}
	}

	sort(argi.begin(), argi.end(), compByInput);

	cout << argi.front().valueOrder;
	for (int i = 1; i < N; i++) {
		cout << ' ' << argi[i].valueOrder;
	}

	return 0;
}