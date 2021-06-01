#include<stdio.h>
int T,N;
int X[200000];

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

int naive(){
    int t[200000];
    int center = N-1;
    for (int i = N - 2 ; i >= 0 ; --i){
        int s = center-i, e = center+i;
        for  (int j = s ; j <= e ; ++j)
            t[j] = median(X[j-1],X[j],X[j+1]);
        for (int j = s; j <= e ;  ++j)
            X[j] = t[j];
        /*
        for (int j = s; j <= e ;  ++j)
            printf("%d ", X[j]);
        printf("\n");
        */
    }
    return X[center];
}

int main(){
    freopen("input.txt", "rt", stdin);
    scanf("%d", &T);
    for (int i = 1 ; i <= T ; ++i){
        scanf("%d", &N);
        int e = 2*N-1;
        for (int j = 0 ; j < e ; ++j)
            scanf("%d", &X[j]);

        /*        
        for (int j = 0; j < e ;  ++j)
            printf("%d ", X[j]);
        printf("\n");
        */

        printf("#%d %d\n",  i, naive());

    }
}

