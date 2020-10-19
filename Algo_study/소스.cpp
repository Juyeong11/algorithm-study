#include"config.h"
#include"graph.h"

int main()
{
	graph_create();
	vector<int> o = bfs(0);
	for (int a : o)
		cout << a << " ";
	return 0;
}



