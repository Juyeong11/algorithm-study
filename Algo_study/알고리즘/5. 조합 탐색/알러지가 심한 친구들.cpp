#include<iostream>
#include<vector>

using namespace std;

int n, m;
vector<int> canEat[50], eaters[50];//i번친구가 먹을 수 있는 음식 집합, i번 음식을 먹을 수 있는 친구들 집합
int best;
//edible 지금까지 고른 음식 중  i번 친구가 먹을 수 있는 음식의 수
void search(vector<int>& edible, int chosen)
{
	if (chosen >= best)return;

	int first = 0;
	while (first < n && edible[first] > 0) ++first;//먹을 수 있는 음식의 종류가 적은 친구를 찾는 최적화방법

	if (first == n) { best = chosen; return; }

	for (int i = 0; i < canEat[first].size(); ++i) {//first가 먹을 수 있는 음식 수
		int food = canEat[first][i];//음식을 선택할때 가장 많은 사람이 먹을 수 있는 음식 부터 시도.
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