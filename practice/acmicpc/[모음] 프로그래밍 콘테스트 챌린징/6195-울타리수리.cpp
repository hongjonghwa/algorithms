#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include <queue>

using namespace std;

int N;
int X[20000];


long long int solv(){
    long long int ret = 0;
    priority_queue<long long int> pq;
    for (int i = 0 ; i < N ; ++i)
        pq.push(-X[i]);

    while (pq.size() > 1){
        long long int cost = -pq.top();
        pq.pop();
        cost += -pq.top();
        pq.pop();

        ret += cost;
        pq.push(-cost);
    }
    return ret;
}

int main(){
    if (scanf("%d", &N) != 1) return EXIT_FAILURE;
    for (int i = 0 ; i < N ; ++i)
        if (scanf("%d", &X[i]) != 1) return EXIT_FAILURE;
    printf("%lld\n", solv());
}
