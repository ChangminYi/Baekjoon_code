#include <iostream>
#include <vector>
#include <string>

using namespace std;

int is_element(int front, int back);
int is_set(int front, int back);

const int NOT_SEEN = -1;
const int ERROR = 0;
const int ACCEPT = 1;

string to_parse;
vector<vector<int>> dp;

int is_element(int front, int back) {
	if (dp[front][back] == NOT_SEEN) {
		if (front > back) {
			dp[front][back] = ERROR;
		}
		else if (front == back || is_set(front, back) == ACCEPT) {
			dp[front][back] = ACCEPT;
		}
		else {
			for (int i = front; i <= back; i++) {
				if (to_parse[i] == ',') {
					if (is_element(front, i - 1) == ACCEPT && is_element(i + 1, back) == ACCEPT) {
						return dp[front][back] = ACCEPT;
					}
				}
			}
			dp[front][back] = ERROR;
		}
	}
	return dp[front][back];
}

int is_set(int front, int back) {
	if (dp[front][back] == NOT_SEEN) {
		if (to_parse[front] == '{' && to_parse[back] == '}') {
			if (front + 1 == back || front + 2 == back) {
				dp[front][back] = ACCEPT;
			}
			else if (is_set(front + 1, back - 1) == ACCEPT) {
				dp[front][back] = ACCEPT;
			}
			else {
				for (int i = front + 1; i <= back - 1; i++) {
					if (to_parse[i] == ',') {
						if (is_element(front + 1, i - 1) == ACCEPT && is_element(i + 1, back - 1) == ACCEPT) {
							return dp[front][back] = ACCEPT;
						}
					}
				}
				dp[front][back] = ERROR;
			}
		}
		else {
			dp[front][back] = ERROR;
		}
	}
	return dp[front][back];
}

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);
	cout.tie(nullptr);
	cout.sync_with_stdio(false);

	int iter;
	cin >> iter;
	for (int i = 1; i <= iter;i++) {
		cin >> to_parse;
		dp = vector<vector<int>>(to_parse.length(), vector<int>(to_parse.length(), NOT_SEEN));
		cout << "Word #" << i << ": ";
		if (is_set(0, to_parse.length() - 1) == ERROR) {
			cout << "No ";
		}
		cout << "Set\n";
	}

	return 0;
}