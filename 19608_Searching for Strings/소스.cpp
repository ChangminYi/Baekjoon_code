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
		// haystack�� �� ª���� �ݵ�� ����
		cout << 0;
	}
	else {
		// �� ���ڿ��� ���� �ʱ�ȭ
		for (const char& c : needle) {
			hash_needle[c - 'a']++;
		}
		for (size_t i = 0; i < needle.length(); i++) {
			hash_haystack[haystack[i] - 'a']++;
		}

		/*
		* ���� needle�� ���� �ȿ���
		* ���ĺ� ���� ���� ������ haystack�� �κ� ���ڿ���
		* needle�� ���� �� �ϳ���� �Ǵ� ����.
		* string�� ��� set�� ������ �޸� �ʰ��� �����Ƿ�
		* �ؽ��Ͽ� �ؽ� ������ ����.
		*/
		for (size_t i = 0; i + needle.length() <= haystack.length(); i++) {
			if (hash_cmp()) {
				hash_set.insert(hasher(haystack.substr(i, needle.length())));
			}

			// ���� �� ���ڿ� ���ĺ� �� ������Ʈ
			if (i + needle.length() < haystack.length()) {
				hash_haystack[haystack[i] - 'a']--;
				hash_haystack[haystack[i + needle.length()] - 'a']++;
			}
		}

		cout << hash_set.size();
	}

	return 0;
}