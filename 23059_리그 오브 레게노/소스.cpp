#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <unordered_map>
#include <algorithm>

using namespace std;

int n, cnt = 0;
vector<pair<string, string>> edge;
vector<string> str;
vector<int> degree;
vector<list<int>> graph;
vector<vector<int>> seq;
unordered_map<string, int> str_idx;

bool cmp(const int lhs, const int rhs) {
    return str[lhs] < str[rhs];
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n;
    edge.resize(n);
    for (pair<string, string>& pstr : edge) {
        cin >> pstr.first >> pstr.second;

        if(str_idx.find(pstr.first) == str_idx.end()){
            str_idx.insert(make_pair(pstr.first, cnt++));
        }
        if (str_idx.find(pstr.second) == str_idx.end()) {
            str_idx.insert(make_pair(pstr.second, cnt++));
        }
    }

    str.resize(str_idx.size());
    degree.resize(str_idx.size());
    graph.resize(str_idx.size());
    for (pair<string, string>& pstr : edge) {
        if (str[str_idx[pstr.first]].empty()) {
            str[str_idx[pstr.first]] = pstr.first;
        }
        if (str[str_idx[pstr.second]].empty()) {
            str[str_idx[pstr.second]] = pstr.second;
        }

        graph[str_idx[pstr.first]].push_back(str_idx[pstr.second]);
        degree[str_idx[pstr.second]]++;
    }

    /*
    * 위상정렬을 하되, 레벨 별로 정리해줘야 한다.
    * 같은 레벨끼리 모아서 그 안에서 문자열 사전순으로 정렬
    * 그리고 출력하면 된다.
    */
    int total_cnt = 0;
    seq.resize(1);
    for (int i = 0; i < (int)str_idx.size(); i++) {
        if (degree[i] == 0) {
            total_cnt++;
            seq.back().push_back(i);
        }
    }
    while (true) {
        vector<int> tmp;

        for (const int& cur : seq.back()) {
            for (const int& nxt : graph[cur]) {
                if (--degree[nxt] == 0) {
                    total_cnt++;
                    tmp.push_back(nxt);
                }
            }
        }

        if (tmp.empty()) {
            break;
        }
        else {
            seq.push_back(tmp);
        }
    }

    if(total_cnt < (int)str_idx.size()){
        cout << -1;
    }
    else {
        for (vector<int>& row : seq) {
            sort(row.begin(), row.end(), cmp);
            
            for (const int& i : row) {
                cout << str[i] << '\n';
            }
        }
    }

    return 0;
}