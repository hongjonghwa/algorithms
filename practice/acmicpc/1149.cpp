#define _CRT_SECURE_NO_WARNINGS
#define MIN(a,b) ( (a)<(b) ? (a) : (b) )
#define INF 987654321
#include<stdio.h>

int N;
//int A[1000][3];
int A[3];
//int CACHE[1000][3];
int CACHE[2][3]; // sliding window

int main() {
	scanf("%d", &N);

	/* 
	// 중간값 배열에 저장
	for (int i = 1; i < N; ++i) {
		CACHE[i][0] = A[i][0] + MIN(CACHE[i - 1][1], CACHE[i - 1][2]);
		CACHE[i][1] = A[i][1] + MIN(CACHE[i - 1][0], CACHE[i - 1][2]);
		CACHE[i][2] = A[i][2] + MIN(CACHE[i - 1][0], CACHE[i - 1][1]);
	}
	int ret = INF;
	ret = MIN(ret, CACHE[N - 1][0]);
	ret = MIN(ret, CACHE[N - 1][1]);
	ret = MIN(ret, CACHE[N - 1][2]);

	printf("%d\n", ret);
	*/

	// Sliding Window
	int cur, prev;
	for (int i = 1; i <= N; ++i) {
		for (int j = 0; j < 3; ++j)
			scanf("%d", &A[j]);

		cur = i % 2, prev = (i - 1) % 2;
		CACHE[cur][0] = A[0] + MIN(CACHE[prev][1], CACHE[prev][2]);
		CACHE[cur][1] = A[1] + MIN(CACHE[prev][0], CACHE[prev][2]);
		CACHE[cur][2] = A[2] + MIN(CACHE[prev][0], CACHE[prev][1]);
	}
	int ret = INF;
	ret = MIN(ret, CACHE[cur][0]);
	ret = MIN(ret, CACHE[cur][1]);
	ret = MIN(ret, CACHE[cur][2]);

	printf("%d\n", ret);

	return 0;
}