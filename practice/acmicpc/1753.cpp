#define _CRT_SECURE_NO_WARNINGS
#define SWAPT(T, a, b) { T t = a ;  a = b ; b = t; }
#define INF 987654321
#include<stdio.h>
#include<iostream>

using namespace std;

int V, E, K;
int minDist[20001];

struct Node{
	int dist, here;
	Node* next;
} freenode[300000];

Node* head[20001];

struct PP {
	int first, second;
	PP(int f, int s) :first(f), second(s) {};
	PP() {};
};

struct PQ {
	PP x[300001];
	int n;
	void push(PP pp) {
		x[++n] = pp;
		int p; // 올라갈 부모
		for (int i = n; i > 1 && x[p=i/2].first > x[i].first; i = p)
			SWAPT(PP, x[i], x[p])
		//shift
	}
	PP pop() {
		PP t = x[1];
		// shift down
		x[1] = x[n--];
		int c; //child ,, 다음 내려갈 위치 
		for (int i = 1 ; (c=2*i) <= n ; i = c){
			if (c + 1 <= n  &&  x[c+1].first < x[c].first) c++;
			if (x[i].first <= x[c].first) break;
			SWAPT(PP, x[i], x[c])
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
void report(){
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
		//scanf("%d%d%d", &u, &v, &w);
		cin >> u >> v >> w;
		//printf("%d %d %d \n", u, v, w);
		f->dist = w;
		f->here = v;
		f->next = head[u];
		head[u] = f;
		f++;
	}
	//report();

	//dijkstra
	for (int i = 1; i <= V; ++i) minDist[i] = INF;
	minDist[K] = 0;
	pq.push(PP(0, K));
	while (pq.n) {
		PP top = pq.pop();
		int curdist = top.first;
		int here = top.second;

		if (curdist > minDist[here]) continue;

		Node *h = head[here];
		while (h) {
			int there = h->here;
			int nextdist = h->dist + curdist;
			if (nextdist < minDist[there]) {
				minDist[there] = nextdist;
				pq.push(PP(nextdist, there));
			}
			//printf("-> %d[%d]", h->here, h->dist);
			h = h->next;
		}
	}

	for (int i = 1; i <= V; ++i) {
		//if (minDist[i] >= INF) printf("INF\n");
		//else printf("%d\n", minDist[i]);
		if (minDist[i] >= INF) cout << "INF" << endl;
		else  cout << minDist[i] << endl;
	}
	

}