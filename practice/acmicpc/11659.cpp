#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int N, M;
int x[100001];

int main() {
	scanf("%d%d", &N, &M);
	int sum=0, u, v;
	for (int i = 1; i <= N; ++i) {
		scanf("%d", &u);
		x[i] = (sum += u);
	}
	for (int i = 1; i <= M; ++i) {
		scanf("%d%d", &u, &v);
		printf("%d\n", x[v] - x[u - 1]);
	}
}