#include<iostream>
#include<assert.h>
#include<string>
using namespace std;



int H, W;
bool map[20][20];
int yblock[4][2] = {
	{1,1},
	{0,1},
	{1,1},
	{0,1},
};
int xblock[4][2] = {
	{0,1},
	{1,1},
	{-1,0},
	{1,0},
};

void printMap()
{
	for (int i = 0; i < H; ++i)
	{
		for (int j = 0; j < W; ++j)
			cout << map[i][j] << " ";
		cout << endl;
	}
	cout << endl;
}

int coverMap()
{
	int x = -1, y = -1;
	for (int i = 0; i < H; ++i)
		for (int j = 0; j < W; ++j)
			if (map[i][j])
			{
				y = i;
				x = j;
				goto EXIT;
			}
	EXIT:
	if (x == -1) return 1;

	int ret = 0;
	for (int i = 0; i < 4; ++i)
	{
		if (map[y][x] && map[y + yblock[i][0]][x + xblock[i][0]] && map[y + yblock[i][1]][x + xblock[i][1]])
		{
			map[y][x] = map[y + yblock[i][0]][x + xblock[i][0]] = map[y + yblock[i][1]][x + xblock[i][1]] = false;
			printMap();

			ret += coverMap();
			map[y][x] = map[y + yblock[i][0]][x + xblock[i][0]] = map[y + yblock[i][1]][x + xblock[i][1]] = true;

		}
	}
	return ret;
}
int main()
{
	int testCase;
	cin >> testCase;
	while (testCase--)
	{
		memset(map, 0, sizeof(map));
		cin >> H >> W;
		assert(1 <= H && W <= 20);
		for (int i = 0; i < H; ++i)
		{
			string line;
			cin >> line;
			assert(line.length() == W);
			for (int j = 0; j < W; ++j)
				if (line[j] == '.') map[i][j] = true;
		}
		cout << coverMap() << endl;
		printMap();
	}
}