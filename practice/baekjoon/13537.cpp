#define _CRT_SECURE_NO_WARNINGS
#define MIN(a,b) ((a)<(b)?(a):(b))
#define MAX(a,b) ((a)>(b)?(a):(b))
#include<stdio.h>

int N, M;
int anw[100001];

template<class T>
void SWAP(T &a, T &b) {
	T temp = a; a = b; b = temp;
}

template<class T>
void quicksort(T *x, int lo, int hi) {
	if (lo >= hi) return;
	int mid = (lo + hi) / 2;
	T pivot = x[mid];
	int i = lo, j = hi;
	while (i <= j) {
		while (x[i] < pivot) i++;
		while (x[j] > pivot) j--;
		if (i <= j) {
			SWAP(x[i], x[j]);
			i++;
			j--;
		}
	}
	quicksort(x, lo, j);
	quicksort(x, i, hi);
}

int ftdata[100001];
struct FT {
	int n;
	void add1(int pos) {
		// last 1 +
		while (pos <= n) {
			ftdata[pos]++;
			pos += (pos & -pos);
		}
	}
	int sum(int pos){
		// last 1 -
		int ret = 0;
		while (pos) {
			ret += ftdata[pos];
			pos &= (pos - 1);
		}
		return ret;
	}

	FT(int number) { n = number; }
};

struct Data {
	int x, no;
	bool operator<(const Data &rhs) {
		return this->x < rhs.x;
	};
	bool operator>(const Data &rhs) {
		return this->x > rhs.x;
	};
} data[100001];

struct Query {
	int i, j, k, no;

	bool operator<(const Query &rhs) {
		return this->k < rhs.k;
	};
	bool operator>(const Query &rhs) {
		return this->k > rhs.k;
	};
} qry[100001];

int main() {
	scanf("%d", &N);
	for (int i = 1; i <= N; ++i) {
		data[i].no = i;
		scanf("%d", &data[i].x);
	}
	quicksort(data, 1, N);
	//for (int i = 1; i < N; ++i)	if (data[i].x > data[i+1].x) printf("ERROR!");

	scanf("%d", &M);
	for (int i = 1; i <= M; ++i){
		qry[i].no = i;
		scanf("%d%d%d", &qry[i].i, &qry[i].j, &qry[i].k);
	}
	quicksort(qry, 1, M);
	//for (int i = 1; i < M; ++i) if (qry[i].k > qry[i + 1].k) printf("ERROR!");

	FT ft(N);
	//for (int i = 1; i <= N; ++i) printf("Ft : %d \n", ftdata[i]);

	int n = N, m = M;
	while (m) {
		while (n && data[n].x > qry[m].k) ft.add1(data[n--].no);
		anw[qry[m].no] = ft.sum(qry[m].j) - ft.sum(qry[m].i - 1);
		//printf("Set Answer %d %d %d \n", qry[m].no, ft.sum(qry[m].j), ft.sum(qry[m].i - 1));
		m--;
	}
	for (int i = 1 ; i <= M ; ++i)
		printf("%d\n", anw[i]);

	return 0;
}

