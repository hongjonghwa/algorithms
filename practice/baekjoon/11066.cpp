#define _CRT_SECURE_NO_WARNINGS
#define MIN(a,b) ( (a)<(b) ? (a) : (b) )
#define INF 987654321
#include<stdio.h>

int T, N;
int x[501], psum[501];
int cost[501][501];

int main() {
	scanf("%d", &T);
	for (int testcase = 1; testcase <= T; ++testcase) {
		scanf("%d", &N);
		for (int i = 1; i <= N; ++i){
			scanf("%d", &x[i]);
			psum[i] = psum[i - 1] + x[i];
		}

		for (int i = 1; i <= N - 1; ++i)
			cost[i][i+1] = x[i] + x[i+1];

		for (int k = 2 ; k < N ; ++k){
			for (int i = 1; i <= N - k; ++i) {
				int lo = i, hi = i + k;
				cost[lo][hi] = INF;
				for (int j = lo; j < hi; ++j) {
					cost[lo][hi] = MIN(cost[lo][hi],
						cost[i][j] + cost[j + 1][hi] + psum[hi] - psum[lo - 1]);
				}
			}
		}
		printf("%d\n", cost[1][N]);
		/*
		for (int i = 1; i <= N; ++i) {
			for (int j = 1; j <= N; ++j)
				printf("%d ", cost[i][j]);
			printf("\n");
		}
		*/
	}
	return 0;
}