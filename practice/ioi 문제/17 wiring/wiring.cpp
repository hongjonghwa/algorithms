/*
문제 : http://ioi2017.org/contest/tasks/

풀이 : http://blog.myungwoo.kr/117 [PS 이야기]

관련 논문 : http://cgm.cs.mcgill.ca/~godfried/publications/akiyama-chvatal-festschrift.pdf
            https://web.archive.org/web/20120907013424/http://john2.poly.edu/papers/jcb05/paper.pdf
*/
//#include "wiring.h"
//#include <bits/stdc++.h>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long lld;

#define MAXN 100005
#define sz(v) ((int)(v).size())

int N, M, K;
int A[MAXN], B[MAXN];
int near[MAXN * 2], sp[MAXN * 2]; lld S[MAXN * 2];
int last[MAXN * 4];
lld D[MAXN * 2];

struct Z {
	int x; bool t;
} C[MAXN * 2];

lld min_total_length(vector<int> r, vector<int> b) {
	N = sz(r); M = sz(b); K = N + M;
	for (int i = 1; i <= N; i++) A[i] = r[i - 1];
	for (int i = 1; i <= M; i++) B[i] = b[i - 1];

	/* Merge */
	for (int i = 1, j = 1, k = 1; k <= K; k++) {
		if (j > M || i <= N && A[i] < B[j])
			C[k] = { A[i++], 0 };
		else
			C[k] = { B[j++], 1 };
	}

	/* Get nearest point */
	for (int i = 1; i <= K; i++) near[i] = 2e9;
	{
		int rec[2] = { 0, }; // 0,1의 마지막 번호
		for (int i = 1; i <= K; i++) { // left to right
			if (rec[!C[i].t])
				near[i] = min(near[i], C[i].x - C[rec[!C[i].t]].x); // 반대편의 거리 저장
			rec[C[i].t] = i;
		}
	}
	{
		int rec[2] = { 0, };
		for (int i = K; i>0; i--) { // right to left
			if (rec[!C[i].t]) near[i] = min(near[i], C[rec[!C[i].t]].x - C[i].x);
			rec[C[i].t] = i;
		}
	}

	for (int i = 1; i <= K; i++) sp[i] = -1;
	for (int i = 0; i <= K + K; i++) last[i] = -1;
	last[K] = 0; int now = 0;
	for (int i = 1; i <= K; i++) {
		if (C[i].t) now++, S[i] = C[i].x;
		else now--, S[i] = -C[i].x;
		S[i] += S[i - 1];
		if (last[now + K] >= 0)	sp[i] = last[now + K]; // sp => j
		last[now + K] = i;
	}
	for (int i = 1; i <= K; i++) {
		D[i] = D[i - 1] + near[i]; // 약결함을 DP
		if (sp[i] >= 0) { // j 이후 강결합 case --> 여러개가 있어도 마지막 한 쌍만 고려
			int j = sp[i];
			D[i] = min(D[i], D[j] + abs(S[i] - S[j])); // D[j] + j 이후 쌍으로 강결합
													   // 모든 쌍 내의 S,T값은 한 쪽이 무조건 크거나 작다
													   // 아닐경우는 이미 반영됨 66~67 line
		}
	}
	return D[K];
}


