#include<iostream>
#include<cstring>
#include<vector>
#include<algorithm>

using namespace std;

int Lis(int start);
int count(int start);
void reconstruct(int start, int skip, vector<int>& lis);

int n = 8, k = 6; // 원소의 수, 순위
int T[8] = { 5,1,6,4,3,2,8,7 };

int cache[501];
int cacheCnt[501];
int MAX = 2000000000;
int main()
{
	vector<int> t;
	memset(cache, -1, sizeof(cache));
	memset(cacheCnt, -1, sizeof(cache));

	reconstruct(-1, 2, t);
	
	for (int i : t)
		cout << i << endl;
}

//start에서 시작하는 증가부분수열 중 최대길이 반환
int Lis(int start)
{
	int& ret = cache[start + 1];

	if (ret != -1) return ret;
	ret = 1;
	for (int i = start + 1; i < n; ++i)
		if (start == -1 || T[start] < T[i])
			ret = max(ret, Lis(i) + 1);

	return ret;
}

//start에서 시작하는 최대 증가 부분 수열의 수를 반환
int count(int start)
{
	if (Lis(start) == 1) return 1;


	int& ret = cacheCnt[start + 1];
	if (ret != -1) return ret;
	ret = 0;
	for (int next = start + 1; next < n; ++next)
	{
		if ((start == -1 || T[start] < T[next]) && Lis(start) == Lis(next) + 1)
			ret = min<long long>(MAX, (long long)ret + count(next));
	}
	return ret;
}

void reconstruct(int start, int skip, vector<int>& lis)
{
	//으아!
	if (start != -1) lis.push_back(T[start]);

	vector<pair<int, int>> followers;

	for (int next = start + 1; next < n; ++next)
		if ((start == -1 || T[start] < T[next]) && Lis(start) == Lis(next) + 1)
			followers.push_back(make_pair(T[next], next));

	sort(followers.begin(), followers.end());

	for (int i = 0; i < followers.size(); ++i)
	{
		int idx = followers[i].second;
		int cnt = count(idx);
		if (cnt <= skip)
			skip -= cnt;
		else
		{
			reconstruct(idx, skip, lis);
			break;
		}
	}
}