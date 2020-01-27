#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int N, M, K;
int x[1000001];
long long int ft[1000001];

void add(int p, int val) {
	//printf("add : %d, %d \n", p, val);
	while (p<=N) {
		ft[p] += val;
		p += (p & -p);
	}
}
long long int sum(int p) {
	long long int ret = 0;
	while (p) {
		ret += ft[p];
		p &= (p - 1);
	}
	return ret;
}

void debug() {
	for (int d = 1; d <= N; ++d) printf("%lld ", ft[d]); printf("\n");
	for (int d = 1; d <= N; ++d) printf("%d ", x[d]); printf("\n");
}

int main() {
	scanf("%d%d%d", &N, &M, &K);
	for (int i = 1;i<=N; ++i)
		scanf("%d", &x[i]);
	for (int i = 1; i <= N; ++i)
		add(i, x[i]);

	int u, v, w;
	//debug()
	for (int i = 0; i < M + K; ++i) {
		scanf("%d%d%d", &u, &v, &w);
		//printf("u,v,w : %d %d %d\n", u, v, w); 
		if (u == 1) {
			add(v, w - x[v]);
			x[v] = w;
		}
		else {
			printf("%lld\n", sum(w) - sum(v - 1));
		}
	}

}