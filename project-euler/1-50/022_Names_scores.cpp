#include<stdio.h>
#include<time.h>
#define ABS(a) ((a)<0 ? -(a) : (a))
#define MAX(a, b) ((a)>(b)?(a):(b))
#define MIN(a, b) ((a)<(b)?(a):(b))
#define NN 5163
typedef long long int lint;
// lint NEXT[MAXN+1];
int X[10001];

template <class T>
inline void SWAP(T &a, T &b){
    T tmp = a; a = b; b = tmp;
};
struct str {
    char *x;
    int l;
    str(){}
    void init(int len, char *initial){
        l = len;
        this->x = new char[len];
        for (int i =  0 ; i < len ; ++i)
            x[i] = initial[i];
    }
    int calc(){
        int ret = 0;
        for (int i = 0 ; i < l ; ++i)
            ret += x[i] - 'A' + 1;
        return ret;
    }
    void report(){
        for (int i = 0 ; i < l ; ++i)
            printf("%c", x[i]);
        printf("\n");
    }

    bool operator < (const str& rhs){
        int m = MIN(l, rhs.l);
        for (int i = 0 ; i < m ; ++i){
            if (x[i] < rhs.x[i]) return true;
            if (x[i] > rhs.x[i]) return false;
        }
        if (l <= rhs.l) return true;
        return false;
    }
} S[10000];

void qsort(int lo, int hi){
    if (lo >= hi) return;
    int mid = lo;
    for (int i = lo + 1 ; i <= hi ; ++i)
        if (S[i] < S[lo]) 
            SWAP(S[i], S[++mid]);
    SWAP(S[lo], S[mid]);
    qsort(lo, mid-1);
    qsort(mid+1, hi);
}
int main (){
    freopen("p022_names.txt","rt",stdin);
    char c;
    char buf[1024];
    int bufidx;
    for (int i = 0 ; i < NN ; ++i){
        scanf("%c", &c);
        if (c != '\"'){
            printf(" %d] something wrong!", i);
            break;
        }
        bufidx = 0;
        for(;;){ 
            scanf("%c", &c);
            if (c == '\"') break;
            buf[bufidx++] = c;
        }

        // debug info
        if (0){
            buf[bufidx] = 0;
            printf( "%s \n", buf);
        }
        S[i].init(bufidx, buf);

        if (i != NN - 1) scanf("%c", &c); // , seperator
        
    }
    /*
    for (int i = 0 ; i < 5000 ; ++i){
        //printf("[%d] ", i);
        S[i].report();
    }
    return 0;
    */
    qsort(0, NN-1);
    /*
    for (int i = 0 ; i < 5000 ; ++i){
        //printf("[%d] ", i);
        S[i].report();
    }
    return 0;
    */
    long long int ret = 0;
    for (int i = 0 ; i < NN ; ++i){
        if (i == 937){
            S[i].report();
            printf("%d\n", S[i].calc());
        }
        int score = (i + 1) * S[i].calc();
        ret += score;
    }


    printf("%lld \n", ret);
}
