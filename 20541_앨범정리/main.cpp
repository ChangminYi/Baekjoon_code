#include <iostream>
#include <string>
#include <set>
#include <map>

using namespace std;

typedef pair<int, int> pint;

struct node {
    node *parent;
    string folder_name;
    set<string> image;
    map<string, node *> child;

    node(const string& _n = "album", node *_p = nullptr) : folder_name(_n), parent(_p) {}
    ~node() {
        for(auto iter = child.begin(); iter != child.end(); iter++) {
            delete iter->second;
        }
        parent = nullptr;
        image.clear();
        child.clear();
    }
};

int n;
string inst[2];
node *head = new node;

void operator+=(pint &lhs, const pint& rhs) {
    lhs.first += rhs.first, lhs.second += rhs.second;
}

pint get_delete_num(node *cur) {
    pint ret = pint(0, 0);

    for(auto it = cur->child.begin(); it != cur->child.end(); it++) {
        ret += get_delete_num(it->second);
    }
    ret.first += cur->child.size();
    ret.second += cur->image.size();

    return ret;
}

int main() {
    /**
     * 폴더 구조체를 만든다. 자식 폴더들은 map을 사용하고, 폴더 내 이미지는 set을 사용한다.
     * 삭제 시에는 재귀적으로 자식 폴더까지 모두 삭제한 결과를 출력해야 한다.
     * 나머지는 요구 사항을 따라 구현하면 된다.
     */

    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    node *cur = head;
    cin >> n;
    do {
        cin >> inst[0] >> inst[1];
        if(inst[0] == "mkalb") {
            if(cur->child.find(inst[1]) == cur->child.end()) {
                cur->child.insert(make_pair(inst[1], new node(inst[1], cur)));
            }
            else {
                cout << "duplicated album name\n";
            }
        }
        else if(inst[0] == "rmalb") {
            pint ret = pint(0, 0);
            if(inst[1] == "-1") {
                if(!cur->child.empty()) {
                    ret = get_delete_num(cur->child.begin()->second);
                    ret.first++;
                    delete cur->child.begin()->second;
                    cur->child.erase(cur->child.begin());
                }
            }
            else if(inst[1] == "0") {
                for(auto iter = cur->child.begin(); iter != cur->child.end(); iter++) {
                    ret += get_delete_num(iter->second);
                    delete iter->second;
                }
                ret.first += cur->child.size();
                cur->child.clear();
            }
            else if(inst[1] == "1") {
                if(!cur->child.empty()) {
                    ret = get_delete_num((--cur->child.end())->second);
                    ret.first++;
                    delete (--cur->child.end())->second;
                    cur->child.erase(--cur->child.end());
                }
            }
            else {
                auto idx = cur->child.find(inst[1]);
                if(idx != cur->child.end()) {
                    ret = get_delete_num(idx->second);
                    ret.first++;
                    delete idx->second;
                    cur->child.erase(idx);
                }
            }

            cout << ret.first << ' ' << ret.second << '\n';
        }
        else if(inst[0] == "insert") {
            if(cur->image.find(inst[1]) == cur->image.end()) {
                cur->image.insert(inst[1]);
            }
            else {
                cout << "duplicated photo name\n";
            }
        }
        else if(inst[0] == "delete") {
            int ret = 0;
            if(inst[1] == "-1") {
                if(!cur->image.empty()) {
                    ret++;
                    cur->image.erase(cur->image.begin());
                }
            }
            else if(inst[1] == "0") {
                ret += cur->image.size();
                cur->image.clear();
            }
            else if(inst[1] == "1") {
                if(!cur->image.empty()) {
                    ret++;
                    cur->image.erase(--cur->image.end());
                }
            }
            else {
                auto idx = cur->image.find(inst[1]);
                if(idx != cur->image.end()) {
                    ret++;
                    cur->image.erase(idx);
                }
            }

            cout << ret << '\n';
        }
        else {
            if(inst[1] == "..") {
                if(cur->parent != nullptr) cur = cur->parent;
            }
            else if(inst[1] == "/") {
                cur = head;
            }
            else {
                auto idx = cur->child.find(inst[1]);
                if(idx != cur->child.end()) {
                    cur = idx->second;
                }
            }

            cout << cur->folder_name << '\n';
        }
    } while(--n);

    delete head;

    return 0;
}