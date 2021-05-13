#include <iostream>

using namespace std;

int Index[100001] = { 0 };
int inorder[100001] = { 0 };
int postorder[100001] = { 0 };


// preorder �� ����ϴ� �Լ� (���)
void getPreOrder(int inStart, int inEnd, int postStart, int postEnd) {
	// �� �̻� ���� �� �� ���� ��� return
	if (inStart > inEnd || postStart > postEnd) {
		return;
	}
	else {
		// postorder�� �� ���� root��
		// Index �迭�� ���� inorder������ root index�� ���� ���� �� �ִ�.
		int rootIndex = Index[postorder[postEnd]];
		int leftSize = rootIndex - inStart;
		int rightSize = inEnd - rootIndex;

		cout << inorder[rootIndex] << ' '; // root �� ���

		// ��� �Լ� ȣ��
		getPreOrder(inStart, rootIndex - 1, postStart, postStart + leftSize - 1);
		getPreOrder(rootIndex + 1, inEnd, postStart + leftSize, postEnd - 1);
	}
}

int main() {
	cin.sync_with_stdio(false);
	cout.sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int n = 0;
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> inorder[i];
		Index[inorder[i]] = i; // inorder ��ҵ��� Index ���� ����
	}
	for (int i = 1; i <= n; i++) {
		cin >> postorder[i];
	}

	getPreOrder(1, n, 1, n);

	return 0;
}