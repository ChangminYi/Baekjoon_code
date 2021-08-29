/*
#include <iostream>
#include <deque>
#include <string>

using namespace std;

void printarray(const deque<int> &argi, const bool reverse) {
	if (argi.empty()) {
		cout << "[]" << '\n';
	}
	else {
		if (!reverse) {
			cout << '[' << argi.front();
			for (uint32_t i = 1; i < argi.size(); i++) {
				cout << ',' << argi[i];
			}
			cout << "]\n";
		}
		else {
			cout << '[' << argi.back();
			for (uint32_t i = 1; i < argi.size(); i++) {
				cout << ',' << argi[argi.size() - 1 - i];
			}
			cout << "]\n";
		}
	}
	return;
}

deque<int> getDeque(const string &s) {
	deque<int> d;

	if (s != "[]") {
		int start = 1, last = 1;
		while (true) {
			while (!(s[last] == ',' || s[last] == ']')) {
				last++;
			}
			d.push_back(stoi(s.substr(start, last)));

			if (s[last] == ']') {
				break;
			}
			else {
				start = last + 1;
				last = start;
			}
		}
	}
	return d;
}

int main() {
	cin.tie(nullptr); cin.sync_with_stdio(false);
	cout.tie(nullptr); cout.sync_with_stdio(false);

	int N = 0;
	cin >> N;

	for (int i = 0; i < N; i++) {
		bool isReverse = false, contFlag = false;
		deque<int> deq;
		string inst, arr;
		int num = 0;
		cin >> inst >> num >> arr;
		deq = getDeque(arr);

		for (uint32_t j = 0; j < inst.size(); j++) {
			if (inst[j] == 'R') {
				isReverse = !isReverse;
			}
			else {
				if (deq.empty()) {
					cout << "error\n";
					contFlag = true;
					break;
				}
				else {
					if (isReverse) {
						deq.pop_back();
					}
					else {
						deq.pop_front();
					}
				}
			}
		}

		if (contFlag) { continue; }
		else { printarray(deq, isReverse); }
	}


	return 0;
}
*/

#include <iostream>
#include <string>
#include <deque>
#include <algorithm>

using namespace std;

int main(void) {
	cin.sync_with_stdio(false);
	cin.tie(nullptr);
	int test_case = 0;
	cin >> test_case;

	for (int t = 0; t < test_case; t++) {
		string func;
		cin >> func;

		int N = 0;
		cin >> N;

		string arr;
		cin >> arr; //배열 입력

		deque<int> dq; //덱
		string temp; //두 자릿수 이상 숫자를 위하여
		for (uint32_t i = 0; i < arr.length(); i++)
			if (arr[i] == '[') {
				continue;
			}
			else if ('0' <= arr[i] && arr[i] <= '9') {
				temp += arr[i];
			}
			else if (arr[i] == ',' || arr[i] == ']') {
				if (!temp.empty()) {
					dq.push_back(stoi(temp));
					temp.clear();
				}
			}

		bool print = true; //error가 아닐 경우 true
		bool left = true; //뒤집어져있지 않으면 true
		for (uint32_t i = 0; i < func.length(); i++) {
			if (func[i] == 'R') {
				left = !left;
			}
			else {
				if (dq.empty()) {
					print = false;
					cout << "error\n";
					break;
				}
				else {
					if (left) {
						dq.pop_front();
					}
					else {
						dq.pop_back();
					}
				}
			}
		}

		if (print) {
			if (left) {
				cout << "[";
				while (!dq.empty()) {
					cout << dq.front();
					dq.pop_front();
					if (!dq.empty()) {
						cout << ",";
					}
				}

				cout << "]\n";
			}
			else {
				cout << "[";
				while (!dq.empty()) {
					cout << dq.back();
					dq.pop_back();
					if (!dq.empty()) {
						cout << ",";
					}
				}
				cout << "]\n";
			}
		}
	}

	return 0;
}