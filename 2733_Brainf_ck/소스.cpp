#include <iostream>
#include <string>
#include <vector>
#include <stack>

using namespace std;

const int NOT_JMP = -1;
const int ARR_SIZE = 32768;

int testcase;
string tmp;
vector<char> inst;
vector<unsigned char> byte_arr(ARR_SIZE);
vector<int> paren_ret;

char is_right_char(const char& c) {
	if (c == '<' || c == '>' || c == '+'
		|| c == '-' || c == '.' || c == '[' || c == ']') {
		return true;
	}
	return false;
}

void init_inst() {
	while (true) {
		getline(cin, tmp);

		if (tmp == "end") {
			break;
		}
		else {
			for (const char& c : tmp) {
				if (c == '%') {
					break;
				}
				else if (!is_right_char(c)) {
					continue;
				}
				else {
					inst.push_back(c);
				}
			}
		}
	}
}

bool check_paren() {
	stack<int> stk;
	paren_ret.resize(inst.size(), NOT_JMP);

	for (int i = 0; i < inst.size(); i++) {
		if (inst[i] == '[') {
			stk.push(i);
		}
		else if (inst[i] == ']') {
			if (stk.empty()) {
				return false;
			}
			else {
				paren_ret[i] = stk.top();
				paren_ret[stk.top()] = i;
				stk.pop();
			}
		}
	}

	return stk.empty();
}

void run_code() {
	fill(byte_arr.begin(), byte_arr.end(), 0);
	for (int i = 0, ptr = 0; i < inst.size(); ) {
		if (inst[i] == '>') {
			ptr = (ptr + 1) % ARR_SIZE;
		}
		else if (inst[i] == '<') {
			if (--ptr < 0) {
				ptr += ARR_SIZE;
			}
		}
		else if (inst[i] == '+') {
			byte_arr[ptr]++;
		}
		else if (inst[i] == '-') {
			byte_arr[ptr]--;
		}
		else if (inst[i] == '.') {
			cout << byte_arr[ptr];
		}
		else if (inst[i] == '[') {
			if (byte_arr[ptr] == 0) {
				i = paren_ret[i];
				continue;
			}
		}
		else if (inst[i] == ']') {
			if (byte_arr[ptr] != 0) {
				i = paren_ret[i];
				continue;
			}
		}

		i++;
	}
}

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);

	(cin >> testcase).ignore();
	for (int i = 1; i <= testcase; i++) {
		init_inst();

		cout << "PROGRAM #" << i << ":\n";
		if (check_paren()) {
			run_code();
			cout << '\n';
		}
		else {
			cout << "COMPILE ERROR\n";
		}

		inst.clear();
	}

	return 0;
}