#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>

int N, M;
int data[14][14];

const int Type[2][2][2] = {
	{ { 0,0 },{ 0,1 } },
	{ { 0,0 },{ 1,0 } },
};


bool set(int y, int x, int type, int delta) {
	bool ok = true;
	for (int i = 0; i < 2; ++i) {
		const int ny = y + Type[type][i][0];
		const int nx = x + Type[type][i][1];

		if (ny < 0 || ny >= M || nx < 0 || nx >= N)
			ok = false;
		else if ((data[ny][nx] += delta)  > 1)
			ok = false;
		//printf("set %d %d %d %d \n", N, ny, nx, data[ny][nx]);
	}
	return ok;
}

int cover() {
	int y = -1, x = -1;
	for (int i = 0; i < M; ++i) {
		for (int j = 0; j < N; ++j) {
			if (data[i][j] == 0) {
				y = i;
				x = j;
				break;
			}
		}
		if (y != -1) break;
	}
	if (y == -1) return 1; // 모든칸을 채웠을때
						   //printf("%d %d \n ", y, x);
	int ret = 0;
	for (int type = 0; type < 2; ++type) {
		if (set(y, x, type, 1))
			ret += cover();
		set(y, x, type, -1);
	}
	return ret % 9901;
}

int cache[14*14 + 5][1 << 14];
int dp() {
	cache[0][0] = 1;


	for (int j = 0; j < M; ++j) {
		for (int i = 0; i < N; ++i) {
			for (int k = 0; k < (1 << N); ++k) {
				int cidx = i + j * N;
				
				cache[cidx][k] %= 9901;

				if (k & 1) cache[cidx + 1][k >> 1] += cache[cidx][k];
				else {
					// 가로 배치
					if ((k & 3) == 0 && i < N - 1) {
						cache[cidx + 1][(k >> 1) + 1] += cache[cidx][k];
					}
					// 세로 배치
					if ((k & 1) == 0 && j < M - 1)
						cache[cidx + 1][(k >> 1) + (1 << (N-1))] += cache[cidx][k];
				}

			}
		}
	}

	return cache[N*M][0] % 9901;

}

int main() {
	scanf("%d%d", &N, &M);

	//printf("%d\n", cover()); // exhaustive search
	printf("%d\n", dp()); // dp

	/*
	for (int i = 0; i <= N*M; ++i) {
		for (int k = 0; k < (1 << N); ++k) {
			printf("%d %d : %d\n", i, k, cache[i][k]);
		}
	}
	*/
	return 0;
}