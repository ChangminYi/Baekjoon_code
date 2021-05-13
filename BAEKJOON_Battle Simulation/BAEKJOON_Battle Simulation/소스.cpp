//예제도 다 맞고 채점도 100%까지 진행하는데 틀림

#include <iostream>
#include <string>
using namespace std;

char getDefense(char c) {
	switch (c) {
	case 'R': return 'S';
	case 'B': return 'K';
	case 'L': return 'H';
	}
}

bool isCombo(string &s, int index) {
	if (s[index] != s[index + 1] && s[index + 1] != s[index + 2] && s[index + 2] != s[index]) {
		return true;
	}
	else {
		return false;
	}
}

int main() {
	string input, output;
	getline(cin, input);

	for (int i = 0; i < input.size(); ) {
		if (i < input.size() - 2) {
			if (isCombo(input, i)) {
				output += 'C';
				i += 3;
			}
			else {
				output += getDefense(input[i++]);
			}
		}
		else {
			output += getDefense(input[i++]);
		}
	}

	cout << output;

	return 0;
}