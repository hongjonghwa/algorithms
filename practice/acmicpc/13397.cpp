#define _CRT_SECURE_NO_WARNINGS
#define MIN(a,b) ((a)<(b)?(a):(b))
#define MAX(a,b) ((a)>(b)?(a):(b))
#include<stdio.h>

int N, M;
int x[5000];
bool pass(int v) {
	int cnt = 1, mi, mx;
	mi = mx = x[0];
	for (int i = 1; i < N; ++i) {
		mi = MIN(mi, x[i]);
		mx = MAX(mx, x[i]);
		if (mx - mi > v) {
			mi = mx = x[i];
			cnt++;
			if (cnt > M) return false;
		}
	}
	return true;
}
int solv() {
	int lo = -1;
	int hi = 10000 * N + 1;
	// lo pass, hi not pass
	while (lo + 1 < hi) {
		int mid = (lo + hi) / 2;
		if (pass(mid)) hi = mid;
		else lo = mid;
	}
	return hi;
}
int main() {
	scanf("%d%d", &N, &M);
	for (int i = 0; i < N; ++i)
		scanf("%d", &x[i]);
	printf("%d\n", solv());

	return 0;
}
