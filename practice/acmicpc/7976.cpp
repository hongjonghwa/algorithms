#define _CRT_SECURE_NO_WARNINGS
#define MIN(a,b) ((a)<(b)?(a):(b))
#define MAX(a,b) ((a)>(b)?(a):(b))
#define EVEN 0
#define ODD 1
#include<stdio.h>
/*
	http://wowoto.me/boj12103/
	https://gist.github.com/Acka1357/87e0ef6122ed780301689911d8546c52

	K�� �������η� ��� ¦�� Ȥ�� Ȧ���� ����� ���ؼ���
	x[0], x[K], x[K*2], x[K*3] �� ��� ¦�� Ȥ�� Ȧ�� ���� ��.
	x[1], x[K+1], x[K*2+1], x[K*3+1] ���� ������

*/

int N, K;
int cnt[1000001][2]; // odd-even count
int d[1000001][2];

int main() {
	scanf("%d%d", &N, &K);
	int x;
	for (int i = 0; i < N; ++i) {
		scanf("%d", &x);
		cnt[i%K][x & 1]++;
	}
	d[0][EVEN] = cnt[0][ODD] ; // MOD 0 �� ��� ¦���� ����� ���� ������ �ʿ��� ������ Ȧ���� count
	d[0][ODD]  = cnt[0][EVEN];
	for (int i = 1; i < K; ++i) {
		// MOD 0 ~ i���� ¦����
		// d[i-1][0] + i ��°�� odd ����, d[i-1][1] + i��°�� Ȧ�� ����
		d[i][EVEN] = MIN(d[i - 1][EVEN] + cnt[i][ODD] , d[i - 1][ODD] + cnt[i][EVEN]);
		d[i][ODD]  = MIN(d[i - 1][EVEN] + cnt[i][EVEN], d[i - 1][ODD] + cnt[i][ODD] );
	}
	printf("%d\n", d[K - 1][0]);

	return 0;
}

