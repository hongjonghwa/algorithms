#define _CRT_SECURE_NO_WARNINGS
#define MIN(a,b) ( (a)<(b) ? (a) : (b) )
#define INF 987654321
#include <stdio.h>

int N, M;
int A[100001];
int *x;

/*
void debug() {
	for (int d = 1; d <= N; ++d) printf("%lld ", ft[d]); printf("\n");
	for (int d = 1; d <= N; ++d) printf("%d ", x[d]); printf("\n");
}
*/
int st_query(int node, int left, int right, int qryLeft, int qryRight) {

	if (qryRight < left || right < qryLeft) return INF;
	if (qryLeft <= left && right <= qryRight) return x[node];

	if (left == right) return x[node];

	int mid = (left + right) / 2;
	int leftMin = st_query(node * 2, left, mid, qryLeft, qryRight);
	int rightMin = st_query(node * 2 + 1, mid + 1, right, qryLeft, qryRight);
	return MIN(leftMin, rightMin);

}

void st_update(int node, int left, int right, int pos, int newValue) {
	if (pos < left || pos > right) return;
	if (left == right) x[node] = newValue;
	else {
		int mid = (left + right) / 2;
		st_update(node * 2, left, mid, pos, newValue);
		st_update(node * 2 + 1, mid + 1, right, pos, newValue);
		x[node] = MIN(x[node * 2], x[node * 2 + 1]);
	}
}
void st_init(int node, int left, int right) {
	if (left == right) x[node] = A[left];
	else{
		int mid = (left + right) / 2;
		st_init(node * 2, left, mid);
		st_init(node * 2 + 1, mid + 1, right);
		x[node] = MIN(x[node * 2], x[node * 2 + 1]);
	}
}

int main() {
	scanf("%d", &N);
	for (int i = 1; i <= N; ++i)
		scanf("%d", &A[i]);
	scanf("%d", &M);

	//ST
	//x = new int[4 * N];
	int n = 1;
	while (n < N) n <<= 1;
	x = new int[n * 2];
	st_init(1, 1, N);
	
	int u, v, w;
	for (int i = 0; i < M; ++i) {
		scanf("%d%d%d", &u, &v, &w);
		if (u == 1)
			st_update(1, 1, N, v, w);
		else
			printf("%d\n", st_query(1, 1, N, v, w));
	}

}