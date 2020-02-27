/*
    빠른 답은 4 이상 일 때 부터 짝수...홀수로 출력
    1 : 1
    2 : NO SOLUTION
    3 : NO SOLUTION
    4 : 2 4 1 3
    5 : 2 4 1 3 5
    6 : 2 4 6 1 3 5

    순열+가지치기 연습
*/

#include<stdio.h>
#include<assert.h>

template<class T>
inline void SWAP(T &a, T & b){
    T tmp = a; a = b; b = tmp;
}
bool adjacent(int a, int b){
    int t = a-b;
    if (t > 1) return false;
    if (t < -1) return false;
    return true;
}

void report(int x[], int n){
    for (int i = 0; i < n ;++i)
        printf("%d ", x[i]);
    printf("\n");
}

int perm(int x[], int l, int n){
    if (l == n){        
        for (int i = 0 ; i < n-1 ; ++i){
            int diff = x[i] - x[i+1];
            assert(diff < -1 || diff > 1);
        }
        report(x, n);
        return 1;
    }
    int find = 0;
    for (int i = l ; i < n ; ++i){
        SWAP(x[i], x[l]);
        if (l == 0) find = perm(x, l+1, n);
        else if (!adjacent(x[l], x[l-1])) find = perm(x, l+1, n);
            
        if (find) return find; // break
        SWAP(x[i], x[l]);
    }
    return find;
}

int x[1000000];
int main(){
    int n;
    if (scanf("%d",  &n) != 1) return -1;
    for (int i = 0 ; i < n ; ++i) x[i] = i+1;

    int find = perm(x, 0, n); // n 
    if (find == 0) printf("NO SOLUTION");
}
