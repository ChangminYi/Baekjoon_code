#include <iostream>
#include <algorithm>
#include <string>
#include <deque>

using namespace std;

typedef struct PERSON {
	int age;
	string name;
}per;

bool comp(per a, per b) {
	return a.age < b.age;
}

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);

	int size = 0;
	cin >> size;

	deque<per> list(size);
	for (per &p : list) {
		cin >> p.age >> p.name;
	}

	stable_sort(list.begin(), list.end(), comp);

	for (per &p : list) {
		cout << p.age << ' ' << p.name << '\n';
	}

	return 0;
}