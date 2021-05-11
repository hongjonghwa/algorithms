#include<cstdlib>
#include<cstdio>
#include<ctime>
#include<algorithm>
#include<cstring>

int MAX_ELEM = 100; // 28bit!
int MIN_ELEM = 0;
int N = 50;

int X[10000*10000];
int X_tmp[10000*10000];
int X1[10000*10000];

template<class T>
inline void SWAP(T & a, T & b){
    T tmp = a; a = b; b = tmp;
}

void isrt(int *x, int n) {
    int i, j;
    int t;
	for (i = 1; i < n; i++) {
		t = x[i];
		for (j = i; j > 0 && x[j-1] > t; j--)
			x[j] = x[j-1];
		x[j] = t;
	}
}
void qsrt(int *x, int lo, int hi){
    if (lo >= hi) return;
    int m = lo;
    for (int i = lo + 1 ; i <= hi ; ++i)
        if (x[i] < x[lo]) SWAP(x[++m],x[i]);
    SWAP(x[lo], x[m]);

    qsrt(x, lo, m-1);
    qsrt(x, m+1, hi);
}
/*
 * 
// counting  from SWEA
void calculateDigitNumber()
{
    for (int i = 0; i < N; i++)
    {
        cnt[arr[i]]++;
    }
 
    for (int i = 1; i < MAX_DIGIT; i++)
    {
        cnt[i] = cnt[i-1] + cnt[i];
    }
}
 
void executeCountingSort()
{
    for (int i = N-1; i >= 0; i--)
    {
        sortedArr[--cnt[arr[i]]] = arr[i];
    }
}
 
 *
 */
void counting_sort(int *x, int n, int *tmp){
    int cnt[MAX_ELEM+1];
    for (int i = 0 ; i < MAX_ELEM+1 ; ++i) cnt[i]=0;
    for (int i = 0 ; i < n ; ++i) cnt[x[i]]++;
    for (int i = 1 ; i < MAX_ELEM+1 ; ++i) cnt[i] = cnt[i-1] + cnt[i];
    for (int i = n-1 ; i >= 0 ; --i) tmp[--cnt[x[i]]]  = x[i];
    // 
    for (int i = 0 ; i < n ; ++i) x[i] = tmp[i]; // inplace 의 경우
}

void radix_sort(int *x, int n, int *tmp){
    int cnt[256]; // bucket 사이즈는 1024 보다 256 이 더 빠르다.
    for (int p = 0 ; p < 32 ; p += 8){
        for (int i = 0 ; i < 256 ; ++i) cnt[i]=0;
        for (int i = 0 ; i < n ; ++i) cnt[ (x[i]>>p) & 0xff ]++;
        for (int i = 1 ; i < 256 ; ++i) cnt[i] = cnt[i-1] + cnt[i];
        for (int i = n-1 ; i >= 0 ; --i) tmp[--cnt[ (x[i]>>p) & 0xff ]]  = x[i];

        // for (int i = 0 ; i < n ; ++i) SWAP(x[i], tmp[i]); // inplace 의 경우
        int *t = x; x = tmp ; tmp = t; // inplace
    }
    // for (int i = 0 ; i < n ; ++i) SWAP(x[i], tmp[i]); // swap array 가 홀수 횟수 일 때
}

void my_sort(){
    // qsrt(X, 0, N-1);
    // counting_sort(X, N, X_tmp);
    radix_sort(X, N, X_tmp);
}

void report(){
    printf("My sorting STL sorting \n");
    printf("========== =========== \n");
    for (int i = 0 ; i < N ; ++i)
        printf("%10d  %10d  %10d\n", X[i], X1[i], X_tmp[i]);
        // printf("%10d  %10d\n", X[i], X1[i]);
}

int main(){
    // printf("RAND_MAX is %d\n", RAND_MAX);
    srand(time(NULL));

    if (0){ // big
        MAX_ELEM = (1<<28)-1; // 28bit!
        MIN_ELEM = -MAX_ELEM;
        N = 10000000; // 1e7
    }
    if (0){ // small
        MAX_ELEM = 5, MIN_ELEM = -5, N = 20; // smaller
    }
    if (0) { // counting sort
        MAX_ELEM = 255;
        MIN_ELEM = 0;
        N = 10000000; // 1e7
    }
    if (1){ // positive, radix sort
        MAX_ELEM = (1<<30)-1; // 30bit!
        MIN_ELEM = 0;
        N = 10000000; // 1e7
    }
    for (int i = 0  ; i < N ; ++i)
        X[i] = rand() % (MAX_ELEM-MIN_ELEM+1) + MIN_ELEM;
    memcpy(X1, X, sizeof(X[0])*N); 
    // report();

    long long int clk;
    clk = clock();
    my_sort();
    printf("My sort  -> %f\n", (double)(clock()-clk) / CLOCKS_PER_SEC);

    // stl sort
    clk = clock();
    std::stable_sort(X1, X1 + N);
    printf("STL sort -> %f\n", (double)(clock()-clk) / CLOCKS_PER_SEC);

    bool okay = true;
    for (int i = 0 ; i < N ; ++i)
        if (X[i] != X1[i]){
            okay = false;
            break;
        }
    if (okay) printf("Okay!\n");
    else {
        printf("Failed!\n");
        if (N<=50) report();
    }
}

