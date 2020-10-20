#include"config.h"
#include"graph.h"

#include<map>
#include<queue>
int main()
{
	graph_create();
	vector<int> o = bfs(1);
	for (int a : o)
		cout << a << " ";
	return 0;
}

int bfs(const vector<int>& perm)
{
	int n = perm.size();

	vector<int> sorted = perm;
	sort(sorted.begin(), sorted.end());

	queue<vector<int>> q;
	map<vector<int>, int> distance;
	return 1;
}

