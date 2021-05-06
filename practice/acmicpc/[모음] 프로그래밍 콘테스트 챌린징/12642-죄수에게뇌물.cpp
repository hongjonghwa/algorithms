#include<cstdio>
#include<cstring>
int N, P, Q; // 1 ≤ P ≤ 10000 , 1 ≤ Q ≤ 100
int X[102];
int D[101][101];
int bribe(int l, int u){
    if (l+1 >= u) return 0;
    if (D[l][u] != -1) return D[l][u];

    int &ret = D[l][u];
    ret = 987654321;
    for (int i = l + 1 ; i < u; ++i){
        int t = X[u] - X[l] -2;
        t += bribe(l, i);
        t += bribe(i, u);
        if (ret > t) ret = t;
    }
    return ret;
}

int solv(){
    X[0] = 0, X[Q + 1] = P + 1;
    memset(D,-1, sizeof(D));
    return bribe(0, Q+1);
}

int main(){
    if (scanf("%d", &N) != 1) return 1;
    for (int t = 0 ; t < N ; ++t){
        if (scanf("%d%d", &P, &Q) != 2) return 1;
        for (int i = 1 ; i <= Q ; ++i)
            if (scanf("%d", &X[i]) != 1) return 1;

        int ans = solv();
        printf("Case #%d: %d\n", t+1, ans);
    }
}