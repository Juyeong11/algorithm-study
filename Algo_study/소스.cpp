#include <iostream>


int find_LIS(int);
int find_LDS(int);

using namespace std;

int _size=0;
int maxS;
int A[1000]= {-1,};

int main(int argc, char* argv[]) {
	

	cin>>_size;
	
	for(int i=0;i<_size;++i)
	{
		cin>>A[i];
	}
	
	cout<<find_LIS(0)<<endl;
	cout<<find_LDS(_size)<<endl;
	return 0;
}

int S_cache[1000];


int find_LIS(int index)
{
	int& ret = S_cache[index];
	if(ret != 0) return ret;
	ret=1;
	for(int next=index+1; next<_size ;++next)
		if(A[index]<A[next])
		{
			ret = max(ret,find_LIS(next)+1);
		}
	return ret;
			
}

int D_cache[1000];
int find_LDS(int index)
{
	int& _ret = D_cache[index];
	if(_ret != 0) return _ret;
	_ret=1;
	for(int next=index-1;next>=0;--next)
		if(A[index]>A[next])
		{
			_ret = max(_ret,find_LDS(next)+1);
		}
	return _ret;
}
