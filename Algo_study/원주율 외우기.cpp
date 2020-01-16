//원주율 외우기

#include<iostream>
#include<string>
#include<algorithm>
#include<cstring>

using namespace std;

int memPi(int);

string N = "21053210534023153215321";

int INF = 999999999;

int cache[10002];
int main()
{
	memset(cache, -1, sizeof(cache));
	cout << memPi(0) << endl;
}

int classify(int a, int b)
{
	string M = N.substr(a, b - a + 1);

	if (M == string(M.size(), M[0]) == 1)
		return 1;

	bool progressive = true;
	for (int i = 0; i < M.size() - 1; ++i)
		if (M[i + 1] - M[i] != M[1] - M[0])
			progressive = false;

	if (progressive && abs(M[1] - M[0]) == 1)
		return 2;

	bool alternating = true;
	for (int i = 0; i < M.size(); ++i)
		if (M[i] != M[i % 2])
			alternating = false;

	if (alternating) return 4;
	if (progressive) return 5;

	return 10;
}



//3~5 자리씩 나눈다.
int memPi(int start)
{
	if (start == N.size()) return 0;

	int& ret = cache[start];

	if (ret != -1) return ret;
	ret = INF;
	for (int L = 3; L <= 5; ++L)
		if (start + L <= N.size() + L)
			ret = min(ret, memPi(start + L) + classify(start, start + L - 1));

	return ret;
}