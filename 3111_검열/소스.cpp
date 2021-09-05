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
		//문자열 왼쪽 부분 검열
		while (lo <= hi) {
			bool str_found = false;
			str_left.push_back(origin[lo++]);

			if (str_left.size() >= to_remove.length()) {
				str_found = true;

				//좌측 문자열에서 삭제할 문자열 검색
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

		//문자열 오른쪽 부분 검열
		while (lo <= hi) {
			bool str_found = false;
			str_right.push_front(origin[hi--]);

			if (str_right.size() >= to_remove.length()) {
				str_found = true;

				//우측 문자열에서 삭제할 문자열 검색
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

	//좌우 합쳤을 시 나타날 수 있는 문자열 삭제
	while (res.find(to_remove) != string::npos) {
		res.erase(res.find(to_remove), to_remove.length());
	}

	cout << res;

	return 0;
}