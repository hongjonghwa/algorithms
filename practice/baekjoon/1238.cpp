#define _CRT_SECURE_NO_WARNINGS
#define INF 987654321;
#include<stdio.h>

int N, M, X;
int x[1001][1001];

int main() {
	scanf("%d%d%d", &N, &M, &X);

	for (int i = 1 ; i <= N ; ++i)
		for (int j = 1 ; j <= N ; ++j)
			x[i][j] = INF;
	for (int i = 1; i <= N; ++i)
		x[i][i] = 0;

	int u, v, w;
	for (int i = 0; i < M; ++i) {
		scanf("%d%d%d", &u, &v, &w);
		if (x[u][v] > w) x[u][v] = w;
	}

	// Floyd
	// dijkstra 2번 돌리는 것이 더 빠름...
	for (int k = 1; k <= N; k++)
		for (int i = 1; i <= N; i++)
			for (int j = 1; j <= N; j++)
				if (x[i][j] > x[i][k] + x[k][j])
					x[i][j] = x[i][k] + x[k][j];

	int ret = 0;
	for (int i = 1; i <= N; ++i)
		if (ret < x[i][X] + x[X][i])
			ret = x[i][X] + x[X][i];

	printf("%d\n", ret);
}