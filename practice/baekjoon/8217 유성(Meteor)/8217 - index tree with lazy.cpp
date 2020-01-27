/*
소스 참고 :  
http://jason9319.tistory.com/282
http://sgc109.tistory.com/203

naive segmentationg tree
naive fenwick tree

*/
#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <algorithm>
#include <vector>
#include <string.h>
#include <assert.h>
using namespace std;
int N, M, K; // N국가 M궤도 K유성우
int owner[300001]; // M : 소유국가
int goal[300001]; // N : 국가별 목표치

struct Meteor {
	int u, v, w;
} meteor[300001];

vector<int> region[300001];


// 524288 10^19?
//int x[300001];
long long int x[524288 * 2];

// naive
void update(int lo, int hi, int w) {
	//printf(" update : %d %d %d \n", lo, hi, w);
	lo += 524287, hi += 524287;
	for (; lo < hi;) {
		if (lo & 1) { // right child
			x[lo] += w;
			//printf(" l : %d \n", lo);
			++lo;
		}
		if (!(hi & 1)) { // left child
			x[hi] += w;
			//printf(" h : %d \n", hi);
			--hi;
		}
		lo >>= 1;
		hi >>= 1;
	}
	if (lo == hi) {
		x[lo] += w;
		//printf(" c : %d \n", lo);
	}
}

long long int sum(int nn) {
	//printf("%d : ", nn);
	nn += 524287;
	long long int ret = 0;
	while (nn) {
		//printf(" -> %d %d, ", nn, x[nn]);
		ret += x[nn];
		nn >>= 1;
	}
	//printf("\n");
	return ret;
}
void rain(int u, int v, int w) {
	if (u <= v) {
		update(u, v, w);
	}
	else {
		update(1, v, w);
		update(u, M, w);
	}
}

int d_lo[300001], d_hi[300001];
vector<int> vt[300001];

int main() {
	scanf("%d%d", &N, &M);
	for (int i = 1; i <=M ; ++i) scanf("%d", &owner[i]);
	for (int i = 1; i <= N; ++i) scanf("%d", &goal[i]);
	scanf("%d", &K);
	for (int i = 1; i <= K; ++i) scanf("%d%d%d", &meteor[i].u, &meteor[i].v, &meteor[i].w);
	//for (int i = 1; i <= M; ++i) printf(" %d", owner[i]); printf("\n");
	//for (int i = 1; i <= N; ++i) printf(" %d", goal[i]); printf("\n");
	//for (int i = 1; i <= K; ++i) printf("%d %d %d\n", meteor[i].u, meteor[i].v, meteor[i].w);

	for (int i = 1; i <= M; ++i){
		region[owner[i]].push_back(i);
		//printf("push %d %d\n", owner[i], i);
	}

	for (int i = 1; i <= N; ++i) {
		d_lo[i] = 0, d_hi[i] = K + 1;
		vt[(K + 1) >> 1].push_back(i);
	}

	
	int f = 1;
	while (f){
		memset(x, 0, sizeof(x));
		f = 0;
		for (int kk = 1; kk <= K; ++kk) {
			int &u = meteor[kk].u, &v = meteor[kk].v, &w = meteor[kk].w;
			rain(u, v, w);

			while (vt[kk].size()) {
				f = 1;
				int nn = vt[kk].back();
				vt[kk].pop_back();

				long long int ret = 0;
				for (int i = 0; i < region[nn].size(); ++i) {
					ret += sum(region[nn][i]);
				}
				if (ret >= goal[nn]) d_hi[nn] = kk;
				else d_lo[nn] = kk;

				if (d_lo[nn] + 1 < d_hi[nn]) {
					vt[(d_lo[nn] + d_hi[nn]) >> 1].push_back(nn);
				}

			}
		}
	}

	for (int nn = 1; nn <= N; ++nn) {
		if (d_hi[nn] == K + 1) printf("NIE\n");
		else printf("%d\n", d_hi[nn]);
	}

	return 0;
}