#include<iostream>
#include<string>

using namespace std;

string quad(string::iterator& it)
{
	char head = *it;
	++it;
	if (head == 'b' || head == 'w')
		return string(1, head);

	string uL = quad(it);
	string uR = quad(it);
	string dL = quad(it);
	string dR = quad(it);
	

	return "X"  + dL + dR + uL + uR;
}
int main()
{
	string test;
	cin >> test;

	string::iterator iter = test.begin();
	cout << quad(iter);

	
}