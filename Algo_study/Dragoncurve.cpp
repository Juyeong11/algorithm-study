#include<iostream>
#include<string>


using namespace std;

/*
void dragonCur(string& cur);


//�巡�� Ŀ���� ���� n, p��° ���ں��� I���ڸ��� ���
//p[1,1,000,000,000], l[1,50]
int main()
{
	string Cur("fx+yf");
	//Cur.replace(Cur.begin(), Cur.begin()+1, "dfg");
	for (int i = 0; i < 5; ++i)
	{
		dragonCur(Cur);
		cout << Cur << endl;
		cout << endl;
	}
	
//	dragonCur(Cur);
}

//replace �� �ݺ����� ���� ����
void dragonCur(string& cur)
{
	string::iterator it = cur.begin();

	while(it != cur.end())
	{
		char head = *it;
		
		if (head == 'x')
		{
			cur.replace(it-1, it + 1, "fx+yf");			
			it += 1;
		}
		if (head == 'y')
		{
			//string::iterator tmp = it;
			cur.replace(it, it+1, "fx-y");
			it += 1;
		
		}

		++it;	
		//cout << head;
	}
	cout << endl;

}

*/
void dragonCur(const string& seed, int generations);

const string X("x+yf");
const string Y("fx-y");

int main()
{
	dragonCur("fx", 3);
}

void dragonCur(const string& seed,int generations)
{
	if (generations == 0)
	{
		cout << seed;
		return;
	}
	for (int i = 0; i < seed.size(); ++i)
	{
		if (seed[i] == 'x') dragonCur(X, generations - 1);
		else if (seed[i] == 'y') dragonCur(Y, generations - 1);
		else
			cout << seed[i];
	}
}