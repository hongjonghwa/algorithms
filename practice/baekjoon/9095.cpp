#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<assert.h>

int N;
long long int CACHE[91];

int main() {
	CACHE[0] = 0;
	CACHE[1] = 1;
	for (int i = 2; i <= 90; ++i) {
		CACHE[i] = 1; // all zero case
		for (int j = i - 2; j > 0; j--)
			CACHE[i] += CACHE[j];
	}
	/*
	for (N = 0 ; N <= 90 ;++N){
		printf("%d %lld\n", N, CACHE[N]);
	}
	*/
	scanf("%d", &N);
	printf("%lld\n", CACHE[N]);

	return 0;
}