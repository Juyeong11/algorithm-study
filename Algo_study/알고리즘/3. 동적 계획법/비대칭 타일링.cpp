#include<iostream>
#include<cstring>


using namespace std;

int tiling(int width);
int asymmetric(int width);

const int Mod = 1000000007;
int cache[101];
int main()
{
	memset(cache, -1, sizeof(cache));
	
	cout<<asymmetric(92)<<endl;
}

int asymmetric(int width)
{
	if(width % 2 ==1) return (tiling(width) - tiling(width/2) + Mod) % Mod;
	
	int ret = tiling(width);
	ret = (ret - tiling(width/2) + Mod) % Mod;
	ret = (ret - tiling(width/2 - 1) + Mod) % Mod;
	
	return ret;
}
int tiling(int width)
{
	if(width <= 1) return 1;
	
	int& ret = cache[width];
	if(ret != -1) return ret;
	
	return ret = (tiling(width-2) + tiling(width - 1)) % Mod;
}