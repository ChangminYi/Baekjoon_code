#include <iostream>
#include <deque>
#include <string>

using namespace std;

string to_remove, origin, res;
deque<char> str_left, str_right;

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);

	cin >> to_remove >> origin;
	
	for (int lo = 0, hi = (int)origin.length() - 1; lo <= hi;) {
		//���ڿ� ���� �κ� �˿�
		while (lo <= hi) {
			bool str_found = false;
			str_left.push_back(origin[lo++]);

			if (str_left.size() >= to_remove.length()) {
				str_found = true;

				//���� ���ڿ����� ������ ���ڿ� �˻�
				for (size_t i = 0; i < to_remove.length(); i++) {
					if (to_remove[i] != str_left[str_left.size() - to_remove.length() + i]) {
						str_found = false;
						break;
					}
				}
			}

			if (str_found) {
				for (size_t i = 0; i < to_remove.length(); i++) {
					str_left.pop_back();
				}
				break;
			}
		}

		//���ڿ� ������ �κ� �˿�
		while (lo <= hi) {
			bool str_found = false;
			str_right.push_front(origin[hi--]);

			if (str_right.size() >= to_remove.length()) {
				str_found = true;

				//���� ���ڿ����� ������ ���ڿ� �˻�
				for (size_t i = 0; i < to_remove.length(); i++) {
					if (to_remove[i] != str_right[i]) {
						str_found = false;
						break;
					}
				}
			}

			if (str_found) {
				for (size_t i = 0; i < to_remove.length(); i++) {
					str_right.pop_front();
				}
				break;
			}
		}
	}

	for (const char& c : str_left) {
		res += c;
	}
	for (const char& c : str_right) {
		res += c;
	}

	//�¿� ������ �� ��Ÿ�� �� �ִ� ���ڿ� ����
	while (res.find(to_remove) != string::npos) {
		res.erase(res.find(to_remove), to_remove.length());
	}

	cout << res;

	return 0;
}