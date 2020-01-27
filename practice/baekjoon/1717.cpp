#define _CRT_SECURE_NO_WARNINGS

#define SWAPT(T,a,b) { T tmp = a; a = b; b = tmp;}
#include<stdio.h>
#include<assert.h>

int grp(int u);

int N, M;
int parent[1000001]; // 0 init
int rnk[1000001]; // 0 init

void merge(int u, int v) {
	u = grp(u);
	v = grp(v);
	if (u == v) return;
	// merge 1
	/*
	if (rnk[u] < rnk[v]) SWAPT(int, u, v);
	parent[v] = u;
	if (rnk[u] == rnk[v]) rnk[u]++;
	*/
	// merge 2
	if (rnk[u] > rnk[v])
		parent[v] = u;
	else if (rnk[u] < rnk[v])
		parent[u] = v;
	else { parent[v] = u; rnk[u]++; }


}
int grp(int u) {
	//assert(u != parent[u]);
	if (parent[u] == u) return u;
	return parent[u] = grp(parent[u]);
}

int main() {
	scanf("%d%d", &N, &M);
	for (int i = 0; i <= N; ++i) parent[i] = i;

	int cmd, u, v;
	for (int i = 0; i < M; ++i) {
		scanf("%d%d%d", &cmd, &u, &v);
		if (cmd == 1){
			if (grp(u) == grp(v)) printf("YES\n");
			else printf("NO\n");
		}
		else {
			merge(u, v);
			// merge u, v
		}
	}
}