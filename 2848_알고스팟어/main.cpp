#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

int n;
string arg[100];
vector<char> alpha_set, seq;
vector<int> graph[26];
int in_degree[26];
bool alpha_appear[26], many_child = false, wrong_order = false;
queue<int> q;
	
int main() {
    /**
     * 두 문자열 간 비교를 통해 알파벳의 선후 관계를 정한다.
     * 만약 비교 가능한 모든 알파벳이 같고 앞의 문자열이 더 길다면,
     * 이는 잘못된 순서로 들어온 문자열이므로 !를 출력한다.
     * 위상 정렬을 통해 순서를 정하는데, 큐에 2개 이상의 노드가 들어가면
     * 해당 노드들은 선후 관계를 정할 수 없으므로 ?를 출력한다.
     * 위상 정렬이 끝나면 알파벳을 방문한 순서대로 출력한다.
     */

	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);

	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> arg[i];
        for(const char c: arg[i]) {
            if(!alpha_appear[c - 'a']) {
                alpha_appear[c - 'a'] = true;
                alpha_set.push_back(c);
            }
        }
	}

	for (int i = 0; i < n - 1; i++) {
        bool order_found = false;
		for (int j = 0; j < min(arg[i].length(), arg[i + 1].length()); j++) {
			if (arg[i][j] != arg[i + 1][j]) {
				graph[arg[i][j] - 'a'].push_back(arg[i + 1][j] - 'a');
				in_degree[arg[i + 1][j] - 'a']++;
				order_found = true;
                break;
			}
		}

        if(!order_found && arg[i].length() > arg[i + 1].length()) {
            wrong_order = true;
            break;
        }
	}

    for(const char c: alpha_set) {
        if(in_degree[c - 'a'] == 0)
            q.push(c - 'a');
    }
	while (!q.empty()) {
		if (q.size() > 1)
			many_child = true;

		int cur = q.front(); q.pop();
		seq.push_back(cur + 'a');

        for(const int& nxt: graph[cur]) {
            if(--in_degree[nxt] == 0)
                q.push(nxt);
        }
	}

	if (wrong_order || seq.size() != alpha_set.size())
		cout << '!';
	else if (many_child)
		cout << '?';
	else {
        for(const char c: seq)
            cout << c;
	}

	return 0;
}