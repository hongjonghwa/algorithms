#define _CRT_SECURE_NO_WARNINGS
#define INF 987654321
#define MIN(a,b) ((a)<(b)?(a):(b))
#define MAX(a,b) ((a)>(b)?(a):(b))
#define ABS(a) ( (a) < 0 ? -(a) : (a) )
#include<stdio.h>
#include<assert.h>

int cost[5][5] = {
	{ 0, 2, 2, 2, 2 },
	{ 0, 1, 3, 4, 3 },
	{ 0, 3, 1, 3, 4 },
	{ 0, 4, 3, 1, 3 },
	{ 0, 3, 4, 3, 1 }
};

int x[100002];
int cache[100002][5][5];

int N;

/*
inline int COST(int from, int to) {
	assert(to != 0);
	if (from == to) return 1;
	if (from == 0) return 2;
	if (ABS(to - from) == 2) return 4;
	return 3;
}
*/

int main() {
	for (N = 1; N <= 100001; ++N) {
		scanf("%d", &x[N]);
		if (x[N] == 0) break;
	}
	N--;
	
	// init
	for (int l = 0; l <= 4; ++l)
		for (int r = 0; r <= 4; ++r)
			cache[0][l][r] = INF;
	cache[0][0][0] = 0;



	for (int i = 1; i <= N; ++i) {
		int &to = x[i];
		// init
		for (int l = 0; l <= 4; ++l)
			for (int r = 0; r <= 4; ++r)
				cache[i][l][r] = INF;
		// steping method 1 : 25개 가능성에서 모두 계산
		/*
		for (int l = 0; l <= 4; ++l){
			for (int r = 0; r <= 4; ++r) {
				// left step
				cache[i][to][r] = MIN(cache[i][to][r], cache[i - 1][l][r] + cost[l][to]);
				// right step
				cache[i][l][to] = MIN(cache[i][l][to], cache[i - 1][l][r] + cost[r][to]);
				// two feet impossible
			}
		}
		cache[i][to][to] = INF;
		*/
		
		// steping method 2 : 두 발 중 하나는 반드시 이전 x[i-1] 에 있음. 10개 가능성에서 계산
		int &prev = x[i - 1];
		for (int another = 0; another <= 4; ++another) {
			// (prev,another) 에서 왼발 이동
			cache[i][to][another] = MIN(cache[i][to][another] ,cache[i - 1][prev][another] + cost[prev][to]);
			// (prev,another) 에서 오른발 이동
			cache[i][prev][to] = MIN(cache[i][prev][to], cache[i - 1][prev][another] + cost[another][to]);
			// (another,prev) 에서 왼발 이동
			cache[i][to][prev] = MIN(cache[i][to][prev], cache[i - 1][another][prev] + cost[another][to]);
			// (another,prev) 에서 오른발 이동
			cache[i][another][to] = MIN(cache[i][another][to], cache[i - 1][another][prev] + cost[prev][to]);
		}
		cache[i][to][to] = INF;

	}

	/*
	for (int i = 0; i <= N; ++i) {
		for (int l = 0; l <= 4; ++l) {
			for (int r = 0; r <= 4; ++r){
				printf("%d ", cache[i][l][r]);
			}
		}
		printf("\n");
	}
	*/

	int ret = INF;
	for (int l = 0; l <= 4; ++l)
		for (int r = 0; r <= 4; ++r)
			if (cache[N][l][r] < ret)
				ret = cache[N][l][r];



	printf("%d ", ret);

	return 0;
}