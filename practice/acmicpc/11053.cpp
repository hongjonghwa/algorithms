#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<assert.h>

/*
	https://en.wikipedia.org/wiki/Longest_increasing_subsequence
*/

int x[1001];

int N;


/*
inline int COST(int from, int to) {
assert(to != 0);
if (from == to) return 1;
if (from == 0) return 2;
if (ABS(to - from) == 2) return 4;
return 3;
}
*/

int main() {
	scanf("%d", &N);

	int ret = 0; // �� - lis
	int t;
	for (int i = 1; i <= N; ++i) {
		scanf("%d", &t);
		int lo = 0, hi = ret+1; // ret+1�� INF ���� �ִٰ� ����
		// �־��� ������ ���� ���� ������ ��ġ
		while (lo + 1 < hi) {
			// �Һ��� : x[lo] < t <= x[hi]
			int mid = (lo + hi) / 2;
			if (t > x[mid]) lo = mid;
			//else if (t == x[mid]) lo = hi = mid;
			else hi = mid; // t== mid�϶���
		}
		x[hi] = t;
		if (hi == ret+1) ret++;
		/*
		// debug
		for (int tt = 0; tt <= ret + 1; ++tt)
			printf("%d ", x[tt]);
		printf("[%d]\n", ret);
		*/
	}

	printf("%d ", ret);

	return 0;
}