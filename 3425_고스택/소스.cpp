#include <iostream>
#include <string>
#include <stack>
#include <cmath>

using namespace std;

typedef long long lli;

const lli MAX_ABS = 1000000000;
const string ERR = "ERROR\n";

int N, inst_cnt, num_arg_cnt;
string inst[100000];
lli num_arg[100000];

string interpret(const int init_val) {
    stack<lli> stk;
    stk.push(init_val);

    for (int i = 0, num_idx = 0; i < inst_cnt; i++) {
        if (inst[i] == "NUM") {
            stk.push(num_arg[num_idx++]);
        }
        else if (inst[i] == "POP") {
            if (stk.empty()) { return ERR; }
            else { stk.pop(); }
        }
        else if (inst[i] == "INV") {
            if (stk.empty()) { return ERR; }
            else {
                lli tmp = stk.top();
                stk.pop();
                stk.push(-tmp);
            }
        }
        else if (inst[i] == "DUP") {
            if (stk.empty()) { return ERR; }
            else { stk.push(stk.top()); }
        }
        else if (inst[i] == "SWP") {
            if (stk.size() < 2) { return ERR; }
            else {
                lli fst = stk.top(); stk.pop();
                lli snd = stk.top(); stk.pop();
                stk.push(fst), stk.push(snd);
            }
        }
        else if (inst[i] == "ADD") {
            if (stk.size() < 2) { return ERR; }
            else {
                lli right = stk.top(); stk.pop();
                lli left = stk.top(); stk.pop();
                if (abs(left + right) > MAX_ABS) { return ERR; }
                else { stk.push(left + right); }
            }
        }
        else if (inst[i] == "SUB") {
            if (stk.size() < 2) { return ERR; }
            else {
                lli right = stk.top(); stk.pop();
                lli left = stk.top(); stk.pop();
                if (abs(left - right) > MAX_ABS) { return ERR; }
                else { stk.push(left - right); }
            }
        }
        else if (inst[i] == "MUL") {
            if (stk.size() < 2) { return ERR; }
            else {
                lli right = stk.top(); stk.pop();
                lli left = stk.top(); stk.pop();
                if (abs(left * right) > MAX_ABS) { return ERR; }
                else { stk.push(left * right); }
            }
        }
        else if (inst[i] == "DIV") {
            if (stk.size() < 2 || stk.top() == 0) { return ERR; }
            else {
                lli right = stk.top(); stk.pop();
                lli left = stk.top(); stk.pop();
                if (abs(left / right) > MAX_ABS) { return ERR; }
                else { stk.push(left / right); }
            }
        }
        else if (inst[i] == "MOD") {
            if (stk.size() < 2 || stk.top() == 0) { return ERR; }
            else {
                lli right = stk.top(); stk.pop();
                lli left = stk.top(); stk.pop();
                if (abs(left % right) > MAX_ABS) { return ERR; }
                else { stk.push(left % right); }
            }
        }
        else { break; }
    }
    
    if (stk.size() == 1) { return to_string(stk.top()) + '\n'; }
    else { return ERR; }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);
    
    /*
    * 요구사항을 그대로 구현하면 된다. 다만, 스택의 동작 과정에서
    * 오류를 내는 경우나 연산에서 오류가 나는 경우를 예외처리해줘야 한다.
    * 연산의 오버플로우/언더플로우도 신경써야 한다.
    */
    while (true) {
        inst_cnt = 1, num_arg_cnt = 0;
        cin >> inst[0];
        if (inst[0] == "QUIT") {
            break;
        }
        else {
            if (inst[0] == "NUM") {
                cin >> num_arg[num_arg_cnt++];
            }

            if (inst[0] != "END") {
                do {
                    cin >> inst[inst_cnt++];
                    if (inst[inst_cnt - 1] == "NUM") {
                        cin >> num_arg[num_arg_cnt++];
                    }
                } while (inst[inst_cnt - 1] != "END");
            }
            cin >> N;
            for (int i = 0, val; i < N; i++) {
                cin >> val;
                cout << interpret(val);
            }
            cout << '\n';
        }
    }

    return 0;
}