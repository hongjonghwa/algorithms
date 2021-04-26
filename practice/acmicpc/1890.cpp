#define _CRT_SECURE_NO_WARNINGS
#define MAX(a,b) ((a)>(b)?(a):(b))
#include <stdio.h>

int N;
int x[100][100];
long long int cache[110][110];
int main() {
	scanf("%d", &N);
	for (int i = 0 ; i < N ; ++i)
		for (int j = 0 ; j < N ; ++j)
			scanf("%d", &x[i][j]);

	for (int i = N - 1;i >= 0 ; --i) {
		for (int j = N - 1; j >= 0; --j) {
			if (i == N - 1 && j == N - 1) cache[i][j] = 1;
			else cache[i][j] = cache[i + x[i][j]][j] + cache[i][j + x[i][j]];
		}
	}
	printf("%lld\n", cache[0][0]);

}