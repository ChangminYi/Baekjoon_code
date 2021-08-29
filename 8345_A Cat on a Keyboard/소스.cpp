#include <iostream>
#include <string>
using namespace std;

int change(char c) {
	switch (c) {
	case '`':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	case '0':
	case '-':
	case '=': return 1;
	case 'Q':
	case 'w':
	case 'E':
	case 'R':
	case 'T':
	case 'Y':
	case 'U':
	case 'I':
	case 'O':
	case 'P':
	case '[':
	case ']':
	case '\\': return 2;
	case 'A':
	case 'S':
	case 'D':
	case 'F':
	case 'G':
	case 'H':
	case 'J':
	case 'K':
	case 'L':
	case ';':
	case '\'':return 3;
	case 'Z':
	case 'X':
	case 'C':
	case 'V':
	case 'B':
	case 'N':
	case 'M':
	case ',':
	case '.':
	case '/': return 4;
	case ' ': return 5;
	}
}


int main() {
	cin.tie(NULL);
	cin.sync_with_stdio(false);

	string str;
	getline(cin, str);

	for (char c : str) {
		cout << change(c);
	}
	return 0;
}