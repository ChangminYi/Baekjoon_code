#include <iostream>
#include <vector>
#include <string>
using namespace std;

int getIndexOfCloth(pair<string, string> &newCloth, vector<vector<pair<string, string>>> &cloths) {
	for (int i = 0; i < cloths.size(); i++) {
		if (newCloth.second == cloths[i][0].second) {
			return i;
		}
	}
	return -1;
}

bool isNewClothType(pair<string, string> &newCloth, vector<vector<pair<string, string>>> &cloths) {
	for (int i = 0; i < cloths.size(); i++) {
		if (newCloth.second == cloths[i][0].second) {
			return false;
		}
	}
	return true;
}

int main() {
	int iter = 0;
	cin >> iter;
	for (; iter > 0; iter--) {
		vector<vector<pair<string, string>>> cloth;
		int num = 0;

		cin >> num;

		for (int i = 0; i < num; i++) {
			pair<string, string> temp;
			cin >> temp.first >> temp.second;

			if (isNewClothType(temp, cloth)) {
				cloth.push_back(vector<pair<string, string>>(1));
				cloth.back()[0] = temp;
			}
			else {
				cloth[getIndexOfCloth(temp, cloth)].push_back(temp);
			}
		}

		int output = 1;
		for (int i = 0; i < cloth.size(); i++) {
			output *= cloth[i].size() + 1;
		}
		output--;

		cout << output << endl;
	}
	return 0;
}