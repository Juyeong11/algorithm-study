/*
이분법
- 주어진 범위 내에서 어떤 함수의 값이 0이 되는 지점을 수치적으로 찾아내는 기법 (중간값 정리랑 비슷하다고 생각하자)
- 목표값까지 절반씩 줄여나가면서 답을 찾음

double f(double x);

double bisection(double lo, double hi)
{
	if (f(lo) > 0)
		swap(lo, hi);
	while (fabs(hi - lo) > 2e-7) { 종료 판정 조건이 중요-> 절반씩 줄여가면서 찾기 때문에 hi와 lo가 충분히 가까워 지면 임의의 답을 반환-> 실제 답과 조금의 오차가 있음
		double mid = (lo + hi) / 2;
		double fmid = f(mid);
		if (fmid <= 0)
			lo = mid;
		else
			hi = mid;
	}
	return(lo + hi) / 2;
}
void infinte()//이 두 변수는 가수비트의 최하위 비트를 제외하고 완전히 똑같기 때문에 사이 값이 없다
{
	double lo = 123456123456.1234588263046875;
	double hi = 123456123456.1234741210937500;
	while (fabs(hi - lo) > 2e-7)
		hi = (lo + hi) / 2.0;
}
-> 정회진 횟수 만큼 반복해주는 방법을 사용하면 큰 숫자를 다루는 경우에도 답을 빠르게 구할 수 있다.

M개월에 걸려 모든 대출 금액을 다갚기 위해 한 달에 최소 얼마씩 갚아야 하나?(이분법)
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
