/*
카메라를 설치할 수 있는 위치가 정해져 있고, 카메라 갯수가 있을 때 카메라 최소 간격을 가장 크게 하는 위치
->카메라 사이 간격별로 정렬?ㄴㄴ
optimize(locations, cameras)= 카메라를 설치할 수 있는 위치locations와 카메라의 수cameras가 주어질 때, 카메라간 최소 간격의 (최대치)를 반환

decistion(locations,cameras,gap)= 카메라를 설치할 수 있는 위치 locations와 카메라의 수 cameras가 주어질 때, 이들을 적절히 배치해 모든 카메라의 칸격이 gap이상이 되도록 하는 방법이 있는가


*/
#include<vector>
using namespace std;
bool decision(const vector<double>& location, int cameras, double gap)
{
	double limit = -1;
	int installed = 0;
	for (int i = 0; i < location.size(); ++i) {
		if (limit <= location[i]) {
			++installed;
			limit = location[i] + gap;
		}
	}
	return installed >= cameras;
}
double optimize(const vector<double>& location, int cameras)
{
	double lo = 0, hi = 241;
	for (int it = 0; it < 100; ++it) {
		double mid = (lo + hi) / 2.0;
		if (decision(location, cameras, mid))
			lo = mid;
		else
			hi = mid;
	}
	return lo;
}