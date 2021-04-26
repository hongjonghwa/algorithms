/*
소스 출처 :  http://jason9319.tistory.com/284
*/
#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
int n, m, q;
int p[100001], sz[100001];

struct Node {
	int u, v, w;
	bool operator<(const Node & rhs) {
		return w < rhs.w;
	}
} node[100000];
struct Query {
	int x, y;
} query[100000];

int find(int h) {
	return h == p[h] ? h : p[h] = find(p[h]);
}

// parellel binary search
vector<int> vt[100000];
int c_sz[1000001]; //c 값 별로 size 를 
int q_lo[100000], q_hi[100000]; // m에 의한 값

void init_unionfind() {
	// union-find default
	for (int i = 1; i <= n; i++) p[i] = i, sz[i] = 1;
}

int main() {
	//setbuf(stdout, NULL); // 주의! 출력이 많으면 엄청 느려짐
	// data
	scanf("%d%d", &n, &m);

	for (int i = 0; i < m; i++)
		scanf("%d%d%d", &node[i].u, &node[i].v, &node[i].w);
	scanf("%d", &q);
	for (int i = 0; i < m; i++)
		scanf("%d%d", &query[i].x, &query[i].y);

	sort(node, node + m); // node sort

	init_unionfind();
	for (int j = 0; j < m; ++j) {

		int u = find(node[j].u), v = find(node[j].v);
		if (u != v) {
			p[v] = u;
			c_sz[node[j].w] = (sz[u] += sz[v]);
		}
	}
	for (int i = 0; i < q; ++i) {
		q_lo[i] = -1, q_hi[i] = m;
		vt[(m - 1) >> 1].push_back(i);
		//printf("push : %d %d \n", (m - 1) / 2, i);
	}

	int f = 1;
	while (f) {
		init_unionfind();
		f = 0;
		for (int j = 0; j < m; ++j) {
			int u = find(node[j].u), v = find(node[j].v);
			if (u != v) {
				p[v] = u;
				sz[u] += sz[v];
			}
			while (vt[j].size()) {

				int qidx = vt[j].back();
				vt[j].pop_back();
				int x = find(query[qidx].x), y = find(query[qidx].y);
				if (x == y) {
					q_hi[qidx] = j;
				}
				else {
					q_lo[qidx] = j;
				}
				if (q_lo[qidx] + 1 < q_hi[qidx]) {
					f = 1;
					int qmid = (q_hi[qidx] + q_lo[qidx]) >> 1;
					vt[qmid].push_back(qidx);
					//printf("range : %d %d \n", q_lo[qidx], q_hi[qidx]);
					//printf("push : %d %d \n", qmid, qidx);
				}
			}
			/*

			if (find(query[i].x) == find(query[i].y)) {
			printf("%d %d\n", node[j].w, sz[u]);
			f = 1;
			break;
			}
			*/
		}
	}


	for (int i = 0; i < q; ++i) {
		if (q_hi[i] == m) printf("-1\n");
		else {
			int cost = node[q_hi[i]].w;
			int size = c_sz[cost];
			printf("%d %d\n", cost, size);
		}

	}
	return 0;
}


