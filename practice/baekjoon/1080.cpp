#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

int N, M;

char before[50][51];
char after[50][51];
bool diff[50][50];
bool flip(int y, int x) {
	if (y + 2 >= N || x + 2 >= M) return false;
	for (int i = y; i <= y + 2; ++i)
		for (int j = x; j <= x + 2; ++j)
			diff[i][j] = !diff[i][j];
	return true;
}
int solv() {
	int ret = 0;
	for (int i = 0; i < N ; ++i)
		for (int j = 0; j < M; ++j) {
			if (diff[i][j]) { // flip
				if (!flip(i, j))
					return -1;
				ret++;
			}
			
		}

	return ret;
}
int main() {
	scanf("%d%d", &N, &M);
	for(int i = 0; i < N ; ++i)
		scanf("%s", &before[i]);
	for (int i = 0; i < N; ++i)
		scanf("%s", &after[i]);

	for (int i = 0; i < N; ++i)
		for (int j = 0; j < M; ++j)
			diff[i][j] = (before[i][j] != after[i][j]);
	/*
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j)
			printf("%d", diff[i][j]);
		printf("\n");
	}
	*/
	printf("%d\n", solv());

	return 0;
}
