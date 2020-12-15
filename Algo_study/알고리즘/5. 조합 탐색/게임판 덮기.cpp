#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

vector<vector<pair<int, int>>> rotations;
int blockSize;

vector<string> rotate(const vector<string>& arr)
{
	vector<string> ret(arr[0].size(), string(arr.size(), ' '));
	for (int i = 0; i < arr.size(); ++i)
		for (int j = 0; j < arr[0].size(); ++j)
			ret[j][arr.size() - i - 1] = arr[i][j];
	return ret;
}
void generateRotations(vector<string> block)
{
	rotations.clear();
	rotations.resize(4);
	for (int rot = 0; rot < 4; ++rot) {
		int originY = -1, originX = -1;
		for(int i=0;i<block.size();++i)
			for(int j=0;j<block[i].size();++j)
				if (block[i][j] == '#') {
					if (originY == -1) {
						originY = i;
						originX = j;
					}
					rotations[rot].push_back(make_pair(i - originY, j - originX));
				}
		block = rotate(block);
	}
	sort(rotations.begin(), rotations.end());
	rotations.erase(unique(rotations.begin(), rotations.end()), rotations.end());

	blockSize = rotations[0].size();
}

int boardH, boardW;
vector<string> board;

int covered[10][10];
int best;
bool set(int y, int x, const vector<pair<int, int>>& block, int delta) {
	//블록을 놓을 때 이미 놓인 블록이나 검츤 칸과 겹치면 거짓을,아니면 참을 반환한다.
}

void search(int placed) {
	int y = -1, x = -1;
	for (int i = 0; i < boardH; ++i) {
		for(int j=0;j<boardW;++j)
			if (covered[i][j] == 0) {
				y = i;
				x = j;
				break;
			}
		if (y != -1)break;
	}

	if (y == -1) {
		best = max(best, placed);
		return;
	}

	for (int i = 0; i < rotations.size(); ++i) {
		if (set(y, x, rotations[i], 1))
			// 여기에 가지치기를 추가해보자; 남은 빈 칸의 수를 블록의 크기로 나눈다-> 실제 놓을 수 있는 블록의 수 -> 답의 상한선
			search(placed + 1);
		set(y, x, rotations[i], -1);
	}
	covered[y][x] = 1;
	search(placed);
	covered[y][x] = 0;

}

int solve()
{
	best = 0;
	for (int i = 0; i < boardH; ++i)
		for (int j = 0; j < boardW; ++j)
			covered[i][j] = (board[i][j] == '#' ? 1 : 0);
	search(0);
	return best;
}
int main()
{

}