#include <iostream>
using namespace std;

int main() {
	int nums[5] = { 0, 0, 0, 0, 0 };
	int size = 0;
	pair<int, int> temp;
	cin >> size;
	for (int i = 0; i < size; i++) {
		cin >> temp.first >> temp.second;
		if (temp.first == 0 || temp.second == 0) {
			nums[4]++;
		}
		else if (temp.first > 0 && temp.second > 0) {
			nums[0]++;
		}
		else if (temp.first < 0 && temp.second>0) {
			nums[1]++;
		}
		else if (temp.first < 0 && temp.second < 0) {
			nums[2]++;
		}
		else {
			nums[3]++;
		}
	}

	cout << "Q1: " << nums[0] << endl << "Q2: " << nums[1] << endl << "Q3: " << nums[2] << endl << "Q4: " << nums[3] << endl << "AXIS: " << nums[4];


	return 0;
}