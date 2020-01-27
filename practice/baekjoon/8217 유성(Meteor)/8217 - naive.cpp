/*
소스 출처 :  http://jason9319.tistory.com/

naive segmentationg tree
naive fenwick tree

*/
#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <algorithm>
#include <vector>
#include <assert.h>
using namespace std;
int N, M, K; // N국가 M궤도 K유성우
int owner[300001]; // M : 소유국가
int goal[300001]; // N : 국가별 목표치

struct Meteor {
	int u, v, w;
} meteor[300001];

vector<int> region[300001];

int x[300001];

// naive
void update(int lo, int hi, int w) {
	for (int i = lo; i <= hi; ++i) x[i] += w;
}

int sum(int nn) {
	int sum = 0;
	for (int i = 0; i < region[nn].size(); ++i) {
		sum += x[region[nn][i]];
	}
	return sum;
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

	for (int nn = 1; nn <= N; ++nn){
		memset(x, 0, sizeof(x));
		int kk;
		for (kk = 1; kk <= K; ++kk) {
			int &u = meteor[kk].u, &v = meteor[kk].v, &w = meteor[kk].w;
			rain(u, v, w);

			int ret = sum(nn);
			if (ret >= goal[nn]) break;
		}
		if (kk == K+1) printf("NIE\n");
		else printf("%d\n", kk);

	}


	return 0;
}


