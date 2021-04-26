#define _CRT_SECURE_NO_WARNINGS
#define MAX(a,b) ((a)>(b)?(a):(b))
#include<stdio.h>

char c[3][102];
int CACHE[101][101][101];

int TriMAX(int a, int b, int c) {
	int ret = MAX(a, b);
	return MAX(ret, c);
}

int main() {
	scanf("%s", (char*)&c[0] + 1);
	scanf("%s", (char*)&c[1] + 1);
	scanf("%s", (char*)&c[2] + 1);

	int i, j, k;
	for (i = 1; c[0][i]; ++i) {
		for (j = 1; c[1][j]; ++j) {
			for (k = 1; c[2][k]; ++k) {
				//printf("%d %d %d\n", i, j, k);
				if (c[0][i] == c[1][j] && c[0][i] == c[2][k] ) CACHE[i][j][k] = CACHE[i - 1][j - 1][k - 1] + 1;
				else CACHE[i][j][k] = TriMAX(CACHE[i - 1][j][k], CACHE[i][j - 1][k], CACHE[i][j][k - 1]);
			}
		}
	}
	printf("%d\n", CACHE[i - 1][j - 1][k - 1]);

}