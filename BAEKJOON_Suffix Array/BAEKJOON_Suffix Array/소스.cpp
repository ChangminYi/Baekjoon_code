//시간초과 (O(n^2logn)임)
//sa, lcp 알고리즘이 따로 있음 (O(nlogn^2))

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

string str;

bool compare(int &a, int &b) {
	return string(str.begin() + a, str.end()) < string(str.begin() + b, str.end());
}

int getPrefix(int a, int b) {
	int lng = 0;
	while (str[a + lng] == str[b + lng]) {
		lng++;
	}
	return lng;
}

int main() {
	cin >> str;
	
	vector<int> suffixArray = vector<int>(str.size());
	for (int i = 0; i < suffixArray.size(); i++) {
		suffixArray[i] = i;
	}
	sort(suffixArray.begin(), suffixArray.end(), compare);
	
	for (int i = 0; i < suffixArray.size() - 1; i++) {
		cout << suffixArray[i] + 1 << ' ';
	}
	cout << suffixArray[suffixArray.size() - 1] + 1 << endl << "x ";
	for (int i = 1; i < suffixArray.size() - 1; i++) {
		cout << getPrefix(suffixArray[i - 1], suffixArray[i]) << ' ';	
	}
	cout << getPrefix(suffixArray[suffixArray.size() - 2], suffixArray[suffixArray.size() - 1]);
	return 0;
}