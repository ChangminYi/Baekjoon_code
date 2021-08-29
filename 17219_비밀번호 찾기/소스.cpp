#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;

int main() {
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin.sync_with_stdio(false);
	cout.sync_with_stdio(false);
	
	int N = 0, M = 0;
	cin >> N >> M;

	unordered_map<string, string> mp;
	for (int i = 0; i < N; i++) {
		string url, pw;
		cin >> url >> pw;
		mp.insert(make_pair(url, pw));
	}

	for (int i = 0; i < M; i++) {
		string toFind;
		cin >> toFind;
		cout << mp[toFind] << '\n';
	}

	return 0;
}