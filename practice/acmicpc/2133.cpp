#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>

int N;
int data[3][30];

const int Type[2][2][2] = {
	{ {0,0}, {0,1} },
	{ {0,0}, {1,0} },
};


bool set(int y, int x, int type, int delta) {
	bool ok = true;
	for (int i = 0; i < 2; ++i) {
		const int ny = y + Type[type][i][0];
		const int nx = x + Type[type][i][1];
		
		if (ny < 0 || ny >= 3 || nx < 0 || nx >= N)
			ok = false;
		else if ( ( data[ny][nx] += delta)  > 1)
			ok = false;
		//printf("set %d %d %d %d \n", N, ny, nx, data[ny][nx]);
	}
	return ok;
}

int cover() {
	int y = -1, x = -1;
	for (int i = 0; i < 3 ; ++i) {
		for (int j = 0; j < N; ++j) {
			if (data[i][j] == 0) {
				y = i;
				x = j;
				break;
			}
		}
		if (y != -1) break;
	}
	if (y == -1) return 1; // ¸ðµçÄ­À» Ã¤¿üÀ»¶§
	//printf("%d %d \n ", y, x);
	int ret = 0;
	for (int type = 0; type < 2; ++type) {
		if (set(y, x, type, 1))
			ret += cover();
		set(y, x, type, -1);
	}
	return ret;
}

int D[31][8];

int solv2() {
	D[0][7] = 1;
	for (int i = 1; i <= N; i++) {
		D[i][0] = D[i - 1][7];
		D[i][1] = D[i - 1][6];
		D[i][2] = D[i - 1][5];
		D[i][4] = D[i - 1][3];
		D[i][3] = D[i - 1][4] + D[i - 1][7];
		D[i][6] = D[i - 1][1] + D[i - 1][7];
		D[i][5] = D[i - 1][2];
		D[i][7] = D[i - 1][0] + D[i - 1][3] + D[i - 1][6];
	}
	return D[N][7];
}



int main() {
	scanf("%d", &N);

	//printf("%d\n", cover()); // exhaustive search
	printf("%d\n", solv2()); // dp
	return 0;
}