//예제도 다 맞고 채점도 100%까지 진행하는데 틀림

#include <iostream>
#include <string>
#include <deque>

using namespace std;

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);

	deque<char> str;
	string temp;
	cin >> temp;
	for (char& c : temp) {
		str.push_back(c);
	}

	while (str.size() >= 3) {
		if (str[0] != str[1] && str[1] != str[2] && str[0] != str[2]) {
			cout << 'C';
			str.pop_front(); str.pop_front(); str.pop_front();
		}
		else {
			switch (str[0]) {
			case 'R':
				cout << 'S';
				break;
			case 'B':
				cout << 'K';
				break;
			case 'L':
				cout << 'H';
				break;
			}
			str.pop_front();
		}
	}

	while (!str.empty()) {
		switch (str[0]) {
		case 'R':
			cout << 'S';
			break;
		case 'B':
			cout << 'K';
			break;
		case 'L':
			cout << 'H';
			break;
		}
		str.pop_front();
	}

	return 0;
}