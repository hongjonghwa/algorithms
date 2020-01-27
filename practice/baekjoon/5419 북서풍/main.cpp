// https://www.acmicpc.net/problem/5419
#include<stdio.h>
#include<algorithm>
#include<assert.h>
using namespace std;

typedef pair<int, int> PP;
int T, N; // 1 ≤ n ≤ 75000
PP X [75000];
int tmparr[75000];

// 세그먼트트리, 인덱스트리, 펙윅트리
void report(){
    printf("----------------------------\n");
    for (int i = 0 ; i < N ; ++i) printf("%d %d \n", X[i].first, X[i].second);
    printf("----------------------------\n");
}

struct SegTree{ 
    int x[75000 * 4];
    int n;
    void init (int N){
        n = 1;
        while(n < N) n *= 2;
        for (int i = 0 ; i < 2 * n ; ++i) x[i] = 0;
    }
    long long int query(int lo, int hi){ // [ ] 버전
        assert(lo<n && hi<n);
        int l = lo + n;
        int r = hi + n;
        long long int res = 0;
        for ( ; l <= r ; l >>= 1, r >>= 1){
            if (l == r){
                res += x[l];
                break;
            }
            //if (l & 1) res += x[l++];
            //if ( (r & 1) == 0) res += x[r--]; // 주의! 논리연산은 우선순위 낮음 
            if (l%2 == 1) res += x[l++];
            if (r%2 == 0) res += x[r--];
        }

        return res;
    }
    void increase(int p){
        assert(p < n);
        p += n;
        while (p> 0){
            x[p]++;
            p /= 2;
        }
    }
} segTree;

long long int solv(){
    //report();
    sort(X, X + N, [](const PP &a, const PP &b) -> bool {
            return a.second > b.second; // sort by y desc
    });

    int hi = 0;
    for (int i = 0 ; i < N ; ++i) {
        if (i > 0 && X[i].second != X[i-1].second) hi++;
        tmparr[i] = hi;
    }
    for (int i = 0 ; i < N ; ++i) X[i].second = tmparr[i];
    //printf("range lo %d ~ hi %d \n", 0, hi);
    //report();
    sort(X, X + N);

    segTree.init(hi+1);
    long long int ret = 0;
    for (int i = 0 ; i < N ; ++i){
        ret += segTree.query(0, X[i].second);
        segTree.increase(X[i].second);
    }
    return ret;
}
int main(){
    setbuf(stdout, 0);
    scanf("%d", &T);
    for (int t = 0 ; t < T ; ++t){
        scanf("%d", &N);
        for (int i = 0 ; i < N ; ++i){
            scanf("%d %d", &X[i].first, &X[i].second);
        }
        long long int ret = solv();
        printf("%lld\n", ret);
    }
}

