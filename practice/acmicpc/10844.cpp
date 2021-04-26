#define _CRT_SECURE_NO_WARNINGS
#define M 1000000000
#define SWAPT(T,a,b) { T tmp = a; a = b; b = tmp;}
#include<stdio.h>
#include<assert.h>

int N;
int CACHE[10][101];

int main() {
	scanf("%d", &N);
	//N = 100;
	for (int k = 0; k <= 9; ++k)
		CACHE[k][1] = 1;
	for (int i = 2; i <= N; ++i) {
		CACHE[0][i] = CACHE[1][i - 1];
		CACHE[9][i] = CACHE[8][i - 1];
		for (int k = 1; k <= 8; ++k)
			CACHE[k][i] = (CACHE[k + 1][i - 1] + CACHE[k - 1][i - 1]) % M;
	}
	//for (N = 1; N <= 100; N++) {
		int ret = 0;
		for (int k = 1; k <= 9; ++k) {
			ret += CACHE[k][N];
			if (ret >= M) ret -= M;
		}
		printf("%d\n", ret);
	//}
}