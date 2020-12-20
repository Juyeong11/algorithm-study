#include<iostream>

using namespace std;

/*
��ĭ�� �� �� �ִ� ���ڰ� 1~9 ���� ���� ��Ʈ�� ǥ���� 2^9 = 1024�� ǥ��
*/
int getSize(int mask);
int getSum(int mask);

//lenĭ�� ���� sum�̰� �� ĭ�鿡 �̹� ���� ���� ������ known�϶� ������ ĭ�� �� �� �ִ� ������ ������ ��ȯ�Ѵ�.
int getCandidates(int len, int sum, int known)
{
	int allSets = 0;
	for (int set = 0; set < 1024; set += 2) {
		if ((set & known) == known && getSize(set) == len && getSum(set) == sum)
			allSets |= set;
	}
	return allSets & ~known;
}

//[len][sum][known]
int candidates[10][46][1024];

void generateCandidates()
{
	memset(candidates, 0, sizeof(candidates));

	for (int set = 0; set < 1024; set += 2) {
		int l = getSize(set), s = getSum(set);
		int subset = set;
		while (true) {
			candidates[l][s][subset] |= (set & ~subset);//���̰� l�̰� ����s�϶� subset�� ���� ������ ���� �� �� ���� �� �ִ� ���� ������ ��ȯ���ش�.
			if (subset == 0)break;
			subset = (subset - 1) & set;//(subset-1) �����ִ� ������ ��Ʈ�� ���� �� ���� ��Ʈ�� ��� Ų�ٻ������� �ű�ٰ� &set�� ���ִϱ� ������ ��Ʈ�� ����� ���� �ȴ�.
		}
	}
}
const int MAXN = 50;
//color: �� ĭ�� ��, value: �� �� ĭ�� �� ����, hint:�� ĭ�� �ش��ϴ� �� ��Ʈ�� ��ȣ
int n, color[MAXN][MAXN], value[MAXN][MAXN], hint[MAXN][MAXN][2];
//sum: ��Ʈ ĭ�� ���� ����, length: ��Ʈ ĭ�� �ش��ϴ� �� ĭ�� ��, known: ��Ʈ ĭ�� �ش��ϴ� ��ĭ�� ���� ���ڵ��� ����
int q, sum[MAXN * MAXN], length[MAXN * MAXN], known[MAXN * MAXN];

void put(int y, int x, int val) {
	for (int h = 0; h < 2; ++h)
		known[hint[y][x][h]] += (1 << val);
	value[y][x] = val;
}
void remove(int y, int x, int val){
	for (int h = 0; h < 2; ++h)
		known[hint[y][x][h]] -= (1 << val);
	value[y][x] = 0;
}
int getCandHint(int hint) {
	return candidates[length[hint]][sum[hint]][known[hint]];
}
int getCandCoord(int y, int x) {
	return getCandHint(hint[y][x][0]) & getCandHint(hint[y][x][1]);
}

void printSolution();
const bool WHITE = 1;
const bool BLACK = 0;
bool search()
{
	int y = -1, x = -1, minCands = 1023;
	for(int i=0;i<n;++i)
		for(int j=0;j<n;++j)
			if (color[i][j] == WHITE && value[i][j] == 0)
			{
				int cands = getCandCoord(i, j);
				if (getSize(minCands) > getSize(cands)) {
					minCands = cands;
					y = i; x = j;
				}
			}
	if (minCands == 0)return false;
	if (y == -1) {
		printSolution();
		return true;
	}
	for(int val=1;val<=9;++val)
		if (minCands & (1 << val)) {
			put(y, x, val);
			if (search())return true;
			remove(y, x, val);
		}
	return false;
}
int main()
{

}