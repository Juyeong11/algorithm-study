#include<iostream>
#include<algorithm>

#include<string>

#include<vector>
#include<cmath>

using namespace std;

int solve(string i, string f);


void normalize(vector<int>& c);
vector<int> multiply(const vector<int>& a, const vector<int>& b);
void addTo(vector<int>&, vector<int>&, int);
void subFrom(vector<int>&, const vector<int>&);

vector<int> karatsuba(const vector<int>& a, const vector<int>& b);

int main()
{
	string idol("MFMFMFFFMMMFMF");
	string fan("MMFFFFFMFFFMFFFFFFMFFFMFFFFMFMMFFFFFFF");
	
	int N = idol.size(), M = fan.size();
	vector<int> a(N);
	vector<int> b(M);
	for (int i = 0; i < N; ++i) a[i] = (idol[i] == 'M');
	
	for (int j = 0; j < M; ++j) b[j] = (fan[j] == 'M');
	

	vector<int> c = karatsuba(a, b);
	int ret = 0;

	for (int i = N -1 ; i < M; ++i)
		if (c[i] == 0)
			ret++;

	cout << ret << endl;
}

//모두 탐색
int solve(string i, string f)
{
	int ret = 0;
	for (int j = 0; j <= f.size() - i.size(); ++j)
	{
		bool t = true;
		for (int k = 0; k < i.size(); ++k)
		{
			int a = j + k;

			if (i[k] == 'M' && f[a] == 'M')
				t = false;
		}
		if (t)
			++ret;
		t = true;
	}

	return ret;
}


void normalize(vector<int>& c)
{
	c.push_back(0);
// *************** 이 문제에서는 자리 올림이 필요가 없다.
	for (int i = 0; i < c.size(); ++i)
	{
		if (c[i] < 0)
		{
			int borrow = (abs(c[i]) + 9) / 10;
			//c[i + 1] -= borrow;
			c[i] += borrow * 10;
		}
		else
		{
			//c[i + 1] += c[i] / 10;
			c[i] = c[i] % 10;
		}
	}
	
	while (c.size() > 1 && c.back() == 0) c.pop_back();


}
vector<int> multiply(const vector<int>& a, const vector<int>& b)
{
	if (a.size() < b.size())
		return multiply(b, a);
	vector<int> c(a.size() + b.size() + 1, 0);

	for (int i = 0; i < a.size(); ++i)
		for (int j = 0; j < b.size(); ++j)
		{

			c[i + j] += a[i] * b[j];
		}

	normalize(c);


	return c;
}

//a = a + b*10^k
void addTo(vector<int>& a, vector<int>& b, int k)
{
	k = k - 1;
	int s = max(a.size(), b.size());

	vector<int> c(s + k + 1, 0);
	vector<int> p(b.size() + k + 1, 0);

	for (int i = 1; i <= b.size(); ++i)
	{
		p[p.size() - i] = b[b.size() - i];
	}
	b = p;

	if (a.size() > b.size())
	{
		for (int i = 0; i < a.size(); ++i)
		{
			if (i < b.size())
				c[i] = a[i] + b[i];
			else
				c[i] = a[i];
		}
	}
	else
	{
		for (int i = 0; i < b.size(); ++i)
		{
			if (i < a.size())
				c[i] = a[i] + b[i];
			else
				c[i] = b[i];
		}
	}




	normalize(c);

	a = c;
}

// a>=b 무조건! a-=b
void subFrom(vector<int>& a, const vector<int>& b)
{

	vector<int> c(a.size(), 0);

	for (int i = 0; i < c.size(); ++i)
	{
		if (i < b.size())
			c[i] = a[i] - b[i];
		else
			c[i] = a[i];

	}
	normalize(c);

	a = c;
}
//z2 = a1*b1;
//z0 = a0*b0;
//z1 = (a0 + a1) * (b0 + b1) - z0 -z2;
vector<int> karatsuba(const vector<int>& a, const vector<int>& b)
{
	int an = a.size(), bn = b.size();

	if (an < bn) return karatsuba(b, a);

	if (an == 0 || bn == 0) return vector<int>();


	if (an <= 10) return multiply(a, b);

	int half = an / 2;

	vector<int> a0(a.begin(), a.begin() + half);
	vector<int> a1(a.begin() + half, a.end());
	vector<int> b0(b.begin(), b.begin() + min<int>(b.size(), half));
	vector<int> b1(b.begin() + min<int>(b.size(), half), b.end());

	vector<int> z2 = karatsuba(a1, b1);
	vector<int> z0 = karatsuba(a0, b0);


	addTo(a0, a1, 0); addTo(b0, b1, 0);

	vector<int> z1 = karatsuba(a0, b0);

	subFrom(z1, z0);
	subFrom(z1, z2);


	vector<int> ret;


	addTo(ret, z0, 0);
	addTo(ret, z1, half);
	addTo(ret, z2, half + half);



	return ret;
}