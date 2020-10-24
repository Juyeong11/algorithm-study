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
노드를 추가 하기 위해서는 가장 먼저 root와 node의 우선순위를 확인해야 한다.
만약 node의 우선순위가 더 높다면 node가 root가 되어야 하기 때문이다.
이렇게 될 경우 기존에 이 트리에 있던 노드들은 모두 node의 자식이 되어야 한다.
여기서 node의 값이 root의 값보다 크다면, root의 오른쪽 서브트리의 값들은 node의 값보다 클 수도 있고 작을 수도 있다.
그러므로 root의 오른쪽 서브 트리의 값을 node보다 큰 값과 작은 값을 가진 각각의 서브트리로 쪼갠다음 작은 값을
root의 오른쪽 서브트리로 붙이고 큰값을 node의 오른쪽 서브트리로 붙이면 삽입이 완료 된다.
*/
typedef pair<Node*, Node*> NodePair;

NodePair split(Node* root, KeyType key)
{
	if (root == NULL) return NodePair(NULL, NULL);

	//루트가 키 미만이면 오른쪽 서브트리를 쪼갠다.
	if (root->key < key)
	{
		NodePair rs = split(root->right, key);
		root->setRight(rs.first);
		return NodePair(root, rs.second);
	}
	//루트가 키 이상이면 왼쪽 서브트리를 쪼갠다.
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
	return root;//root가 바뀔 수 있으니 반환값을 root로 해주어 바뀌는 root값을 알려준다.
}

//a와b가 두 개의 트립이고, max(a) < min(b) 일 때 이 둘을 합친다.
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

	//루트를 지우고 양 서브트리를 합친 뒤 반환한다.
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

//k번째 원소를 반환한다.
Node* kth(Node* root, int k)
{
	int leftSize = 0;
	if (root->left != NULL) leftSize = root->left->size;
	if (k <= leftSize) return kth(root->left, k);
	if (k == leftSize + 1)return root;
	return kth(root->right, k - leftSize - 1);
}

//key 보다 작은 키값의 수를 반환한다.
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