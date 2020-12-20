#include<iostream>

using namespace std;

/*
빈칸에 들어갈 수 있는 숫자가 1~9 사이 숫자 비트로 표현해 2^9 = 1024로 표현
*/
int getSize(int mask);
int getSum(int mask);

//len칸의 합이 sum이고 이 칸들에 이미 쓰인 수의 집합이 known일때 나머지 칸에 들어갈 수 있는 숫자의 집합을 반환한다.
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
			candidates[l][s][subset] |= (set & ~subset);//길이가 l이고 합이s일때 subset인 숫자 집합이 있을 때 더 넣을 수 있는 숫자 집합을 반환해준다.
			if (subset == 0)break;
			subset = (subset - 1) & set;//(subset-1) 켜져있는 최하위 비트를 끄고 그 밑의 비트를 모두 킨다생각하자 거기다가 &set을 해주니까 최하위 비트만 지우는 것이 된다.
		}
	}
}
const int MAXN = 50;
//color: 각 칸의 색, value: 각 흰 칸에 쓴 숫자, hint:각 칸에 해당하는 두 힌트의 번호
int n, color[MAXN][MAXN], value[MAXN][MAXN], hint[MAXN][MAXN][2];
//sum: 힌트 칸에 쓰인 숫자, length: 힌트 칸에 해당하는 흰 칸의 수, known: 힌트 칸에 해당하는 흰칸에 쓰인 숫자들의 집합
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