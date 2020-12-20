#include<iostream>
#include<assert.h>

using namespace std;
int ratio(long long a, long long b) {
    return static_cast<int>(100.0 * b / a);
}
int neededGames(long long totalPlay, long long win)
{
    long long play = 0;
    long long hi = 20'0000'0000;
    long long lo = 0;
    if (ratio(totalPlay + hi, win + hi) <= ratio(totalPlay, win))
        return -1;
    
    /*���� 100�� �� �ʿ� ���� 1%�� �ö󰡸� �׸��ΰ� ������
    for (int iter = 0; iter < 100; ++iter)
    {
        play = (lo + hi) / 2;
        if (ratio(totalPlay + play, win + play) > ratio(totalPlay, win))
            hi = play;
        else
            lo = play;
    }
    return hi;
    */
    while (lo + 1 < hi) {
        long long mid = (lo + hi) / 2;
        if (ratio(totalPlay, win) == ratio(totalPlay + mid, win + mid))//�Ҽ��� �Ʒ��� ���� ��� ������ ������ �·��� 1%�� �ȿ����� ���� ������ ó���ȴ�.
            lo = mid;
        else
            hi = mid;
    }
    return hi;
}
int neededGames2(int totalPlay, int win)
{
    return 0;
}
int main() {
    int cases;
    cin >> cases;
    for (int cc = 0; cc < cases; ++cc) {
        int n, m;
        cin >> n >> m;
        int a = neededGames(n, m);
     //   int b = neededGames2(n, m);
     //   assert(a == b);
        cout << a << endl;
    }
}
