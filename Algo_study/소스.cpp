#include<iostream>
#include<vector>
#include<string>
#include<cmath>
using namespace std;

int isOperator(char a)
{
	if (a == '+' || a == '-')
		return 1;
	if (a == '/' || a == '*')
		return 2;
	if (a == '(' || a == ')')
		return 3;

	return 0;
}
int calculation(int a,int b, int oper)
{
	switch (oper)
	{
	case '+':
		return a+b;
	case '-':
		return a-b;
	case '*':
		return a*b;
	case '/':
		return a/b;
	default:
		break;
	}
}

int main()
{
	// �Է¹޾Ƽ� '1''2''3''+''1'2'3' �� 123'+'123���� �ٲ۴�
	string temp;
	cin >> temp;
	vector<int> numbers;
	for (int i = 0; i < temp.size(); ++i)
	{
		int lenghOfdigit = 0;
		while (temp[i + lenghOfdigit] != '\0' &&!isOperator(temp[i + lenghOfdigit])) {
			lenghOfdigit++;
		}
		int ret = 0;
		for (int digit = 0; digit < lenghOfdigit; ++digit)
		{
			ret += (temp[i + digit]-48) * pow(10, lenghOfdigit - digit-1);
		}
		if (ret)
		{
			numbers.push_back(ret);
			i += lenghOfdigit - 1;
		}
		else
			numbers.push_back(temp[i]);//�鸸 �����ش�
	}

	for (int i : numbers)
		cout << i;
	cout << endl;//�ߵǴ��� Ȯ�� ��

	//������ �켱������ �°� ����ǥ������� �ٲ۴�
	vector<int> sortNumbers;
	vector<int> Oper;
	for (int i = 0; i < numbers.size(); ++i)
	{
		if (isOperator(numbers[i]))
		{
			if (numbers[i] == '(')
			{
				continue;
			}
			if (numbers[i] == ')')
			{
				sortNumbers.push_back(Oper.back());
				Oper.pop_back();
				continue;
			}
				
			while (!Oper.empty() && isOperator(numbers[i]) >= isOperator(Oper.back()))
			{
				sortNumbers.push_back(Oper.back());
				Oper.pop_back();
				continue;
			}

			Oper.push_back(numbers[i]);
		}
		else
		{
			sortNumbers.push_back(numbers[i]);
		}

	}
	while (!Oper.empty()) { sortNumbers.push_back(Oper.back()); Oper.pop_back(); }


	//����ǥ����� ���
	vector<int> cal;
	for (int i = 0; i < sortNumbers.size(); ++i)
	{
		if (!isOperator(sortNumbers[i]))
		{
			cal.push_back(sortNumbers[i]);
		}
		else
		{
			int a1 = cal.back();
			cal.pop_back();
			int a2 = cal.back();
			cal.pop_back();
			
			cal.push_back(calculation(a1, a2, sortNumbers[i]));
		}
	}
	cout << cal[0];
}