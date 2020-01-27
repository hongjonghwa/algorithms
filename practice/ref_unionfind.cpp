
#include <stdio.h>
#include <iostream>
#include <ctime>

// ALLY : 동맹
// @author jaechun.yoo

const int MAX_N = 100003;
const int MAX_M = 100003;
const int MAX_Q = 200003;
int N, M, Q;
struct Edge {
	int s, e, deleted;
} e[MAX_M];
struct Query {
	int type, p1, p2;
} q[MAX_Q];
int parent[MAX_N], depth[MAX_N];
int ans[MAX_Q], aidx;

int find(int n) {
	if (n == parent[n]) return n;
	return parent[n] = find(parent[n]);
}

int merge(int n1, int n2) {
	int r1 = find(n1);
	int r2 = find(n2);
	if (r1 == r2) return 0;

	if (depth[r1] < depth[r2]) {
		parent[r1] = r2;
	} else {
		parent[r2] = r1;
	}
	if (depth[r1] == depth[r2]) {
		++depth[r1];
	}

	return 1;
}

int main() {
	clock_t startTime = clock();
	//freopen("sample_input.txt", "r", stdin);
	//freopen("eval_input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);

	int T; scanf("%d", &T);

	for (int test_case = 1; test_case <= T; ++test_case) {
		scanf("%d%d", &N, &M);
		for (int i = 1; i <= M; ++i) {
			scanf("%d%d", &e[i].s, &e[i].e);
			e[i].deleted = 0;
		}
		scanf("%d", &Q);
		for (int i = 1; i <= Q; ++i) {
			scanf("%d", &q[i].type);
			if (q[i].type == 1) {		// 간선 삭제
				scanf("%d", &q[i].p1);
				e[q[i].p1].deleted = 1;	// 삭제 마킹
			} else {		// tmp1 == 2, 찾기
				scanf("%d%d", &q[i].p1, &q[i].p2);
			}
		}

		// 삭제된 간선을 제외하고 초기 그래프 생성 - Union Find
		for (int i = 1; i <= N; ++i) {
			parent[i] = i;
			depth[i] = 1;
		}

		for (int i = 1; i <= M; ++i) {
			if (e[i].deleted) continue;
			merge(e[i].s, e[i].e);
		}

		aidx = 0;

		// 뒤에서 부터 반대로 Query에 질의
		for (int i = Q; i >= 1; --i) {
			if (q[i].type == 1) {		// 삭제 커맨드 -> 간선 연결
				merge(e[q[i].p1].s, e[q[i].p1].e);
			} else {					// 연결관계 체크
				if (find(q[i].p1) == find(q[i].p2)) {
					ans[aidx++] = 1;
				} else {
					ans[aidx++] = 0;
				}
			}
		}

		printf("#%d ", test_case);
		for (int i = aidx - 1; i >= 0; --i) {
			if (ans[i] == 0) {
				printf("0");
			} else {
				printf("1");
			}
		}
		printf("\n");
	}

	//printf("\nElapsed Time : %.3f\n", (double)(clock() - startTime) / CLOCKS_PER_SEC);
	return 0;
}
