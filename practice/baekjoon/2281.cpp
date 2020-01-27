#define _CRT_SECURE_NO_WARNINGS
#define INF 987654321
#define MAX(a,b) ( (a)>(b) ? (a) : (b) )
#define MIN(a,b) ( (a)<(b) ? (a) : (b) )
#include <stdio.h>

int N, M;
int x[1001];
int cache[1001];

int dp(int start) {
	if (cache[start] != -1) return cache[start];
	int &ret = cache[start];

	ret = INF;
	int filled = -1;
	int i;
	for (i = start; i <= N; ++i) {
		filled++;
		filled += x[i];

		if (filled > M) break;

		int t = (M - filled)*(M - filled) + dp(i + 1);
		ret = MIN(ret, t);
	}
	if (i > N) ret = 0;

	return ret;

}

int main() {
	scanf("%d%d", &N, &M);
	for (int i = 1; i <= N; ++i)
		scanf("%d", &x[i]);

	for (int i = 1; i <= N; ++i)
		cache[i] = -1;
	cache[N + 1] = 0;

	printf("%d\n", dp(1));
	/*
	for (int i = 1; i <= N+1; ++i)
		printf("%d ", cache[i]);
		*/

	return 0;
}