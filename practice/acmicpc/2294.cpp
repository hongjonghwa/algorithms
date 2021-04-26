#define _CRT_SECURE_NO_WARNINGS
#define INF 987654321
#define MIN(a,b) ( (a) < (b) ? (a) : (b) )
#include<stdio.h>
#include<assert.h>

int N, K;
int A[100];
int CACHE[10001];


// iterative
int coincnt2(int k) {
	for (int i = 0; i < N; ++i) {
		for (int j = A[i]; j <= k; ++j) {
			CACHE[j] = MIN( CACHE[j], CACHE[j - A[i]] + 1);
		}
	}
	return CACHE[k];
}


// recursive
int coincnt(int k) {
	if (CACHE[k] != -1) return CACHE[k];
	CACHE[k] = INF;
	for (int i = 0; i < N; ++i) {
		if (k >= A[i]) {
			int candidate = coincnt(k - A[i]) + 1;
			if (CACHE[k] > candidate) CACHE[k] = candidate;
		}

	}
	return CACHE[k];
}

int main() {

	scanf("%d%d", &N, &K);
	for (int i = 0; i < N; ++i) {
		scanf("%d", &A[i]);
	}

	// recursive
	CACHE[0] = 0;
	for (int i = 1; i <= K; ++i) {
		CACHE[i] = -1;
	}
	int ans = coincnt(K);
	if (ans >= INF) ans = -1;
	printf("%d\n", ans);

	// iterative
	CACHE[0] = 0;
	for (int i = 1; i <= K; ++i) {
		CACHE[i] = INF;
	}
	ans = coincnt2(K);
	if (ans >= INF) ans = -1;
	printf("%d\n", ans);

	

	return 0;
}