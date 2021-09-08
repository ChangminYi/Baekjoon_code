#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <limits>

using namespace std;

const int MAX = 50000000;

int testcase, mem_size, code_size, input_size;
string code, input;
vector<int> loop_idx;
vector<unsigned char> arr;

void init_loop_state() {
	stack<int> stk;

	for (int i = 0; i < code_size; i++) {
		if (code[i] == '[') {
			stk.push(i);
		}
		if (code[i] == ']') {
			loop_idx[i] = stk.top();
			loop_idx[stk.top()] = i;
			stk.pop();
		}
	}
}

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);

	cin >> testcase;
	do {
		cin >> mem_size >> code_size >> input_size;
		cin >> code >> input;

		loop_idx = vector<int>(code_size, 0);
		arr = vector<unsigned char>(mem_size, 0);
		init_loop_state();

		int mem_idx = 0, input_idx = 0;
		int inst_cnt = 0, inf_start = INT32_MAX;
		bool inf_loop = false;
		for (int i = 0; i < code_size; i++) {
			if (code[i] == '-') {
				arr[mem_idx] = (arr[mem_idx] + 255) % 256;
			}
			else if (code[i] == '+') {
				arr[mem_idx] = (arr[mem_idx] + 1) % 256;
			}
			else if (code[i] == '<') {
				mem_idx = (mem_idx - 1 + mem_size) % mem_size;
			}
			else if (code[i] == '>') {
				mem_idx = (mem_idx + 1) % mem_size;
			}
			else if (code[i] == '[' && arr[mem_idx] == 0) {
				i = loop_idx[i];
			}
			else if (code[i] == ']' && arr[mem_idx] != 0) {
				i = loop_idx[i];
			}
			else if (code[i] == ',') {
				arr[mem_idx] = (input_idx == input_size ? 255 : input[input_idx++]);
			}

			if (inst_cnt > MAX) {
				inf_start = min(inf_start, i);
			}
			if (inst_cnt > 2 * MAX) {
				inf_loop = true;
			}

			inst_cnt++;
			if (inf_loop) {
				cout << "Loops " << inf_start << ' ' << loop_idx[inf_start] << '\n';
				break;
			}
		}

		if (!inf_loop) {
			cout << "Terminates\n";
		}
	} while (--testcase > 0);

	return 0;
}