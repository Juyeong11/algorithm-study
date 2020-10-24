#include<iostream>

using namespace std;

typedef int KeyType;

struct Node {
	KeyType key;

	int priority, size;

	Node* left, * right;

	Node(const KeyType& _key) : key(_key), priority(rand()),
		size(1), left(NULL), right(NULL)
	{}
	void setLeft(Node* newLeft) { left = newLeft; calcSize(); }
	void setRight(Node* newRight) { right = newRight; calcSize(); }

	void calcSize()
	{
		size = 1;
		if (left) size += left->size;
		if (right)size += right->size;
	}
};
/*
��带 �߰� �ϱ� ���ؼ��� ���� ���� root�� node�� �켱������ Ȯ���ؾ� �Ѵ�.
���� node�� �켱������ �� ���ٸ� node�� root�� �Ǿ�� �ϱ� �����̴�.
�̷��� �� ��� ������ �� Ʈ���� �ִ� ������ ��� node�� �ڽ��� �Ǿ�� �Ѵ�.
���⼭ node�� ���� root�� ������ ũ�ٸ�, root�� ������ ����Ʈ���� ������ node�� ������ Ŭ ���� �ְ� ���� ���� �ִ�.
�׷��Ƿ� root�� ������ ���� Ʈ���� ���� node���� ū ���� ���� ���� ���� ������ ����Ʈ���� �ɰ����� ���� ����
root�� ������ ����Ʈ���� ���̰� ū���� node�� ������ ����Ʈ���� ���̸� ������ �Ϸ� �ȴ�.
*/
typedef pair<Node*, Node*> NodePair;

NodePair split(Node* root, KeyType key)
{
	if (root == NULL) return NodePair(NULL, NULL);

	//��Ʈ�� Ű �̸��̸� ������ ����Ʈ���� �ɰ���.
	if (root->key < key)
	{
		NodePair rs = split(root->right, key);
		root->setRight(rs.first);
		return NodePair(root, rs.second);
	}
	//��Ʈ�� Ű �̻��̸� ���� ����Ʈ���� �ɰ���.
	NodePair ls = (root->left, key);
	root->setLeft(ls.second);
	return NodePair(ls.first, root);
}

Node* insert(Node* root, Node* node)
{
	if (root == NULL) return node;

	if (root->priority < node->priority) {
		NodePair splitted = split(root, node->key);
		node->setLeft(splitted.first);
		node->setRight(splitted.second);
		return node;
	}
	else if (node->key < root->key)
		root->setLeft(insert(root->left, node));
	else
		root->setRight(insert(root->right, node));
	return root;//root�� �ٲ� �� ������ ��ȯ���� root�� ���־� �ٲ�� root���� �˷��ش�.
}

//a��b�� �� ���� Ʈ���̰�, max(a) < min(b) �� �� �� ���� ��ģ��.
Node* merge(Node* a, Node* b)
{
	if (a == NULL) return b;
	if (b == NULL) return a;
	if (a->priority < b->priority) {
		b->setLeft(merge(a, b->left));
		return b;
	}
	a->setRight(merge(a->right, b));
	return a;
}

Node* erase(Node* root, KeyType key)
{
	if (root == NULL) return root;

	//��Ʈ�� ����� �� ����Ʈ���� ��ģ �� ��ȯ�Ѵ�.
	if (root->key == key) {
		Node* ret = merge(root->left, root->right);
		delete root;
		return ret;
	}
	if (key < root->key)
		root->setLeft(erase(root->left, key));
	else
		root->setRight(erase(root->right, key));
	return root;
}

//k��° ���Ҹ� ��ȯ�Ѵ�.
Node* kth(Node* root, int k)
{
	int leftSize = 0;
	if (root->left != NULL) leftSize = root->left->size;
	if (k <= leftSize) return kth(root->left, k);
	if (k == leftSize + 1)return root;
	return kth(root->right, k - leftSize - 1);
}

//key ���� ���� Ű���� ���� ��ȯ�Ѵ�.
int countLessThan(Node* root, KeyType key)
{
	if (root == NULL) return 0;
	if (root->key >= key)
		return countLessThan(root->left, key);
	int ls = (root->left ? root->left->size : 0);
	return ls + 1 + countLessThan(root->right, key);
}
int main()
{

}