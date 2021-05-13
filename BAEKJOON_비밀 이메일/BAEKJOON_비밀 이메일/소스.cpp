//대체 이 코드는 뭐가 틀린 건지 모르겠음
/*#include <iostream>
#include <string>
using namespace std;

int main() {
	int row = 0, col = 0;;
	string str, newstr;

	cin >> str;

	for (int i = 1; i <= str.size(); i++) {
		for (int j = 1; j <= str.size(); j++) {
			if (i*j == str.size()) {
				if (i <= j) {
					row = i; col = j;
				}
			}
		}
	}

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			newstr.push_back(str[i + j*col]);
		}
	}

	cout << newstr;

	return 0;
}*/

#include <iostream>
using namespace std;

int main() {
	char str[101];
	char newstr[101][101];
	int row = 0, col = 0, length = 0;


	cin.getline(str, 101);
	while (str[length] != 0) {
		length++;
	}

	for (int i = 0; i <= length; i++) {
		for (int j = 1; j <= length; j++) {
			if (i*j == length) {
				if (i <= j) {
					row = i;
					col = j;
				}
			}
		}
	}

	for (int i = 0, temp = 0; i < col; i++) {
		for (int j = 0; j < row; j++) {
			newstr[j][i] = str[temp++];
		}
	}

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			cout << newstr[i][j];
		}
	}

	return 0;
}