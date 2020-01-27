#include<stdio.h>
#include<algorithm>
using namespace std;
int N, M; // N ≤ 300,000, 3 ≤ M ≤ 10e9
typedef pair<int, int> PP;
PP X[600000];
int len = 0;

int main(){
    scanf("%d%d", &N, &M);
    for (int i = 0 ; i < N ; ++i){
        int from, to;
        scanf("%d%d", &from, &to);
        if (to < from) {
            X[len++] = PP(to, 1); // 라인시작
            X[len++] = PP(from, -1); // 라인 종료
        }
    }
    sort(X, X+len, [] (PP & a, PP & b) ->bool { 
            if (a.first == b.first) return a.second > b.second;
            return a.first < b.first;
    });


    int count = 0, start;
    long long int ret = 0;
    for (int i = 0 ; i < len ; ++i){
        int delta = X[i].second;
        int x = X[i].first;
        if (count == 0) start = x;
        count += delta;
        if (count == 0) ret += (x - start);
    }
    printf("%lld\n", ret*2+M);
}


