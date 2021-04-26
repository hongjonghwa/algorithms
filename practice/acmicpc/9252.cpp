#define _CRT_SECURE_NO_WARNINGS
#define MAX(a,b) ((a)>(b)?(a):(b))
#include<stdio.h>
#include"assert.h"

char c[2][1002];
int CACHE[1001][1001];
void reverse(int i, int j) {
	//printf("%d %d\n", i, j);
	assert(CACHE[i][j] > 0);
	if (CACHE[i][j] == CACHE[i - 1][j]) reverse(i - 1, j);
	else if (CACHE[i][j] == CACHE[i][j - 1]) reverse(i, j - 1);
	else {
		if (CACHE[i][j] > 1) reverse(i - 1, j - 1);
		//printf("%c", CACHE[i][j]);
		printf("%c", c[0][i]);
	}
}
int main() {
	scanf("%s", (char*)&c[0] + 1);
	scanf("%s", (char*)&c[1] + 1);

	int i, j;
	for (i = 1; c[0][i]; ++i) {
		for (j = 1; c[1][j]; ++j) {
			CACHE[i][j] = MAX(CACHE[i - 1][j], CACHE[i][j - 1]);
			if (c[0][i] == c[1][j]) { 
				CACHE[i][j] = CACHE[i - 1][j - 1] + 1; 
				//LASTMATCH[i][j] = PP(i, j);
			}
		}
	}
	printf("%d\n", CACHE[i - 1][j - 1]);
	reverse(i - 1, j - 1);
	printf("\n");
}