//개미굴은 일종의 tree
//적당히 노드 만들어서 트리 만들어준 다음에
//dfs로 출력만 맞춰주면 된다.

#include <iostream>
#include <vector>
#include <string>
using namespace std;

typedef class NODE {
public:
	~NODE() {
		if (this->child.empty()) {
			return;
		}
		else {
			for (NODE *n : this->child) {
				delete n;
			}
		}
	}
	NODE() {}
	NODE(string &s) : key(s) {}
	NODE* pushChild(string &s) {
		NODE *newNode = new NODE(s);
		if (this->child.empty()) {
			this->child.push_back(newNode);
			return newNode;
		}
		else {
			for (int i = 0; i < this->child.size(); i++) {
				if (this->child[i]->key == newNode->key) {
					return this->child[i];
				}
				else if (this->child[i]->key > newNode->key) {
					this->child.insert(this->child.begin() + i, newNode);
					return newNode;
				}
			}
			this->child.push_back(newNode);
			return newNode;
		}
	}
	void pushChild(vector<string> &args) {
		if (args.empty()) {
			return;
		}
		else {
			NODE *togo = this->pushChild(args.front());
			vector<string> toPush = vector<string>(args.begin() + 1, args.end());
			togo->pushChild(toPush);
		}
	}
	void print() {
		this->print("");
	}
	void print(string s) {
		if (this->key.empty() == false) {
			cout << s << this->key << '\n';
		}
		for (int i = 0; i < this->child.size(); i++) {
			this->child[i]->print(s + "--");
		}
	}
	vector<NODE *> getChild() {
		return this->child;
	}
private:
	string key;
	vector<NODE *> child;
}node;



int main() {
	cin.tie(NULL);
	cin.sync_with_stdio(false);

	node *root = new node();
	int num = 0;
	cin >> num;

	for (int i = 0; i < num; i++) {
		int tempInt = 0;
		cin >> tempInt;
		vector<string> tempStr(tempInt);
		for (string &s : tempStr) {
			cin >> s;
		}

		root->pushChild(tempStr);
	}

	for (node *n : root->getChild()) {
		n->print();
	}

	delete root;
	return 0;
}