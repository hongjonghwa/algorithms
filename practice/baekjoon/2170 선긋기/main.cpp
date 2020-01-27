#include<stdio.h>
int N; // 1 ≤ N ≤ 1,000,000
struct Pair{
    int first, second;
    bool operator< (const Pair & rhs) const { 
        return first < rhs.first || (first == rhs.first && second < rhs.second);
    }
} X[2000000];

template<class T>
inline void SWAP(T & a ,T & b){
    T tmp = a; a = b; b = tmp;
}


void qsort(int lo, int hi){
    if (lo >= hi) return;
    int m = lo;
    for (int i = lo + 1 ; i <= hi ; ++i)
        if (X[i] < X[lo]) 
            SWAP(X[i], X[++m]);
    SWAP(X[lo], X[m]);
    qsort(lo, m-1);
    qsort(m+1, hi);
}
int main(){
    scanf("%d", &N);
    for (int i = 0 ; i < N ; ++i){
        scanf("%d%d", &X[i*2].first, &X[i*2+1].first);
        X[i*2].second = 1;
        X[i*2+1].second = -1;
    }
    N *= 2;
    qsort(0, N-1);

    int count = 1;
    int ret = 0;
    for (int i = 1 ; i < N ; ++i){
        if (count > 0) ret += X[i].first - X[i-1].first;
        count += X[i].second;
    }

    printf("%d\n", ret);
}

