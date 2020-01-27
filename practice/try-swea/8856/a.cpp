#include<stdio.h>
int T,N;
int X[2001];

int median(int a, int b, int c){
    if (a>b){
        if (c>a)
            return a;
        if (b>c)
            return b;
        return c;
    }else{ // b>=a
        if (c>b)
            return  b;
        if (a>c)
            return a;
        return c;
    }
}

bool euler(){
    int e = 0;
    for (int i  = 1 ; i <=N ; ++i){
        if (X[i] == 2) continue;
        if (X[i] == 1) e++;
        else return false;
    }
    return e == 2;
}

int fact(int n){
    int ret = 1;
    for (int i = 2 ; i <= n ;  ++i)
        ret*=i;
    return ret;
}

int main(){
    freopen("input.txt", "rt", stdin);
    scanf("%d", &T);
    for (int i = 1 ; i <= T ; ++i){
        scanf("%d", &N);
        for (int j = 1 ; j <= N  ; ++j) X[i] = 0;
        int t;
        for (int j = 2 ; j <= N  ; ++j){
            scanf("%d", &t);
            X[j]++;
            X[t]++;
        }

    }
}

