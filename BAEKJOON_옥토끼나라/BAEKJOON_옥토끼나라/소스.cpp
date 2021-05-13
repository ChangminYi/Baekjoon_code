#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef class EDGE {
public:
	int start;
	int end;
	bool operator<(EDGE &e) {
		if (this->start == e.start) {
			return this->end < e.end;
		}
		else {
			return this->start < e.start;
		}
	}
} edge;

void swap(int &a, int &b) {
	int temp = a;
	a = b;
	b = temp;
}

int isIn(int _toFind, vector<vector<int>> &argi) {
	for (int i = 0; i < argi.size(); i++) {
		if (argi[i].front() == -1) {
			continue;
		}
		else {
			for (int j = 0; j < argi[i].size(); j++) {
				if (_toFind == argi[i][j]) {
					return i;
				}
			}
		}
	}
	return -1;
}

vector<vector<int>> subgraph(vector<edge> &arge, int _totalNum, int _quar) {
	vector<vector<int>> subg = vector<vector<int>>(_totalNum);
	for (int i = 0; i < subg.size(); i++) {
		subg[i].push_back(i);
	}

	for (int i = 0; i < arge.size(); i++) {
		int s_index = isIn(arge[i].start, subg);
		int e_index = isIn(arge[i].end, subg);
		if (s_index == -1 && e_index == -1) {	//이미 둘 다 들어감
			continue;
		}
		else if (s_index == -1) {	//end값이 어딘가에 들어가있음
			subg[e_index].push_back(arge[i].start);
		}
		else if (e_index == -1) {	//start값이 어딘가에 들어가있음
			subg[s_index].push_back(arge[i].end);
		}
		else {	//아직 둘 다 안들어감
			subg[s_index].push_back(arge[i].end);
			subg[e_index].front() = -1;
		}
	}

	for (int i = subg.size() - 1; i > -1; i--) {
		if (subg[i].front() == -1) {
			subg.erase(subg.begin() + i);
		}
	}

	return subg;
}

int accordNum(vector<int> &argi, vector<int> &_sorted) {
	int count = 0;
	for (int i = 0; i < argi.size(); i++) {
		if (binary_search(_sorted.begin(), _sorted.end(), argi[i])) { count++; }
	}
	return count;
}

int notSickLand(vector<vector<int>> argi, vector<int> _sickLand, int _minSick) {
	int count = 0;
	for (int i = 0; i < argi.size(); i++) {
		int temp = accordNum(argi[i], _sickLand);
		if (temp >= _minSick) { count += argi[i].size(); }
		else { count += temp; }
	}
	return count;
}

int main() {
	cin.tie(NULL);
	cin.sync_with_stdio(false);
	cout.tie(NULL);
	cout.sync_with_stdio(false);

	int N = 0, M = 0, K = 0, T = 0;
	cin >> N >> M >> K >> T;
	vector<edge> bridge = vector<edge>(M);
	for (edge &e : bridge) {
		int temp[2];
		cin >> temp[0] >> temp[1];
		if (--temp[0] > --temp[1]) { swap(temp[0], temp[1]); }
		e.start = temp[0];
		e.end = temp[1];
	}
	sort(bridge.begin(), bridge.end());
	vector<int> sickLand = vector<int>(K);
	for (int &i : sickLand) {
		cin >> i;
		i--;
	}
	sort(sickLand.begin(), sickLand.end());

	for (int i = 0; i < N; i++) {
		vector<edge>tempBridge(bridge);
		for (int j = tempBridge.size() - 1; j > -1; j--) {
			if (tempBridge[j].start == i || tempBridge[j].end == i) {
				tempBridge.erase(tempBridge.begin() + j);
			}
		}
		cout << N - notSickLand(subgraph(tempBridge, N, i), sickLand, T) << ' ';
	}


	return 0;
}