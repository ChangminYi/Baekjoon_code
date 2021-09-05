#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>

using namespace std;

const int NUM_ALPHA = 26;

string needle, haystack;
vector<int> hash_needle(NUM_ALPHA, 0), hash_haystack(NUM_ALPHA, 0);
hash<string> hasher;
unordered_set<long long> hash_set;

bool hash_cmp() {
	for (int i = 0; i < NUM_ALPHA; i++) {
		if (hash_needle[i] != hash_haystack[i]) {
			return false;
		}
	}
	return true;
}

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);

	cin >> needle >> haystack;
	if (needle.length() > haystack.length()) {
		// haystack이 더 짧으면 반드시 없음
		cout << 0;
	}
	else {
		// 각 문자열의 조합 초기화
		for (const char& c : needle) {
			hash_needle[c - 'a']++;
		}
		for (size_t i = 0; i < needle.length(); i++) {
			hash_haystack[haystack[i] - 'a']++;
		}

		/*
		* 만약 needle의 길이 안에서
		* 알파벳 수가 서로 같으면 haystack의 부분 문자열은
		* needle의 조합 중 하나라고 판단 가능.
		* string을 모두 set에 넣으면 메모리 초과가 나오므로
		* 해싱하여 해시 값만을 저장.
		*/
		for (size_t i = 0; i + needle.length() <= haystack.length(); i++) {
			if (hash_cmp()) {
				hash_set.insert(hasher(haystack.substr(i, needle.length())));
			}

			// 다음 번 문자열 알파벳 수 업데이트
			if (i + needle.length() < haystack.length()) {
				hash_haystack[haystack[i] - 'a']--;
				hash_haystack[haystack[i + needle.length()] - 'a']++;
			}
		}

		cout << hash_set.size();
	}

	return 0;
}