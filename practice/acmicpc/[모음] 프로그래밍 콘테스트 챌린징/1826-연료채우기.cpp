#include<cstdlib>
#include<cstdio>
#include<queue>
#include<vector>
#include<algorithm>

using namespace std;

int N, L, P;
// vector<pair<int, int>> gas_station(10000);
pair<int,int> gas_station[10000];

int solv(){
    int ret = 0;
    // sort(gas_station.begin(), gas_station.begin()+N); // vector 일 때
    sort(gas_station, gas_station+N);
    gas_station[N].first = L, gas_station[N].second = 0; // 마지막 목적지

    priority_queue<int> pq;
    for (int i = 0 ;i <= N ; ++i){
        while (gas_station[i].first > P) {
            if (pq.size()==0) return -1;
            P += pq.top();
            pq.pop();
            ++ret;
        }
        pq.push(gas_station[i].second);
    }

    return ret;
}

int main(){
    if (scanf("%d", &N) != 1) return EXIT_FAILURE;
    for (int i = 0 ; i < N ; ++i)
        if (scanf("%d%d", &gas_station[i].first, &gas_station[i].second) != 2) return EXIT_FAILURE;
    if (scanf("%d%d", &L, &P) != 2) return EXIT_FAILURE;
    int ans = solv();
    printf("%d\n", ans);
}
