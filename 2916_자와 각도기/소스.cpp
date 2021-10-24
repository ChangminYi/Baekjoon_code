#include <iostream>
#include <vector>

using namespace std;

const int MAX_ANGLE = 360;

int n, k;
bool visit[MAX_ANGLE + 1] = { false };
vector<int> angles, to_find;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> k;
    angles.resize(n), to_find.resize(k);

    for (int& i : angles) {
        cin >> i;
        visit[i] = true;
    }
    for (int& i : to_find) {
        cin >> i;
    }

    // 두 각 더하여 새로운 각 생성
    while (true) {
        bool new_added = false;

        for (size_t i = 0; i < angles.size(); i++) {
            for (size_t j = 0; j < angles.size(); j++) {
                int new_angle = (angles[i] + angles[j]) % MAX_ANGLE;

                if (!visit[new_angle]) {
                    visit[new_angle] = true;
                    new_added = true;
                    angles.push_back(new_angle);
                }
            }
        }

        if (!new_added) {
            break;
        }
    }
    //두 각 빼서 새로운 각 생성
    while (true) {
        bool new_added = false;

        for (size_t i = 0; i < angles.size(); i++) {
            for (size_t j = 0; j < angles.size(); j++) {
                int new_angle = (angles[i] - angles[j] + MAX_ANGLE) % MAX_ANGLE;

                if (!visit[new_angle]) {
                    visit[new_angle] = true;
                    new_added = true;
                    angles.push_back(new_angle);
                }
            }
        }

        if (!new_added) {
            break;
        }
    }

    for (const int& i : to_find) {
        cout << (visit[i] ? "YES\n" : "NO\n");
    }

    return 0;
}