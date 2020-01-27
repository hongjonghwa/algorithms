#define _CRT_SECURE_NO_WARNINGS
#define SWAPT(T, a, b) { T t = a ;  a = b ; b = t; }
#define INF 987654321
#include<stdio.h>
#include<iostream>

using namespace std;

int V, E, K;
int minDist[10001][21];

struct Node {
	int dist, here;
	Node* next;
} freenode[100000];

Node* head[10001];

struct PPP {
	int first, second, third;
	PPP(int f, int s, int t) :first(f), second(s), third(t) {};
	PPP() {};
};

struct PQ {
	PPP x[200001];
	int n;
	void push(PPP pp) {
		x[++n] = pp;
		int p; // 올라갈 부모
		for (int i = n; i > 1 && x[p = i / 2].first > x[i].first; i = p)
			SWAPT(PPP, x[i], x[p])
			//shift
	}
	PPP pop() {
		PPP t = x[1];
		// shift down
		x[1] = x[n--];
		int c; //child ,, 다음 내려갈 위치 
		for (int i = 1; (c = 2 * i) <= n; i = c) {
			if (c + 1 <= n  &&  x[c + 1].first < x[c].first) c++;
			if (x[i].first <= x[c].first) break;
			SWAPT(PPP, x[i], x[c])
		}
		return t;
	}
	void report() {
		for (int i = 1; i <= n; ++i) {
			printf(" -> %d(%d)", x[i].first, x[i].first);
		}
		printf("\n");
	}
	PQ() { n = 0; }
} pq;

// list report
void report() {
	for (int i = 1; i <= V; ++i) {
		printf("%d :", i);
		Node *h = head[i];
		while (h) {
			printf("-> %d[%d]", h->here, h->dist);
			h = h->next;
		}
		printf("\n");

	}
}

int main() {
	ios::sync_with_stdio(false);
	//scanf("%d%d%d", &V, &E, &K);
	cin >> V >> E >> K;

	for (int i = 1; i <= V; ++i) head[i] = 0;

	// list 
	Node* f = freenode;
	int u, v, w;
	for (int i = 0; i < E; ++i) {
		cin >> u >> v >> w;
		
		f->dist = w;
		f->here = v;
		f->next = head[u];
		head[u] = f++;

		f->dist = w;
		f->here = u;
		f->next = head[v];
		head[v] = f++;
	}
	//report();

	//dijkstra
	for (int i = 1; i <= V; ++i)
		for (int j = 0; j <= K ; ++j)
			minDist[i][j] = INF;

	minDist[1][0] = 0;
	pq.push(PPP(0, 1, 0));

	int answer;
	while (pq.n) {
		PPP top = pq.pop();
		int dist = top.first;
		int here = top.second;
		int jump = top.third;

		if (dist > minDist[here][jump]) continue;
		if (here == V) {
			answer = dist;
			break;
		}


		Node *h = head[here];
		while (h) {
			int there = h->here;
			int nextdist = h->dist + dist;
			if (nextdist < minDist[there][jump]) {
				minDist[there][jump] = nextdist;
				pq.push(PPP(nextdist, there, jump));
				if (jump < K) {
					pq.push(PPP(dist, there, jump + 1));
				}
			}
			//printf("-> %d[%d]", h->here, h->dist);
			h = h->next;
		}
	}

	printf("%d\n", answer);

	return 0;
}