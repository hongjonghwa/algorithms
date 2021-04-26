#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int N, M;
int x[1025][1025];

int main() {
	scanf("%d%d", &N, &M);
	int p,q,s,t;
	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= N; ++j) {
			scanf("%d", &p);
			x[i][j] = x[i][j - 1] + x[i - 1][j] - x[i - 1][j - 1] + p;
		}
	}
	/*
	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= N; ++j)
			printf("%d ", x[i][j]);
		printf("\n");
	}
	*/
	for (int i = 1; i <= M; ++i) {
		scanf("%d%d%d%d", &p, &q, &s, &t);
		printf("%d\n", x[s][t] - x[p - 1][t] - x[s][q - 1] + x[p - 1][q - 1]);

	}
}