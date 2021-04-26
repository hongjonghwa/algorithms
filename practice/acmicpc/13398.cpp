#define _CRT_SECURE_NO_WARNINGS
#define MAX(a,b) ( (a)>(b) ? (a) : (b) )
#include <stdio.h>

int N;
int x[100002];
int lmax[100002];
int rmax[100002];
int lmax1[100002];
int rmax1[100002];

int solv1() {
	for (int i = 1; i <= N; ++i) {
		lmax[i] = MAX(lmax[i - 1] + x[i], 0); // i에서 끝나는 최대값(0포함)
		lmax1[i] = MAX(lmax[i - 1], lmax1[i - 1] + x[i]); // i에서 끝나는 1개를 제외한 최대값(0포함)
	}
	for (int i = N; i >= 1; --i) {
		rmax[i] = MAX(rmax[i + 1] + x[i], 0);
		rmax1[i] = MAX(rmax[i + 1], rmax1[i + 1] + x[i]);
	}

	int ret = -9999;

	for (int i = 1; i <= N; ++i) {
		ret = MAX(ret, lmax1[i - 1] + x[i] + rmax[i + 1]);
		ret = MAX(ret, lmax[i - 1] + x[i] + rmax1[i + 1]);
	}
	return ret;
}

int solv2() {
	lmax[0] = -99999; // 아래 로직에서는  필수!!
	/*
		예외 케이스 lmax[1..N] lmax1[1..N] 은 모두 최소 1개의 값을 포함하지만,
	   마지막줄 lmax[i-1] 로 접근할 때는, 
	   lmax[0] 에는 값이 포함되지 않을 수 있다.
	   lmax[0] 을 포함하지 않도록 NINF 설정
	   */
	for (int i = 1; i <= N; ++i) {
		lmax[i] = MAX(lmax[i - 1], 0) + x[i]; // 최소 1개를 포함한 최대값 (누락없음)
		lmax1[i] = MAX(lmax1[i - 1], 0) + x[i];  //  lmax1중간에 하나 빠짐값 (그래도 최소 1개는 포함)
		lmax1[i] = MAX(lmax1[i], lmax[i-1]);
	}

	int ret = -9999;

	for (int i = 1; i <= N; ++i) {
		ret = MAX(ret, lmax[i]);
		ret = MAX(ret, lmax1[i]);

	}
	return ret;
}
int main() {
	scanf("%d", &N);
	for (int i = 1; i <= N; ++i)
		scanf("%d", &x[i]);

	//printf("%d\n", solv1());
	printf("%d\n", solv2());

	return 0;
}