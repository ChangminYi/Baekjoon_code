#include <iostream>
#include <string>
#include <stack>
#include <cctype>

using namespace std;

string arg;
int paren_pair[50];
stack<int> stk;

int get_len(const int lo, const int hi) {
    int ret = 0, i = lo;
    while(i <= hi) {
        if(arg[i] == '(') {
            ret += (arg[i - 1] - '0') * get_len(i + 1, paren_pair[i]) - 1;
            i = paren_pair[i] + 1;
        }
        else {
            if(isdigit(arg[i])) ret++;
            i++;
        }
    }

    return ret;
}

int main() {
    /**
     * 스택을 사용하여 미리 괄호의 짝의 인덱스를 찾는다.
     * 문자열을 읽으면서, 숫자를 만나면 길이를 1 늘린다.
     * 괄호를 만났다면, 그 안의 길이를 재귀적으로 구하고 괄호의 짝 다음으로 이동한다.
     * 이를 문자열의 끝까지 반복하면 압축이 풀린 문자열의 길이가 나온다.
     */

    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);
    
    cin >> arg;
    for(int i = 0; i < arg.length(); i++) {
        if(arg[i] == '(')
            stk.push(i);
        else if(arg[i] == ')') {
            paren_pair[stk.top()] = i;
            stk.pop();
        }
        else continue;
    }

    cout << get_len(0, arg.length() - 1);

    return 0;
}