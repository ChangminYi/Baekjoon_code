#include <iostream>
#include <string>
#include <map>
#include <iomanip>

using namespace std;

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);
	cout.tie(nullptr);
	cout.sync_with_stdio(false);

	map<string, int> stat;
	string temp;
	int total_count = 0;

	while (getline(cin, temp)) {
		if (stat.find(temp) != stat.end()) {
			stat[temp]++;
		}
		else {
			stat.insert(make_pair(temp, 1));
		}

		total_count++;
	}

	cout << fixed;
	cout.precision(4);
	for (map<string, int>::iterator i = stat.begin(); i != stat.end(); i++) {
		cout << (*i).first << ' ' << (double)(*i).second / total_count * 100 << '\n';
	}

	return 0;
}