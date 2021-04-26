#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<assert.h>

int N, K;
int A[10];



int main() {
	scanf("%d%d", &N, &K);
	for (int i = 0; i < N; ++i) {
		scanf("%d", &A[i]);
	}
	int coincnt = 0;
	for (int i = N - 1; i >= 0 && K > 0 ; --i) {
		coincnt += K / A[i];
		K %= A[i];
	}

	assert(K == 0);
	printf("%d", coincnt);

	return 0;
}