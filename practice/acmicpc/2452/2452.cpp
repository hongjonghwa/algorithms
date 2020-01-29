#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<vector>
#include<queue>

using namespace std;

int M, N;
int data[101][101];
int INF = 987654321;
void fillno(int i, int j, int idx){
	int here = data[i][j];
	data[i][j] = idx;
	if (i-1 >= 0 && data[i-1][j] == here) fillno(i-1,j,idx);
	if (i+1 < M && data[i+1][j] == here) fillno(i+1,j,idx);
	if (j-1 >= 0 && data[i][j-1] == here) fillno(i,j-1,idx);
	if (j+1 < N && data[i][j+1] == here) fillno(i,j+1,idx);
}


vector<vector<int> > adj;
int bfs(int v){ // return maximum node;
	vector<int > dist(adj.size(), INF);
	queue<int> q;
	dist[v] = 0;
	q.push(v);

	while (!q.empty()){
		int here = q.front();
		q.pop();
		for (int i = 0 ; i < adj[here].size(); ++i){
			int there = adj[here][i];
			if (dist[there] > dist[here]+1){
				dist[there] = dist[here]+1;
				q.push(there);
			}
		}
	}

	int ret = 0;
	for (int i = 1 ; i < dist.size(); ++i ) ret = max(ret, dist[i]);
	return ret;
}

int getMinimumRadius(){
    //int start = adj.size()/2;
    int start = -data[M/2][N/2];
    vector<int> dist(adj.size(), -1);
    queue<int> q;
    q.push(start);
    //bool updated = true;
    int ret = INF;
    while(!q.empty()){
        int here = q.front();
        q.pop();
        if (dist[here] == -1) dist[here] = bfs(here);
        if (dist[here]>ret+0) continue;
        ret = min(ret, dist[here]);
        for (int i = 0 ; i < adj[here].size() ; ++i){
            int there = adj[here][i];
            if (dist[there] == -1){
                q.push(there);
            }
        }
    }
    return ret;
}

int solv(){
	memset(data,0,sizeof(data));

	cin >> M >> N;
	for (int i = 0; i < M ; ++i)
		for (int j = 0; j < N ; ++j)
			cin >> data[i][j];

	int idx = 0;
	for (int i = 0; i < M ; ++i)
		for (int j = 0; j < N ; ++j)
			if (data[i][j] >=0) fillno(i,j, --idx);

	//make graph
	int V = -idx;
	vector<pair<int,int> > edges;
	for (int i = 0; i < M ; ++i)
		for (int j = 0; j < N ; ++j){
			int here = -data[i][j];
			int right = -data[i+1][j];
			int bottom = -data[i][j+1];
			if (here != right){
				int u = here, v = right;
				if (u>v) swap(u,v);
				if (u!=0) edges.push_back(make_pair(u,v));
			}
			if (here != bottom){
				int u = here, v = bottom;
				if (u>v) swap(u,v);
				if (u!=0) edges.push_back(make_pair(u,v));
			}
		}
	
	sort(edges.begin(), edges.end());
	edges.erase(unique(edges.begin(), edges.end()), edges.end());

	adj = vector<vector<int > >(V+1, vector<int>());
	for (int i = 0 ; i < edges.size(); ++i){
		int u = edges[i].first, v = edges[i].second;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	// run bfs
	/*
	int ret = INF;
	for (int i = 1 ; i<= V ; ++i){
		int tmp = bfs(i);
		cout << "     " << i << "    " << tmp << endl;
		ret = min(ret, tmp);
	}
	return ret;
	*/
	return getMinimumRadius();
}

int main(){
	ios::sync_with_stdio(false);
	cout << solv();
	return 0;
}