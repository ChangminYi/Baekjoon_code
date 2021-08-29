//틀린 게 안보이는데 틀림 -> 예외 생각해봐야 할듯

#include <iostream>
#include <algorithm>
//#include <queue>

using namespace std;
//typedef long long lint;
/*
int gcd(int a, int b) {
	if (b == 0) { return a; }
	else { return gcd(b, a % b); }
}

lint lcm(int a, int b) {
	int g = gcd(a, b);
	return g * (a / g) * (b / g);
}

int main() {
	int D = 0, P = 0, Q = 0;
	queue<lint> q;
	cin >> D >> P >> Q;

	lint l = lcm(P, Q);
	q.push((D / l) * l);

	int min = 0x7FFFFFFF;
	while (!q.empty()) {
		int temp = q.front();
		q.pop();

		if (temp + P < D) {
			q.push(temp + P);
		}
		else {
			min = (temp + P < min ? temp + P : min);
		}

		if (temp + Q < D) {
			q.push(temp + Q);
		}
		else {
			min = (temp + Q < min ? temp + Q : min);
		}
	}

	cout << min;

	return 0;
}
*/

int main() {
	int D = 0, P = 0, Q = 0;
	cin >> D >> P >> Q;
	int ans = 0;
	if (P < Q) { swap(P, Q); }

	if (D%P == 0 || D % Q == 0) {
		cout << D;
		return 0;
	}
	else {
		ans = (D / P)*P + P;
	}

	int t = ans;
	for (int i = 1; i <= t / P; i++) {
		int temp = t - P * i;
		if ((D - temp) % Q == 0) {
			cout << D;
			return 0;
		}
		else {
			temp += ((D - temp) / Q)*Q + Q;
		}
		if (ans == temp) { break; }
		ans = min(temp, ans);
	}
	cout << ans;
	return 0;
}