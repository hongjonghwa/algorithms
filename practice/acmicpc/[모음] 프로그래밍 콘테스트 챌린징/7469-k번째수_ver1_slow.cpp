#include<cstdio>
#include<algorithm>

unsigned N, M; // 1 ≤ n ≤ 100,000, 1 ≤ m ≤ 5,000
struct node{
	int val; 
	unsigned ord;
} X[100000];
unsigned Q[3][5000];

void solv(){
    std::sort(X, X+N, [](node & a, node & b) { return a.val < b.val; } );
    for (unsigned m =  0 ; m < M ; ++m){
        auto &from = Q[0][m], &to= Q[1][m], &k = Q[2][m];
        unsigned c = 0;
        for (unsigned i = 0 ; i < N ; ++i){
            if (X[i].ord >= from && X[i].ord <= to){
                if (++c == k){
                    printf("%d\n", X[i].val);
                    break;
                }
            }

        }
        
    }
}

int main(){
    if (scanf("%d%d", &N, &M) != 2) return 1;
    for (unsigned i =  0 ; i < N ; ++i){
        if (scanf("%d", &X[i].val) != 1) return 1;
        X[i].ord = i+1;
    }
    for (unsigned i =  0 ; i < M ; ++i)
        if (scanf("%d%d%d", &Q[0][i], &Q[1][i], &Q[2][i]) != 3) return 1;
    solv();
}