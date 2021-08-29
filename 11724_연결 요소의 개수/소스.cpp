#include <iostream>
#include <vector>
using namespace std;

typedef class NODE{
public:
	bool isConnectedWith(int nodeNum) {
		for (int i : this->edge) {
			if (nodeNum == i) {
				return true;
			}
		}
		return false;
	}
	void addEdge(int nodeNum) {
		if (!isConnectedWith(nodeNum)) {
			this->edge.push_back(nodeNum);
		}
	}
	const vector<int> getAllEdge() {
		return this->edge;
	}
private:
	vector<int> edge;
} node;

const bool canVisit(vector<bool> &argb) {
	for (bool b : argb) {
		if (!b) {
			return true;
		}
	}
	return false;
}

bool isInVector(int data, vector<int> &v) {
	for (int i : v) {
		if (data == i) {
			return true;
		}
	}
	return false;
}

const vector<vector<int>> getSubgraph(vector<node> &graph) {
	vector<vector<int>> subgraph;
	vector<int> temp;
	vector<bool> isVisited = vector<bool>(graph.size(), false);
	int index = 0;

	while (canVisit(isVisited)) {
		temp.push_back(index);
		isVisited[index] = true;

		for (int i = 0; i < temp.size(); i++) {
			vector<int> argi = graph[temp[i]].getAllEdge();
			for (int j : argi) {
				if (!isInVector(j, temp)) {
					temp.push_back(j);
				}
			}

			isVisited[temp[i]] = true;
		}

		subgraph.push_back(temp);
		temp.clear();
		while (index<graph.size() && isVisited[index]) {
			index++;
		}
	}

	return subgraph;
}

int main() {
	int numOfNode = 0, numOfEdge = 0;
	cin >> numOfNode >> numOfEdge;
	vector<node> graph = vector<node>(numOfNode);
	for (int i = 0, temp[2]; i < numOfEdge; i++) {
		cin >> temp[0] >> temp[1];
		temp[0]--; temp[1]--;
		graph[temp[0]].addEdge(temp[1]);
		graph[temp[1]].addEdge(temp[0]);
	}

	cout << getSubgraph(graph).size();

	return 0;
}