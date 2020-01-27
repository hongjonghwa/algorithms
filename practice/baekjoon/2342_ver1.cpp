#define _CRT_SECURE_NO_WARNINGS
#define INF 987654321
#define MIN(a,b) ((a)<(b)?(a):(b))
#define MAX(a,b) ((a)>(b)?(a):(b))
#define ABS(a) ( (a) < 0 ? -(a) : (a) )
#include<stdio.h>
#include<assert.h>
int x[100002];
int cache[100002][5][5];

int N;

inline int COST(int from, int to) {
	assert(to != 0);
	if (from == to) return 1;
	if (from == 0) return 2;
	if (ABS(to - from) == 2) return 4;
	return 3;
}

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
		// steping
		for (int l = 0; l <= 4; ++l){
			for (int r = 0; r <= 4; ++r) {
				// left step
				cache[i][to][r] = MIN(cache[i][to][r], cache[i - 1][l][r] + COST(l, to));
				// right step
				cache[i][l][to] = MIN(cache[i][l][to], cache[i - 1][l][r] + COST(r, to));
				// two feet impossible
			}
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