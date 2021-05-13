//�ð��ʰ�->hash map���� �˻��ð� ���̸� ����
//key�� string, value�� ������ ������ ��

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