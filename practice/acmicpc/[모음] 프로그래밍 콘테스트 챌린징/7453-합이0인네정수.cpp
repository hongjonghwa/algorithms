#include<cstdio>
#include<algorithm>
#include<cstring>


int N;
int X[4][4000];
int XX[2][4000*4000];

template<class T>
inline void SWAP(T & a, T & b){
    T tmp = a; a = b; b = tmp;
}
void qsrt(int *x, int lo, int hi){
    if (lo >= hi) return;
    int m = lo;
    for (int i = lo + 1 ; i <= hi ; ++i)
        if (x[i] < x[lo]) SWAP(x[i], x[++m]);
    SWAP(x[lo], x[m]);
    qsrt(x, lo, m-1);
    qsrt(x, m+1, hi);
}

int XX_tmp[4000*4000]; // counting sort output array.
void rsrt(int *x, int n){
    int *tmp = XX_tmp;

    int cnt[256]; // bucket 사이즈는 1024 보다 256 이 더 빠르다.
    for (int p = 0 ; p < 32 ; p += 8){
        for (int i = 0 ; i < 256 ; ++i) cnt[i]=0;
        for (int i = 0 ; i < n ; ++i) cnt[ (x[i]>>p) & 0xff ]++;
        for (int i = 1 ; i < 256 ; ++i) cnt[i] = cnt[i-1] + cnt[i];
        for (int i = n-1 ; i >= 0 ; --i) tmp[--cnt[ (x[i]>>p) & 0xff ]]  = x[i];
        int *t = x; x = tmp ; tmp = t; // inplace
    }

}

long long solv(){
    int i, j, k;

    const int abs_max = 1<<28; // offset 
    k = 0;
    for (i = 0 ; i < N ; ++i)
        for (j = 0 ; j < N ; ++j){
            XX[0][k] = abs_max + X[0][i]+X[1][j];
            XX[1][k++] = abs_max - (X[2][i]+X[3][j]) ; // 하나는 마이너스 부호로
        }

    int N2 = N * N;
    //std::sort(XX[0], XX[0] + N2);
    //std::sort(XX[1], XX[1] + N2);
    // qsrt(XX[0], 0, N2-1);
    // qsrt(XX[1], 0, N2-1);
    rsrt(XX[0], N2);
    rsrt(XX[1], N2);

    long long ret = 0;
    i = j = 0;
    while (i < N2 && j < N2){
        if (XX[0][i]==XX[1][j]){ // 같은 수 연속 고려
            int cnt1 = 1, cnt2 = 1;
            while (i+cnt1<N2 && XX[0][i]==XX[0][i+cnt1]) cnt1++;
            while (j+cnt2<N2 && XX[1][j]==XX[1][j+cnt2]) cnt2++;
            ret += (long long)cnt1*(long long)cnt2;
            i += cnt1;
            j += cnt2;
        }else if (XX[0][i] < XX[1][j]) i++;
        else j++;
    }
    
    return ret;
}
int main(){
    if (scanf("%d", &N) != 1) return 1;
    for (int i = 0 ; i < N ; ++i)
        if (scanf("%d%d%d%d", &X[0][i], &X[1][i], &X[2][i], &X[3][i]) != 4) return 1;
    printf("%lld\n", solv());
}