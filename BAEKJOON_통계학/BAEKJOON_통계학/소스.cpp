#include <iostream>
#include <algorithm>
#include <deque>
#include <cmath>

using namespace std;

int arr[8001] = { 0 }; 

int getMid(int size) {
	double sum = 0;
	for (int i = 0; i < 8001; i++) {
		sum += (i - 4000) * arr[i];
	}
	return (int)floor((sum / size) + 0.5);
}

int getMax() {
	deque<int> maxcandidate = {0};
	for (int i = 1; i < 8001; i++) {
		if (arr[i] > arr[maxcandidate.front()]) {
			maxcandidate = { i };
		}
		else if (arr[i] == arr[maxcandidate.front()]){
			maxcandidate.push_back(i);
		}
	}

	if (maxcandidate.size() == 1) {
		return maxcandidate.front() - 4000;
	}
	else {
		return maxcandidate[1] - 4000;
	}
}

int main() {
	cin.tie(nullptr); cin.sync_with_stdio(false);
	cout.tie(nullptr); cout.sync_with_stdio(false);

	int N = 0;
	cin >> N;

	deque<int> ary = deque<int>(N);
	for (int &i : ary) {
		cin >> i;
		arr[i + 4000]++;
	}

	sort(ary.begin(), ary.end());

	cout << getMid(N) << '\n';
	cout << ary[N / 2] << '\n';
	cout << getMax() << '\n';
	cout << ary.back() - ary.front();

	return 0;
}