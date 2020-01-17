#include<iostream>
#include<algorithm>

using namespace std;
int Quant(int from, int parts);

const int INF = 987654321;

int n[] = { 1,744,755,4,897,902,890,6,777 };
int pSum[101], pSqsum[101];
int arrsize;

int s;//사용할 숫자수

int cache[101][11];
int main()
{
	memset(cache, -1, sizeof(cache));

	s = 3;

	arrsize = sizeof(n) / sizeof(int);
	sort(n, n + arrsize);
	pSum[0] = n[0];
	pSqsum[0] = n[0] * n[0];
	for (int i = 1; i < arrsize; ++i)
	{
		pSum[i] = pSum[i - 1] + n[i];
		pSqsum[i] = pSqsum[i - 1] + n[i] * n[i];
	}

	cout << Quant(0, 3);
}


int Average(int lo, int hi)
{
	int sum = pSum[hi] - (lo == 0 ? 0 : pSum[lo - 1]);
	int sqSum = pSqsum[hi] - (lo == 0 ? 0 : pSqsum[lo - 1]);

	int m = int(0.5 + (double)sum / (hi - lo + 1));

	int ret = sqSum - 2 * m * sum + m * m * (hi - lo + 1);
	return ret;
}

int Quant(int from, int parts)
{
	if (from == arrsize) return 0;

	if (parts == 0) return INF;

	int& ret = cache[from][parts];
	if (ret != -1) return ret;
	ret = INF;

	for (int partSize = 1; from + partSize <= arrsize; ++partSize)
		ret = min(ret, Average(from, from + partSize - 1) + Quant(from + partSize, parts - 1));

	return ret;
}