//시간초과->hash map으로 검색시간 줄이면 가능
//key를 string, value를 순서로 넣으면 됨

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;


int main() {
	unordered_map<string, int> set;
	vector<string> answer;
	int size = 0, count = 0;

	cin >> size;
	string temp;
	for (int i = 0; i < size; i++) {
		cin >> temp;
		set.insert(make_pair(temp, i));
	}
	for (int i = 0; i < size; i++) {
		cin >> temp;
		answer.push_back(temp);
	}


	for (int i = 0; i < size - 1; i++) {
		for (int j = i + 1; j < size; j++) {
			if (set[answer[i]] < set[answer[j]]) {
				count++;
			}
		}
	}

	cout << count << '/' << ((size - 1)*size) / 2;

	return 0;
}