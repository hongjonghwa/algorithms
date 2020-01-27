#define _CRT_SECURE_NO_WARNINGS
#define MIN(a,b) ((a)<(b)?(a):(b))
#define MAX(a,b) ((a)>(b)?(a):(b))
#include<stdio.h>

int N;
int x[1000001];
int lsum[1000001], rsum[1000001];
int skipsum[1000001];
int gcd(int p, int q) {
	return q == 0 ? p : gcd(q, p%q);
}

int solv() {
	lsum[1] = x[1];
	for (int i = 2; i <= N; ++i)
		lsum[i] = gcd(x[i], lsum[i - 1]);

	rsum[N] = x[N];
	for (int i = N - 1; i >= 1; --i)
		rsum[i] = gcd(x[i], rsum[i + 1]);

	skipsum[1] = rsum[2];
	skipsum[N] = lsum[N-1];
	for (int i = 2; i < N; ++i)
		skipsum[i] = gcd(lsum[i-1], rsum[i+1]);

	int answer = -1;
	for (int i = 1; i <= N; ++i) {
		if ((x[i] % skipsum[i] != 0) &&
			(answer == -1 || skipsum[i] > skipsum[answer]) ) answer = i;
	}
	return answer;
}
int main() {
	scanf("%d", &N);
	for (int i = 1; i <= N; ++i)
		scanf("%d", &x[i]);

	int answer = solv();
	if (answer != -1)
		printf("%d %d\n", skipsum[answer], x[answer]);
	else 
		printf("-1\n");
	

	return 0;
}

