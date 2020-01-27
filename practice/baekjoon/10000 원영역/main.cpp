#include<stdio.h>
#include<algorithm>
#include<stack>
using namespace std;
int N; // 1 ≤ N ≤ 300,000

typedef pair<long long int, long long int > PP;
typedef pair<long long int, pair<int, int > > TT;

PP X[300000];

int main(){
    scanf("%d" , &N);
    int l = 0;
    for (int i = 1; i <= N ; ++i){
        int x, r;
        scanf("%d%d", &x, &r);
        X[l++].first = (long long int)x - r;
        X[l++].second = (long long int)x + r;
    }
    sort(X, X + l, [] (PP &a, PP &b) -> bool{ 
            if (a.first == b.first) return a.second > b.second;
            return a.first < b.first;
    }); // X 는 시작점으로 정리되어있다.
    stack<PP> s;
    for (int i = 0 ; i < l ; ++i){
        
    }

}
