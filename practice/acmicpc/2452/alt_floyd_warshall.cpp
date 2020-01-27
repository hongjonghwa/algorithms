#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<vector>

using namespace std;

int T, M, N;
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

	/*
	for (int i = 0; i < M ; ++i){
		for (int j = 0; j < N ; ++j)
			cout << data[i][j] << " ";
		cout << endl;
	}
	*/
	
	//Floyd-warshall
	int V = -idx;
	cout << "V:" << V << "\t";
	vector<vector<int> > adj(V+1, vector<int>(V+1, INF) );
	for (int i = 1 ; i <= V ; ++i ) adj[i][i] = 0;
	for (int i = 0; i < M ; ++i)
		for (int j = 0; j < N ; ++j){
			int here = -data[i][j];
			int right = -data[i+1][j];
			int bottom = -data[i][j+1];
			if (here != right) adj[here][right] = adj[right][here] = 1;
			if (here != bottom) adj[here][bottom] = adj[bottom][here] = 1;
		}
	/*
	for ( int k = 1; k <= V ; ++k)
		for (int i = 1 ; i<= V ; ++i)
			for (int j = 1 ; j <= V ; ++j)
				adj[i][j] = min(adj[i][j], adj[i][k] + adj[k][j]);
	*/
	/* method 1 */
	/*
	int ret = 0;
	for (int i = 1 ; i<= V ; ++i)
		for (int j = i+1 ; j <= V ; ++j)
			ret = max(ret, adj[i][j]);
	return (ret+1)/2;
	*/

	/* method 2 */
	int ret = INF;
	int longest;
	for (int i = 1 ; i<= V ; ++i){
		longest = 0;
		for (int j = 1 ; j <= V ; ++j){
			longest = max(longest, adj[i][j]);
		}
		//cout << longest << endl;
		ret = min(ret, longest);
	}
	return ret;
}

int main(){
	ios::sync_with_stdio(false);
	//freopen("sample_input.txt","rt",stdin);
	freopen("eval_input.txt","rt",stdin);
	cin >> T;
	for (int i = 1 ; i <= T ; ++i){
		cout << "#" << i << " " << solv() << endl;
		//break;
	}
	return 0;
}
