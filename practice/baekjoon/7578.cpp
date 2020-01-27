#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

int N;
int x[500001];
int ridx[1000001];

int tmp[500001];
long long int merge(int lo, int hi) {
	long long int ret = 0;
	if (lo == hi) return ret;

	int mid = (lo + hi) / 2;
	ret += merge(lo, mid);
	ret += merge(mid + 1, hi);

	int i = lo, j = mid + 1, k = lo;
	while (i <= mid && j <= hi) {
		if (x[j] < x[i]) {
			tmp[k++] = x[j++];
			ret += mid - i + 1;
		}
		else tmp[k++] = x[i++];
	}
	while (i <= mid)  tmp[k++] = x[i++];
	while (j <= hi)  tmp[k++] = x[j++];

	for (int kk = lo; kk <= hi; ++kk)
		x[kk] = tmp[kk];


	return ret;
}


int ft[500001];
void add(int idx, int addVal) {// 마지막 1을 더함
	while (idx <= N) {
		ft[idx] += addVal;
		idx += idx & -idx;
	}
}
int sum(int idx) { // 마지막 1을 뺌
	int ret = 0;
	while (idx) { 
		ret += ft[idx];
		idx &= idx - 1;
	}
	return ret;
}
long long int solv2() {
	long long int ret = 0;
	for (int i = 1; i <= N; ++i) {
		add(x[i], 1);
		ret += sum(N) - sum(x[i]);
	}
	return ret;
}

int main() {
	scanf("%d", &N);

	int u;
	for (int i = 1 ; i <= N ; ++i){
		scanf("%d", &x[i]);
		ridx[x[i]] = i;
	}
	for (int i = 1; i <= N; ++i) {
		scanf("%d", &u);
		x[i] = ridx[u];
	}

	// merge sort
	//printf("%lld\n", merge(1,N));
	// fenwick tree
	printf("%lld\n", solv2());
	return 0;
}