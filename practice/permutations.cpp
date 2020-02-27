#include<stdio.h>

template<class T>
inline void SWAP(T &a, T & b){
    T tmp = a; a = b; b = tmp;
}


void report(int x[], int n){
    for (int i = 0; i < n ;++i)
        printf("%d ", x[i]);
    printf("\n");
}

int perm(int x[], int l, int n){
    if (l == n){
        report(x, n);
        return 1;
    }
    int ret = 0;
    for (int i = l ; i < n ; ++i){
        SWAP(x[i], x[l]);
        ret += perm(x, l+1, n);
        SWAP(x[i], x[l]);
    }
    return ret;
}

int main(){
    int x[] = { 1,2,3,4,5,6,7,8,9,10 };
    int n;
    while (scanf("%d",  &n) == 1){
        int cnt = perm(x, 0, n); // n 
        printf("Count is %d\n", cnt);
    }
}
