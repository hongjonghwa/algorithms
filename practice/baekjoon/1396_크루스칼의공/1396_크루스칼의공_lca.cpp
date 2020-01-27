/*
	소스 출처 :  http://jason9319.tistory.com/280 
*/
#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
int n, m, p[200010], par[200010][22], sz[200020], g[200020], h[200020], q;
vector<pair<int, pair<int, int> > > edge;

struct Node {
	int u, v, w;
	bool operator<(const Node & rhs) {
		return w < rhs.w;
	}
} node[100000];

vector<int> vt[200001];
int find(int h) {
	return h == p[h] ? h : p[h] = find(p[h]);
}

void dfs(int curr) {
	//for (auto next : vt[curr]) {
	for (size_t i = 0; i < vt[curr].size(); ++i) {
		//if (next == prev)continue;
		int next = vt[curr][i];
		par[next][0] = curr;
		h[next] = h[curr] + 1;
		dfs(next);
	}
}
int getlca(int x, int y) {
	if (h[x] > h[y])
		swap(x, y);

	/* 
	for (int i = 20; i >= 0; i--) {
		if (h[y] - h[x] >= (1 << i))
			y = par[y][i];
	}
	*/
	int diff = h[y] - h[x];
	for (int i = 0; diff; ++i) {
		if (diff & 1) y = par[y][i]; // 비트연산 필요
		diff >>= 1;
	}

	if (x == y)return x;
	for (int i = 20; i >= 0; i--) {
		if (par[x][i] != par[y][i]) {
			x = par[x][i];
			y = par[y][i];
		}
	}
	return par[x][0];
}
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n + m; i++) {
		p[i] = i;
		sz[i] = 1;
	}
	for (int i = 0; i < m; i++) {
		int x, y, z;
		scanf("%d%d%d", &x, &y, &z);
		node[i].u = x, node[i].v = y, node[i].w = z;
	}
	sort(node, node + m);
	for (int i = n + 1; i <= n + m; i++) {
		int x = node[i - n - 1].u;
		int y = node[i - n - 1].v;
		int z = node[i - n - 1].w;

		x = find(x), y = find(y);

		if (x == y) continue;
		sz[i] = sz[x] + sz[y];
		g[i] = z;
		vt[i].push_back(x);
		vt[i].push_back(y);
		p[x] = p[y] = i;
	}
	for (int i = n + m; i > 0; i--) {
		if (!h[i])
			dfs(i);
	}
	for (int j = 1; j <= 20; j++) {
		for (int i = 1; i <= n + m; i++)
			par[i][j] = par[par[i][j - 1]][j - 1];
	}
	scanf("%d", &q);
	for (int i = 0; i < q; ++i) {
	//while (q--) {
		int x, y;
		scanf("%d%d", &x, &y);
		if (find(x) != find(y)) {
			puts("-1");
			continue;
		}
		int lca = getlca(x, y);
		printf("%d %d\n", g[lca], sz[lca]);
	}
	return 0;
}


