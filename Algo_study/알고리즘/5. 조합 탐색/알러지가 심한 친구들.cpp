#include<iostream>
#include<vector>

using namespace std;

int n, m;
vector<int> canEat[50], eaters[50];//i��ģ���� ���� �� �ִ� ���� ����, i�� ������ ���� �� �ִ� ģ���� ����
int best;
//edible ���ݱ��� �� ���� ��  i�� ģ���� ���� �� �ִ� ������ ��
void search(vector<int>& edible, int chosen)
{
	if (chosen >= best)return;

	int first = 0;
	while (first < n && edible[first] > 0) ++first;//���� �� �ִ� ������ ������ ���� ģ���� ã�� ����ȭ���

	if (first == n) { best = chosen; return; }

	for (int i = 0; i < canEat[first].size(); ++i) {//first�� ���� �� �ִ� ���� ��
		int food = canEat[first][i];//������ �����Ҷ� ���� ���� ����� ���� �� �ִ� ���� ���� �õ�.
		for (int j = 0; j < eaters[food].size(); ++j)
			edible[eaters[food][j]]++;
		search(edible, chosen + 1);
		for (int j = 0; j < eaters[food].size(); ++j)
			edible[eaters[food][j]]--;
	}
}
int main()
{

}