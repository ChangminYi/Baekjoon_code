#include <iostream>
#include <vector>

using namespace std;

int n, m, k;
vector<int> graph[2'001], bombed;
bool origin_destroy[2'001], rep_destroy[2'001];

bool is_same_map() {
    for (int i = 1; i <= n; i++) {
        if (origin_destroy[i] != rep_destroy[i]) return false;
    }
    return true;
}

bool adj_all_destroyed(const int cur) {
    for (const int& adj : graph[cur]) {
        if (!origin_destroy[adj]) return false;
    }
    return true;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    /*
    * ���� �ڽŵ� ���ݵǾ���, ���� ���ð� ��� ���ݵǾ��ٸ� ���� ��ȣ�� �����Ѵ�.
    * �̸� ���ؼ� ���� ��Ȳ�� ���� �����, �Է����� ���� ��Ȳ�� ������ ���Ѵ�.
    * �� ����� ���ؼ� ���� ���� ���ð� ���� ���� ���ݴ��� ��찡 �ȴ�.
    */

    cin >> n >> m;
    for (int n1, n2; m; m--) {
        cin >> n1 >> n2;
        graph[n1].push_back(n2);
        graph[n2].push_back(n1);
    }
    cin >> k;
    for (int i; k; k--) {
        cin >> i;
        origin_destroy[i] = true;
    }

    for (int i = 1; i <= n; i++) {
        if (origin_destroy[i] && adj_all_destroyed(i)) {
            bombed.push_back(i);
            rep_destroy[i] = true;
            for (const int& adj : graph[i]) {
                rep_destroy[adj] = true;
            }
        }
    }

    if (is_same_map()) {
        cout << bombed.size() << '\n';
        for (const int& i : bombed) {
            cout << i << ' ';
        }
    }
    else {
        cout << -1;
    }

    return 0;
}