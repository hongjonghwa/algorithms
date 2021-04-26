#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<assert.h>

/*

11053�� ���� ����
https://en.wikipedia.org/wiki/Longest_increasing_subsequence
*/

int data[1000001];
int x[1000001]; // �̺�Ž���� �ʿ�
int xidx[1000001]; // ���ڸ� ��ġ Ȯ�ο� �ʿ�
int parent[1000001]; // prev seq ����

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
	
	for (int i = 1; i <= N; ++i) {
		int &t = data[i];
		scanf("%d", &t);
		int lo = 0, hi = ret + 1; // ret+1�� INF ���� �ִٰ� ����
								  // �־��� ������ ���� ���� ������ ��ġ
		while (lo + 1 < hi) {
			// �Һ��� : x[lo] < t <= x[hi]
			int mid = (lo + hi) / 2;
			if (t > x[mid]) lo = mid;
			//else if (t == x[mid]) lo = hi = mid;
			else hi = mid; // t== mid�϶���
		}
		x[hi] = t;
		xidx[hi] = i;
		parent[i] = xidx[hi - 1];
		if (hi == ret + 1) {
			ret++;
		}


	}

	printf("%d\n", ret);
	for (int i = xidx[ret], j = ret; i; i = parent[i]) 
		x[j--] = data[i];

	for (int i = 1; i <= ret; i++) 
		printf("%d ", x[i]);

	// debug
	/*
	for (int tt = 0; tt <= ret; ++tt)
		printf("%d ", x[tt]);
	printf("[%d]\n", ret);

	for (int tt = 0; tt <= ret; ++tt)
		printf("%d ", xidx[tt]);
	printf("[%d]\n", ret);
	
	for (int tt = 0; tt <= 6; ++tt)
		printf("%d ", parent[tt]);
	printf("[%d]\n", ret);
	*/
	return 0;
}