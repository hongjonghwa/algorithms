#include<stdio.h>
#include<string.h>
#define INF 987654321

int N, M;
int D[2501][2501];
long long int C[2500][2501]

int main(){
	scanf("%d%d", &N, &M);
	memset(D, 63, sizeof(D));
	for (int i = 1 ; i <= N ; ++i)
		D[i][i] = 0;

	for (int k = 1 ; k <= N ; ++k)
		for (int i = 1 ; i <= N ; ++i)
			for (int j = 1 ; j <= N ; ++j)
				if (D[i][j] > D[i][k] + D[k][j])
					D[i][j] = D[i][k] + D[k][j];

	C[1]
}
