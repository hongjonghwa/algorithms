/*
소스 참고 :  
http://jason9319.tistory.com/282
http://sgc109.tistory.com/203


*/
#define _CRT_SECURE_NO_WARNINGS

//#include <cstdio>
#include <iostream>
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
long long int x[300002];
//long long int x[524288 * 2];

void add(int n, int val) {
	// last 1을 더한다
	while (n <= M + 1) {
		x[n] += val;
		n += (n & -n);
	}
}
void update(int lo, int hi, int w) {
	add(lo, w);
	add(hi + 1, -w);
}

long long int sum(int n) {
	// last1을 뺀다
	long long int ret = 0;
	while (n) {
		ret += x[n];
		n &= (n - 1);
	}
	return ret;
}
void rain(int u, int v, int w) {
	if (u <= v) {
		//update(u, v, w);
		add(u, w);
		add(v + 1, -w);
	}
	else {
		//update(1, v, w);
		//update(u, M, w);
		add(1, w);
		add(v + 1, -w);
		add(u, w);
	}
}

int d_lo[300001], d_hi[300001];
vector<int> vt[300001];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N >> M;
	for (int i = 1; i <=M ; ++i) cin >> owner[i];
	for (int i = 1; i <= N; ++i) cin >> goal[i];
	cin >> K;
	for (int i = 1; i <= K; ++i) cin >> meteor[i].u >> meteor[i].v >> meteor[i].w;
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
					if (ret >= goal[nn]) break;
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
		if (d_hi[nn] == K + 1) cout << "NIE\n";
		else cout << d_hi[nn] << '\n';
	}

	return 0;
}