#define _CRT_SECURE_NO_WARNINGS
#define MAX(a,b) ((a)>(b)?(a):(b))
#include<stdio.h>

char c[2][1002];
int CACHE[1001][1002];

int main() {
	scanf("%s", (char*)&c[0] + 1 );
	scanf("%s", (char*)&c[1] + 1);

	int i, j;
	for (i = 1; c[0][i]; ++i) {
		for (j = 1; c[1][j]; ++j) {
			CACHE[i][j] = MAX(CACHE[i - 1][j], CACHE[i][j - 1]);
			if (c[0][i] == c[1][j]) CACHE[i][j] = CACHE[i - 1][j - 1] + 1;
		}
	}
	printf("%d\n", CACHE[i - 1][j - 1]);

}