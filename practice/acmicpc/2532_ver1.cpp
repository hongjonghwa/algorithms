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
	int no, left, right;
} node[500000];
int x[500000];


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
void uniq1() {
	int i = 0;
	for (int j = 1; j < N; ++j) {
		if (node[i].left == node[j].left && node[i].right == node[j].right) continue;
		i++;
		//node[i] = node[j];
		swap1(node[i], node[j]);
	}
	N = i + 1;
}

void sort2(int lo, int hi) {
	if (lo >= hi) return;
	int mid = (lo + hi) / 2;
	int pivot_l = node[mid].left, pivot_r = node[mid].right;
	int i = lo, j = hi;
	while (i <= j) {
		while (
			node[i].right < pivot_r ||
			(node[i].right == pivot_r && node[i].left > pivot_l)
			) i++;
		while (
			node[j].right > pivot_r ||
			(node[j].right == pivot_r && node[j].left < pivot_l)
			) j--;
		if (i <= j) {
			swap1(node[i], node[j]);
			i++;
			j--;
		}
	}
	sort2(lo, j);
	sort2(i, hi);
}

void report(){
	for (int i = 0; i < N; ++i)
		printf("%d %d %d\n", node[i].no, node[i].left, node[i].right);
}

int main() {
	scanf("%d", &N);
	for (int i = 0 ; i < N ; ++i)
		scanf("%d%d%d", &node[i].no, &node[i].left, &node[i].right);
	//printf("####### init \n"); report();

	sort1(0, N - 1);
	//printf("####### sort \n");report();
	uniq1();
	//printf("####### uniq \n"); report();
	for (int i = 0; i < N; ++i)
		node[i].no = i;
	//printf("####### re-num \n"); report();
	sort2(0, N - 1);
	//printf("####### sort2 \n"); report();


	int ans = 0;
	for (int i = 0; i < N; ++i) {
		int &t = node[i].no;
		//printf("T : %d\n ", t);
		int lo = -1, hi = ans;
		// x[lo] > t > x[hi] 
		while (lo + 1< hi) {
			//printf("lo ~ hi : %d ~ %d \n", lo, hi);
			int mid = (lo + hi) / 2;
			if (t < x[mid]) lo = mid; // t보다 크다
			else hi = mid; // t보다 작거나 같아..
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
	printf("%d", ans);

	return 0;
}