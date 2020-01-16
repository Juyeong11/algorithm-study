#include<iostream>

using namespace std;


int test_case = 0;

int student_Num = 0;
int friend_Num = 0;
int temp_arr[50] = {-1,};
bool areFriends[10][10] = {0};

int main()
{
	/* 입력부분
	cin>>test_case;
	
	for(int i=0;i<test_case;++i)
	{
		cin>>student_Num>>friend_Num;
		
		for(int& a:temp_arr)
			a = -1;
		for(int a=0;a<10;a++)
			for(int b=0;b<10;b++)
				areFriends[a][b]=0;
			
		for(int j=0;j<friend_Num*2;++j)
		{
			cin>>temp_arr[j];
		}
		
		for(int k=0;k<friend_Num*2;k+=2)
		{
			areFriends[temp_arr[k]][temp_arr[k]+1]= true;
		}
	}
	*/
	
	student_Num = 4; friend_Num = 6; int _temp_arr[50]={0,1,1,2,2,3,3,0,0,2,1,3,};
	
	for(int k=0;k<friend_Num*2;k+=2)
	{
		areFriends[_temp_arr[k]][_temp_arr[k+1]]= true;
	}
	for(int a=0;a<10;a++)
	{
		for(int b=0;b<10;b++)
			cout<<areFriends[a][b];
		cout<<endl;
	}
	
	
//출력
}
