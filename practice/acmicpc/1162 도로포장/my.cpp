#include<iostream>
#include<cstdio>
#include<vector>
//#include<priority_queue>
#include<queue>

using namespace std;

int MAX_N = 10000;
int MAX_M = 50000;
int INF = 987654321;

int T,N,M;
int t;
int K = 1;
int start,end,time1;	
vector<pair<int,int> > adj[10001];
//vector<vector<int> > adj;
//vector<vector<int>> adj
vector<int> dijstra(int src){
	vector<int> dist[K+1];
	for (int k = 0 ; k <= K ; ++k) dist[k] = vector<int>(N+1,INF);
	//vector<int> dist(N+1, INF);
	dist[K][src] = 0;
	for (int k = K ; k>=0 ; --k) dist[k][src] = 0;
	// cost, nextnode, k
	priority_queue<pair<int,pair<int,int > > > pq;
	pq.push(make_pair(0,make_pair(src,K)));
	while (!pq.empty()){
		int cost = -pq.top().first;
		int here = pq.top().second.first;
		int remaink = pq.top().second.second;
		pq.pop();
		for (int i = 0 ; i < adj[here].size() ; ++i){
			int there = adj[here][i].first;
			int nextDist = cost + adj[here][i].second;
			/*
			if (t==1 && here == 1&& there == 2) 
				cout <<"########"<<nextDist << ":" << remaink << endl;
				*/
			if(remaink>0){ // 도로 포장 
				//cout <<"########"<<cost << ":" << dist[remaink-1][there] << endl;
				if (cost < dist[remaink-1][there]){
					pq.push(make_pair(-cost, make_pair(there, remaink-1)));
					dist[remaink-1][there] = cost;
					for(int k = 0 ; k < remaink-1 ; ++k){
						dist[k][there] = min(cost, dist[k][there]);
						/*
						if (t==1 && here == 1&& there == 2) 
							cout <<"##111###"<<k <<":" <<cost <<endl;
							*/
					}
				}
			}
			if (nextDist < dist[remaink][there]){
				pq.push(make_pair(-nextDist, make_pair(there, remaink)));
				dist[remaink][there] = nextDist;
				for(int k = 0 ; k < remaink ; ++k) {
					dist[k][there] = min(nextDist, dist[k][there]);
					/*
					if (t==1 && here == 1&& there == 2) 
						cout <<"##222###"<<k <<":" <<cost <<endl;
						*/
				}
			}
		}
	}
/* 
	for (int k = 0 ; k <=K ; ++k){
		cout << "K : " << k << endl;
		for (int i =0 ; i < dist[k].size() ; ++i){
			cout << "[" << i << "] " << dist[k][i] << endl;
		}
		cout << endl;
	}
	 */
	return dist[0];
}

int main(){
	ios::sync_with_stdio(false);
	freopen("sample_input.txt","rt",stdin);
	//freopen("eval_input.txt","rt",stdin);
	cin >> T;
	for (t=0 ; t < T ; ++t){
		cin >> N >> M;
		for (int n = 1 ; n <= N ; ++n) adj[n].clear();
		for (int m = 0 ; m < M ; ++m){
			cin >> start >> end >> time1;
			adj[start].push_back(make_pair(end,time1));
		}
		/* adj 확인 */
		/*
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
		*/
		vector<int> dist = dijstra(1);
		/*
		for (int i =0 ; i < dist.size() ; ++i){
			cout << "[" << i << "] " << dist[i] << endl;
		}
		cout << endl;
		*/
		cout << "#" << t+1 << " " << dist[N] <<  endl;
		//if (t==1) break;
	}

	return 0;

}
