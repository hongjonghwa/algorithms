#define _CRT_SECURE_NO_WARNINGS
#define ABS(x) ((x)<0 ? -(x) : (x))
#include<stdio.h>

/*
	https://www.acmicpc.net/problem/1659

	*/

template<class T>
inline T abs(T x) {
	return x < 0 ? -(x) : x;
}

int S, T;
int s[500001], t[500001];
long long int d[5000][5000];

long long int dp() {
	for (int i = 0; i <= S; ++i)
		for (int j = 0; j <= T; ++j)
			d[i][j] = 0x3FFFFFFFFFFFFFFF;
	d[0][0] = 0;
	for (int i = 1; i <= S; ++i)
		for (int j = 1; j <= T; ++j) {
			long long int tmin = d[i - 1][j - 1];
			if (d[i - 1][j] < tmin) tmin = d[i - 1][j];
			if (d[i][j - 1] < tmin) tmin = d[i][j - 1];
			tmin += ABS(s[i] - t[j]);
			if (tmin < d[i][j]) d[i][j] = tmin;
		}


	//out minimal sum
	return d[S][T];
}

int main() {
	scanf("%d%d", &S, &T);
	for (int i = 1; i <= S; ++i) scanf("%d", &s[i]);
	for (int i = 1; i <= T; ++i) scanf("%d", &t[i]);

	printf("%lld\n", dp());

	int rec[2] = { 0, };
	printf("%lld\n", rec[0]);
	printf("%lld\n", rec[1]);

}