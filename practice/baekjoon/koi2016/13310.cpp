#include<cstdio>
using namespace std;

int N, T;
struct Star{
	int x,y,dx,dy;
} star[30000];

int dist[501][501];

int main(){
	scanf("%d%d", &N, &T);
	for (int i = 0; i < N ; ++i)
		scanf("%d%d%d%d", &star[i].x, &star[i].y, &star[i].dx, &star[i].dy);



	return 0;
}
