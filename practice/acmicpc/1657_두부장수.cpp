#define _CRT_SECURE_NO_WARNINGS
#define MAX(a,b) ((a)>(b)?(a):(b))
#include<stdio.h>

int N, M;
char tf[14][14];
int ci[256];

int cost[5][5] = {
	{10, 8, 7, 5, 1},
	{ 8, 6, 4, 3, 1},
	{ 7, 4, 3, 2, 1},
	{ 5, 3, 2, 2, 1},
	{ 1, 1, 1, 1, 0} };

int cache[14*14 + 1][1 << 14];
int dp() {
	
	cache[0][0] = 0;
	//cache[0][other] 음수 초기화없이 0 초기화로 충분
	for (int j = 0; j < N; ++j) {
		for (int i = 0; i < M; ++i) {
			for (int k = 0; k < (1 << M); ++k) {
				int cidx = i + j * M;

				int &curIdx = cache[cidx][k];
				// 현재 위치 - cache[cidx][k];
				// 1) skip
				int &skipIdx = cache[cidx + 1][k >> 1];
				skipIdx = MAX(skipIdx, curIdx);

				// 2) 가로로 자름
				if ((k & 3) == 0 && i < M - 1) {
					int &horIdx = cache[cidx + 1][(k >> 1) + 1];
					int cc = cost[ ci[ tf[j][i] ] ][ ci[ tf[j][i+1] ] ];
					//printf("cost : %c %c %d \n", tf[j][i], tf[j][i + 1], cc);
					horIdx = MAX(horIdx, curIdx + cc);
				}
				// 3) 세로로 자름
				if ((k & 1) == 0 && j < N - 1){
					int &verIdx = cache[cidx + 1][(k >> 1) + (1 << (M - 1))];
					int cc = cost[ci[tf[j][i]]][ci[tf[j + 1][i]]];
					verIdx = MAX(verIdx, curIdx + cc);
				}
			}
		}
	}

	return cache[N*M][0];

}


int main() {
	ci['A'] = 0; ci['B'] = 1; ci['C'] = 2; ci['D'] = 3; ci['F'] = 4;

	scanf("%d%d", &N, &M);
	for (int i = 0; i < N; ++i) {
		scanf("%s", tf[i]);
	}
	/*
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			printf("%c", tf[i][j]);
		}
		printf("\n");
	}
	*/

	printf("%d\n", dp()); // dp

	/*
	for (int i = 0; i <= N*M; ++i) {
		for (int k = 0; k < (1 << M); ++k) {
			printf("%d %d : %d\n", i, k, cache[i][k]);
		}
	}
	*/

	return 0;
}