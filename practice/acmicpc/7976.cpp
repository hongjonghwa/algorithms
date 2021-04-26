#define _CRT_SECURE_NO_WARNINGS
#define MIN(a,b) ((a)<(b)?(a):(b))
#define MAX(a,b) ((a)>(b)?(a):(b))
#define EVEN 0
#define ODD 1
#include<stdio.h>
/*
	http://wowoto.me/boj12103/
	https://gist.github.com/Acka1357/87e0ef6122ed780301689911d8546c52

	K개 묶음으로로 모두 짝수 혹은 홀수를 만들기 위해서는
	x[0], x[K], x[K*2], x[K*3] 은 모두 짝수 혹은 홀수 여야 함.
	x[1], x[K+1], x[K*2+1], x[K*3+1] 또한 동일함

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
	d[0][EVEN] = cnt[0][ODD] ; // MOD 0 를 모두 짝수로 만들기 위해 변경이 필요한 갯수는 홀수의 count
	d[0][ODD]  = cnt[0][EVEN];
	for (int i = 1; i < K; ++i) {
		// MOD 0 ~ i합을 짝수로
		// d[i-1][0] + i 번째의 odd 갯수, d[i-1][1] + i번째의 홀수 갯수
		d[i][EVEN] = MIN(d[i - 1][EVEN] + cnt[i][ODD] , d[i - 1][ODD] + cnt[i][EVEN]);
		d[i][ODD]  = MIN(d[i - 1][EVEN] + cnt[i][EVEN], d[i - 1][ODD] + cnt[i][ODD] );
	}
	printf("%d\n", d[K - 1][0]);

	return 0;
}

