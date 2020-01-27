#include<iostream>
#include<cstdio>
#include<vector>
//#include<priority_queue>
#include<queue>

using namespace std;

int MAX_N = 10000;
int MAX_M = 50000;
int INF = 987654321;

int T,N,M,K;
int start,end,time1;	
vector<pair<int,int> > adj[10001];
//vector<vector<int> > adj;
//vector<vector<int>> adj
vector<int> dijstra(int src){
	vector<int> dist(N+1, INF);
	dist[src] = 0;
	priority_queue<pair<int,int> > pq;
	pq.push(make_pair(0,src));
	while (!pq.empty()){
		int cost = -pq.top().first;
		int here = pq.top().second;
		pq.pop();
		for (int i = 0 ; i < adj[here].size() ; ++i){
			int there = adj[here][i].first;
			int nextDist = cost + adj[here][i].second;
			if (nextDist < dist[there]){
				pq.push(make_pair(-nextDist, there));
				dist[there] = nextDist;
			}
		}
	}
	return dist;
}

int main(){
	ios::sync_with_stdio(false);
	freopen("sample_input.txt","rt",stdin);
	//freopen("eval_input.txt","rt",stdin);
	cin >> T;
	for (int t=0 ; t < T ; ++t){
		cin >> N >> M;
		for (int n = 1 ; n <= N ; ++n) adj[n].clear();
		for (int m = 0 ; m < M ; ++m){
			cin >> start >> end >> time1;
			adj[start].push_back(make_pair(end,time1));
		}
		/* adj 확인 */
		cout << "#" << t << endl;
		for (int n = 1 ; n <= N ; ++n){
			cout << n << " -";
			for (int i = 0 ; i < adj[n].size() ; ++i){
				cout << " "
					<< adj[n][i].first << "(" 
					<< adj[n][i].second << ")";
			}
			cout << endl;
		}
		vector<int> dist = dijstra(1);
		for (int i =0 ; i < dist.size() ; ++i){
			cout << "[" << i << "] " << dist[i] << endl;
		}
		cout << endl;
		cout << "#" << t+1 << " " << dist[N] <<  endl;
	}

	return 0;

}
