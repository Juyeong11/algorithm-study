/*
�̺й�
- �־��� ���� ������ � �Լ��� ���� 0�� �Ǵ� ������ ��ġ������ ã�Ƴ��� ��� (�߰��� ������ ����ϴٰ� ��������)
- ��ǥ������ ���ݾ� �ٿ������鼭 ���� ã��

double f(double x);

double bisection(double lo, double hi)
{
	if (f(lo) > 0)
		swap(lo, hi);
	while (fabs(hi - lo) > 2e-7) { ���� ���� ������ �߿�-> ���ݾ� �ٿ����鼭 ã�� ������ hi�� lo�� ����� ����� ���� ������ ���� ��ȯ-> ���� ��� ������ ������ ����
		double mid = (lo + hi) / 2;
		double fmid = f(mid);
		if (fmid <= 0)
			lo = mid;
		else
			hi = mid;
	}
	return(lo + hi) / 2;
}
void infinte()//�� �� ������ ������Ʈ�� ������ ��Ʈ�� �����ϰ� ������ �Ȱ��� ������ ���� ���� ����
{
	double lo = 123456123456.1234588263046875;
	double hi = 123456123456.1234741210937500;
	while (fabs(hi - lo) > 2e-7)
		hi = (lo + hi) / 2.0;
}
-> ��ȸ�� Ƚ�� ��ŭ �ݺ����ִ� ����� ����ϸ� ū ���ڸ� �ٷ�� ��쿡�� ���� ������ ���� �� �ִ�.

M������ �ɷ� ��� ���� �ݾ��� �ٰ��� ���� �� �޿� �ּ� �󸶾� ���ƾ� �ϳ�?(�̺й�)
#include<vector>
using namespace std;

double balance(double amount, int duration, double rates, double monthlyPayment)
{
	double balance = amount;
	for (int i = 0; i < duration; ++i)
	{
		balance *= (1.0 + (rates / 12.0) / 100.0);
		balance -= monthlyPayment;
	}
	return balance;
}
double payment(double amount, int duration, double rates)
{
	double lo = 0;
	double hi = amount * (1.0 + (rates / 12) / 100.0);
	for (int iter = 0; iter < 100; ++iter)
	{
		double mid = (lo + hi) / 2.0;
		if (balance(amount, duration, rates, mid) <= 0)
			hi = mid;
		else
			lo = mid;
	}
	return hi;
}

��� �˻�
�Լ����� �ش����� 1�� �ְ�, �ش��� ������ ������, �������� ������ �Ҷ� ��밡�� �� ���(�翬�� �������� �ؼ������ε� �����Ѵ�)
->�ִ����� �����ϴ� ������ �˰� �־�� �Ѵ� (lo, hi)
 ������ ũ�Ⱑ �� �ݺ����� 2/3���� �پ� ��� ������ nȸ �ݺ��ϰ� ���� ������ ���̴� hi-lo * (2/3)^n �� �ȴ�.

double f(double x);//�ִ�ġ�� ã�� �Լ�

double ternary(double lo, double hi){
	for(int iter =0; iter<100;iter++)
		double a = (2*lo + hi)/3.0;//1/3����
		double b = (lo + 2*hi)/3.0;//2/3����0
		if(f(a)>f(b))
			hi = b;
		else
			lo = a;
	return (lo+hi)/2.0;
}

ö�� 2�� ���
���� �Լ��� ���� �Լ�p485
double t;
vector<double> runSpeed, cycleSpeed;

double time(int i, double run)
{
	double cycle = t - run;
	return run / runSpeed[i] + cycle / cycleSpeed[i];
}

double diff(double r) {
	int n = runSpeed.size();
	double cheater = time(n - 1, r);
	double others = time(0, r);
	for (int i = 1; i < n - 1; ++i)
		others = min(others, time(i, r));
	return others - cheater;
}

double maxDifference()
{
	double lo = 0, hi = t;
	for (int it = 0; it < 100; ++it)
	{
		double aab = (2 * lo + hi) / 3;
		double abb = (lo + 2 * hi) / 3;
		if (diff(aab) > diff(abb))
			hi = abb;
		else
			lo = aab;
	}
	return (lo + hi) / 2;
}
*/
