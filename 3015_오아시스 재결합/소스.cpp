#include <iostream>
#include <stack>

using namespace std;

typedef long long lli;
typedef pair<int, int> pint;

int n;
lli res;
stack<pint> stk;

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);

	cin >> n;
	for (int i = 0, cur_h; i < n; i++) {
		cin >> cur_h;

		while (!stk.empty() && stk.top().first < cur_h) {
			res += stk.top().second;
			stk.pop();
		}

		if (stk.empty()) {
			stk.push(make_pair(cur_h, 1));
		}
		else {
			if (stk.top().first == cur_h) {
				pint cur = stk.top();
				stk.pop();

				res += cur.second;
				if(!stk.empty()){
					res++;
				}

				cur.second++;
				stk.push(cur);
			}
			else {
				stk.push(make_pair(cur_h, 1));
				res++;
			}
		}
	}

	cout << res;

	return 0;
}