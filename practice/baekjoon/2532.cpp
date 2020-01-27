#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<assert.h>

int N;

template<class T>
void swap1(T &a, T &b) {
	T t = a;
	a = b;
	b = t;
}

struct Node {
	int left, right;
} node[500001];
int x[500001];


void sort1(int lo, int hi) {
	if (lo >= hi) return;
	int mid = (lo + hi) / 2;
	int pivot_l = node[mid].left, pivot_r = node[mid].right;
	int i = lo, j = hi;
	while (i <= j ) {
		while (
				node[i].left < pivot_l ||
				(node[i].left == pivot_l && node[i].right > pivot_r)
			) i++;
		while (
				node[j].left > pivot_l ||
				(node[j].left == pivot_l && node[j].right < pivot_r)
			) j--;
		if (i <= j) {
			swap1(node[i], node[j]); 
			i++;
			j--;
		}
	}
	sort1(lo, j);
	sort1(i, hi);
}

void report(){
	for (int i = 1; i <= N; ++i)
		printf("%d %d \n", node[i].left, node[i].right);
}

int main() {
	scanf("%d", &N);
	int nullval;
	for (int i = 1 ; i <= N ; ++i)
		scanf("%d%d%d", &nullval, &node[i].left, &node[i].right);
	//printf("####### init \n"); report();

	sort1(1, N);
	//printf("####### sort \n");report();


	node[0].left = node[0].right = -1;
	int ans = 0;
	for (int i = 1; i <= N; ++i) {
		// unique
		if (node[i].left == node[i - 1].left && node[i].right == node[i - 1].right) continue;

		int &t = node[i].right;
		// right 의 역순으로 lis 구성, 
		// 같은 수가 나올때도 그 끝에 붙임. (덮어 쓰지 않음...)
		int lo = -1, hi = ans;
		// x[lo] > t > x[hi] 
		while (lo + 1 != hi) {
			int mid = (lo + hi) / 2;
			if (t <= x[mid]) lo = mid; // 같은 수 붙임
			else hi = mid; // t보다 작거나 ..
		}
		x[hi] = t;
		//printf("lo: %d", lo);
		if (hi == ans) ans++;

		/*
		for (int i = 0; i < ans ; ++i)
			printf("%d ", x[i]);
		printf("\n");
		*/

	}
	printf("%d\n", ans);

	return 0;
}