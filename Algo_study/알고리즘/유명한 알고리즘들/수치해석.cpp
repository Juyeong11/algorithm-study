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
*/
