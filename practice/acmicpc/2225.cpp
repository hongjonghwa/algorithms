#define _CRT_SECURE_NO_WARNINGS
#define MOD 1000000000
#include<stdio.h>

int N, K;
int CACHE[201][201]; // k���� n�� ����� ����� ��
int main() {
	scanf("%d%d", &N, &K);
	CACHE[0][0] = 1;
	for (int k = 1; k <= K; ++k) {
		CACHE[k][0] = 1;
		int sum = CACHE[k - 1][0];
		for (int n = 1; n <= N; ++n) {
			sum += CACHE[k - 1][n];
			if (sum > MOD) sum -= MOD;
			CACHE[k][n] = sum;
		}
	}
	printf("%d\n", CACHE[K][N]);

}