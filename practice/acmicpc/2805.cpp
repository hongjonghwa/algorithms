#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

int N, M;
int A[1000000];



int main() {
	scanf("%d%d", &N, &M);
	for (int i = 0; i < N; ++i) {
		scanf("%d", &A[i]);
	}
	int lo = 1;
	int hi = 1000000001;

	// lo : 1, hi : 0
	while (lo + 1 < hi) {
		int mid = (lo + hi) / 2;
		//printf("%d %d %d\n", lo, hi, mid);

		long long int sum = 0;
		for (int i = 0; i < N; ++i)
			if (A[i] > mid)
				sum += (A[i] - mid); // 여기서 int overflow 발생 가능


		if ( sum >= M) lo = mid;
		else hi = mid;

	}
	printf("%d", lo);

	return 0;
}