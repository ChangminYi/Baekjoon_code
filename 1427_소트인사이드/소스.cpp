#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

bool comp(char a, char b) {
	return a > b;
}

int main() {
	string s;
	cin >> s;
	
	sort(s.begin(), s.end(), comp);

	cout << s;

	return 0;
}