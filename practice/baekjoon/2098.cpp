#define INF 987654321
#include<stdio.h>

int N;
int W[16][16];

// exhaustive search
bool visited[16];
int visit(int u){
	int ret = INF;
	bool allvisited = true;
	for (int i = 0 ; i <N ; ++i){
		if (!visited[i]){
			allvisited = false;
			if (i != u && W[u][i]>0){ // 갈 수 있다
				visited[i] = true;
				int tt = visit(i) + W[u][i];
				if (tt < ret) ret = tt;
				visited[i] = false;
			}
		}
	}
	if (allvisited) return W[u][0]; // 기저사례
	return ret;
}

// dp
int cache[16][1<<16];
int dp(int here, int visited, int visitCount){
	int &ret = cache[here][visited];
	if (ret != -1) return ret;

	if (visitCount == N) return ret = W[here][0];
	
	ret = INF;
	for (int next = 0 ; next < N ; ++next){
		if (visited & (1<<next) || W[here][next] == 0) continue;
		int tt = W[here][next] + dp(next, visited | (1<<next), visitCount + 1);
		if (tt < ret) ret = tt;
	}
	return ret;
	
}

int main(){
	scanf("%d", &N);
	for (int i = 0 ; i < N ; ++i)
		for (int j = 0 ; j < N ; ++j)
			scanf("%d", &W[i][j]);

	// exhaustive search
	//printf ("%d\n", visit(0));

	// dp
	for (int i = 0 ; i < N ; ++i)
		for (int j = 0 ; j < (1<<N) ; ++j)
			cache[i][j] = -1;
	printf ("%d\n", dp(0, 1, 1));


	return 0;
}
