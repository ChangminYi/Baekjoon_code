#include <iostream>
#include <vector>

using namespace std;

int n, q, k;
vector<int> adj[250001];
int tree_par[250001];
int set_par[250001], set_size[250001];
int arg[250000];
bool in_arg[250001];

void dfs(int cur, int par) {
    for(const int& nxt: adj[cur]) {
        if(nxt == par)
            continue;
        tree_par[nxt] = cur;
        dfs(nxt, cur);
    }
}

int find_par(int cur) {
    if(set_par[cur] == cur)
        return cur;
    else
        return set_par[cur] = find_par(set_par[cur]);
}

void union_set(int x, int y) {
    int px = find_par(x), py = find_par(y);
    if(px == py)
        return;
    set_size[px] += set_size[py];
    set_par[py] = px;
}

int main() {
    /**
     * union-find를 통해서 k개의 정점의 인접 여부를 관리할 수 있다.
     * 쿼리에 대한 응답을 하기 전, dfs를 실행하여 트리의 형태를 완성하고,
     * 각 노드의 부모 노드를 저장한다. 쿼리를 처리할 때, 각 노드의 부모 노드가
     * S 안에 있는지를 확인한 후, 존재한다면 같은 집합으로 묶음으로써 인접함을 표시한다.
     * 모든 노드에 대해서 union이 끝나면, 각 set의 크기를 통해 가능한 쌍의 수를 구한다.
     * 쌍의 수가 int를 넘어갈 수 있음을 주의해야 한다. 그 후, 다음 쿼리를 위해
     * S의 원소들과 관련된 변수를 모두 초기화해준다.
     */
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> n;
    for(int i = 0, u, v; i < n - 1; i++) {
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs(1, 0);
    for(int i = 1; i <= n; i++) {
        set_par[i] = i;
        set_size[i] = 1;
    }

    cin >> q;
    do {
        cin >> k;
        for(int i = 0; i < k; i++) {
            cin >> arg[i];
            in_arg[arg[i]] = true;
        }
        
        for(int i = 0; i < k; i++) {
            if(in_arg[arg[i]] && in_arg[tree_par[arg[i]]])
                union_set(arg[i], tree_par[arg[i]]);
        }

        long long sum = 0;
        for(int i = 0, par; i < k; i++) {
            if(find_par(arg[i]) == arg[i])
                sum += (long long)set_size[arg[i]] * (set_size[arg[i]] - 1) / 2;
        }
        cout << sum << '\n';

        for(int i = 0; i < k; i++) {
            in_arg[arg[i]] = false;
            set_par[arg[i]] = arg[i];
            set_size[arg[i]] = 1;
        }
    } while(--q);

    return 0;
}