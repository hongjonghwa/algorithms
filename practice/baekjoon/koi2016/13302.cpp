#define INF 987654321
#define MAX(a,b) ((a)>(b)?(a):(b))
#define MIN(a,b) ((a)<(b)?(a):(b))
#include<stdio.h>
#include<string.h>

int N,M;
int x[101];
int cache[101][40];

int dp(int day, int j){
	//printf("called %d %d %d  \n", day, j, cache[day][j]);
	if (day < 0 || j < 0 || j>= 40) return INF;
	if (cache[day][j] >= 0 ) return cache[day][j];
	int &ret = cache[day][j];

	if (x[day]) return ret = dp(day-1,j);
	ret = INF;
	ret = MIN(ret, dp(day-1, j) + 10000);
	ret = MIN(ret, dp(day-1, j+3));

	ret = MIN(ret, dp(day-1, j-1) + 25000);
	ret = MIN(ret, dp(day-2, j-1) + 25000);
	ret = MIN(ret, dp(day-3, j-1) + 25000);

	ret = MIN(ret, dp(day-1, j-2) + 37000);
	ret = MIN(ret, dp(day-2, j-2) + 37000);
	ret = MIN(ret, dp(day-3, j-2) + 37000);
	ret = MIN(ret, dp(day-4, j-2) + 37000);
	ret = MIN(ret, dp(day-5, j-2) + 37000);

	//printf(" %d %d %d \n", day, j, ret);
	return ret;
}
int main(){
	scanf("%d%d", &N, &M);
	for (int i = 0; i< M ; ++i){
		int t;
		scanf("%d", &t);
		x[t] = 1;
	}
	//printf (" N : %d M : %d \n", N, M);
	memset(cache, -1, sizeof(cache));
	cache[0][0] = 0;
	int ans = INF;
	for (int j = 0; j < 20 ; ++j){
		ans = MIN(ans, dp(N,j));
		//printf("  %d \n", dp(0,j));
	}
	printf("%d \n", ans);
}
