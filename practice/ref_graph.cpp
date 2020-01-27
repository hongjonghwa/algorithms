#include <stdio.h>
#include <iostream>
#include <ctime>
using namespace std;

// INTERSTELLAR : 인터스텔라
// @author jaechun.yoo

typedef long long ll;
//const int INF = 987654321;
const ll INF = 987654321987654321;
const int MAX_N = 100003;
int N, M, K;
ll ans;
ll d[MAX_N][3];		// d[k][s] : k노드에 도달하는데 s번 warp를 사용하여 가는 최단 거리
int visited[MAX_N];

struct Node {
	int idx;
	ll dist;
};

struct ArrList {
	Node *arr, *tmp;
	int size, tail;

	ArrList() {
		arr = new Node[size];
		size = 10;
		tail = 0;
	}
	Node get(int idx) {
		return arr[idx];
	}
	void add(Node edge) {
		if (tail >= size) expand();
		arr[tail++] = edge;
	}
	void expand() {
		size = size * 3 / 2 + 1;
		tmp = new Node[size];
		for (int i = 0; i < tail; ++i) {
			tmp[i] = arr[i];
		}
		delete[] arr;
		arr = tmp;
	}
	int getSize() {
		return tail;
	}
	void clear() {
		delete[] arr;
		size = 10;
		tail = 0;
		arr = new Node[size];
	}
} e[MAX_N];

ll cmin(ll a, ll b) { return a < b ? a : b; }

int que[1000000];
int qhead, qtail;

void bfs(int src, int dest) {
	qhead = qtail = 0;
	que[qtail++] = src;
	d[src][0] = 0;

	int u[3];
	Node nextNode;
	int here, next;
	ll nextDist;
	while (qtail - qhead > 0) {
		here = que[qhead++];

		for (int i = 0; i < e[here].getSize(); ++i) {
			nextNode = e[here].get(i);
			next = nextNode.idx;
			nextDist = nextNode.dist;
			u[0] = u[1] = u[2] = 0;

			//printf("---- next : %d, nextdist : %d\n", next, nextDist);
			if (d[next][0] > d[here][0] + nextDist) {
				d[next][0] = d[here][0] + nextDist;
				u[0] = 1;
			}

			if (K == 1) {
				if (d[next][1] > d[here][0] + 1) {
					d[next][1] = d[here][0] + 1;
					u[1] = 1;
				}
				if (d[next][1] > d[here][1] + nextDist) {
					d[next][1] = d[here][1] + nextDist;
					u[1] = 1;
				}
			} else if (K == 2) {
				if (d[next][1] > d[here][0] + 1) {
					d[next][1] = d[here][0] + 1;
					u[1] = 1;
				}
				if (d[next][1] > d[here][1] + nextDist) {
					d[next][1] = d[here][1] + nextDist;
					u[1] = 1;
				}

				if (d[next][2] > d[here][1] + 1) {
					d[next][2] = d[here][1] + 1;
					u[2] = 1;
				}
				if (d[next][2] > d[here][2] + nextDist) {
					d[next][2] = d[here][2] + nextDist;
					u[2] = 1;
				}
			}

			if (u[0] || u[1] || u[2]) {
				if (next == dest) continue;

				//if (K == 0 && u[0] && d[next][K] >= ans) continue;
				//else if (K == 1 && !u[0] && u[1] && d[next][K] >= ans) continue;
				//else if (K == 2 && !u[0] && !u[1] && u[2] && d[next][K] >= ans) continue;

				que[qtail++] = next;
			}
		}
	}
}

int main() {
	clock_t startTime = clock();
	//freopen("sample_input.txt", "r", stdin);
	//freopen("eval_input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);

	int T, tmp1, tmp2, tmp3;
	int A, B;
	scanf("%d", &T);

	for (int test_case = 1; test_case <= T; ++test_case) {
		scanf("%d%d%d", &N, &M, &K);
		for (int i = 1; i <= N; ++i) {
			e[i].clear();
			visited[i] = 0;
			for (int j = 0; j < 3; ++j) {
				d[i][j] = INF;
			}
		}

		for (int i = 1; i <= M; ++i) {
			scanf("%d%d%d", &tmp1, &tmp2, &tmp3);
			e[tmp1].add({ tmp2, tmp3 });
			e[tmp2].add({ tmp1, tmp3 });
		}
		scanf("%d%d", &A, &B);

		ans = INF;

		bfs(A, B);

		//for (int i = 1; i <= N; ++i) {
		//	for (int j = 0; j < 3; ++j) {
		//		printf("%d ", d[i][j]);
		//	}
		//	printf("\n");
		//}
		//printf("\n");

		printf("#%d %lld\n", test_case, d[B][K]);
	}

	//printf("\nElapsed Time : %.3f\n", (double)(clock() - startTime) / CLOCKS_PER_SEC);
	return 0;
}
