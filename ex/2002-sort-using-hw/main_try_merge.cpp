/*
 * external sorting ??
 * merge_sort + isort 결합 : 로직이 복잡해서 더 느려짐 .
 * 1024 개씩 나누어서 손실 소팅을 하는 것은 이득이 없다.
 */
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<algorithm>
#include<time.h>
#include <functional>


#define SIZE 1048576
#define IDX 2048


void my_sort(unsigned int DATA[SIZE]);

unsigned int DATA[SIZE];
unsigned int BAK_DATA[SIZE];
unsigned int idx1[IDX], idx2[IDX];

long long int SCORE = 0;

static unsigned int g_seed = 1;
inline unsigned int fastrand(){
    g_seed = (214013*g_seed+2531011);
    return (g_seed>>16)&0xFFFFFFF;
}

// 오름차순
int comp_s (const void * p1, const void * p2)
{
    short i1 = *(short*) p1, i2 = *(short*) p2;
    if (i1 > i2) return 1;
    if (i1 == i2) return 0;
    return -1;
}

void hw_sort(short DATA[1024]){
    clock_t clk = clock();
    qsort(DATA, 1024, sizeof(short), comp_s);
    SCORE -= clock() - clk;
}

int main(){
    clock_t start_clk = clock(), clk;

    for (int i = 0 ; i < IDX ; ++i){
        idx1[i] = fastrand () % 65536;
        idx2[i] = fastrand () % 65536;
    }
    for (int i = 0 ; i < SIZE ; ++i){
        BAK_DATA[i] = DATA[i] = (idx1[fastrand()%IDX] << 16) | idx2[fastrand()%IDX];
    }
    std::sort(BAK_DATA , BAK_DATA+SIZE, std::greater<unsigned int>());
    
    clk = clock();
    my_sort(DATA);
    SCORE += clock() - clk;
    
    printf("Score: %lld\n", SCORE * 1000 / CLOCKS_PER_SEC);
    for (int i = 0 ; i < SIZE ; ++i){
        assert(BAK_DATA[i] == DATA[i]);
    }

    clock_t total_duration = clock()-start_clk;
    printf("Execution time: %f\n", (double)total_duration / CLOCKS_PER_SEC);
    assert(total_duration < 2 * CLOCKS_PER_SEC); // 2 sec 제한
}

/* My implementation */
int comp_ui(const void* p1, const void* p2)
{ 
    unsigned int i1 = *(unsigned int*) p1;
    unsigned int i2 = *(unsigned int*) p2;
    if (i1 > i2) return 1;
    if (i1 == i2) return 0;
   
    return -1;
   /* or simply: return i1 - i2; */
}
int comp_ui_gt(const void* p1, const void* p2){
    return -comp_ui(p1,p2);
}

template <class T>
inline void SWAP(T & a, T & b){
    T tmp = a;
    a = b;
    b = tmp;
}

void isort(unsigned int * x, int size){
    int i, j;
    unsigned int t;
    for (i = 1; i < size ; ++i){
        t = x[i];        
        for (j = i ; j > 0 && x[j-1] < t ; --j){
            x[j] = x[j-1];
        }
        x[j] = t;
    }
}

void qsort1(unsigned int * x, int l, int u){
    if (l >= u) return;
    int m = l;
    for (int i = l + 1 ; i <= u ; ++i){
        if (x[i] > x[l]){
            SWAP(x[i], x[++m]);
        }
    }
    SWAP(x[l],x[m]);
    qsort1(x, l, m-1);
    qsort1(x, m+1, u);

}

void qsort2(unsigned int * x, int l, int u){
    if (u-l < 20) return;
    int m = l;
    for (int i = l + 1 ; i <= u ; ++i){
        if (x[i] > x[l]){
            SWAP(x[i], x[++m]);
        }
    }
    SWAP(x[l],x[m]);
    qsort1(x, l, m-1);
    qsort1(x, m+1, u);

}
unsigned int buf[1024*1024];

void hw_sort_wrap (unsigned int x[SIZE], int l, int u){
    
    short tmp[1024];
    unsigned int bckup[1024];
    for (int i = 0 ; i < 1024 ; ++i) bckup[i] = x[i+l];
    for (int i = 0 ; i < 1024 ; ++i) {
        tmp[i] = ((bckup[i] >> 17) & (~1023)) + i;
    }
    hw_sort(tmp);

    for (int i = 0 ; i < 1024 ; ++i){
        int idx =  1023 - (tmp[i] & 1023) ;// reverse
        x[i+l] = bckup[idx];
    }
    // for (int i = 0 ; i < 10 ; ++i) printf("%u ", x[i+l]); printf("\n");

    isort(x + l, 1024);

}
void merge_sort(unsigned int x[SIZE], int l, int u){
    int c = u-l+1;
    if (c == 1024) {
        hw_sort_wrap(x, l, u);
        return;
    }
    if (c == 1) return;
    // printf( "%d - %d (%d) \n", l, u, c);
    int m  = ( l + u ) / 2;
    merge_sort(x, l, m);
    merge_sort(x, m+1, u);

    int i = l, j = m+1, k = l;
    while (i <= m && j <= u){
        if (x[i] > x[j]) buf[k++] = x[i++];
        else buf[k++] = x[j++];
    }

    while (i <= m ) buf[k++] = x[i++];
    while (j <= u ) buf[k++] = x[j++];

    for (register int i = l ; i <= u ; ++i)
        x[i] = buf[i];
}

void my_sort(unsigned int DATA[SIZE]){  

    // hw_sort testing
    /*
    short test[1024] = {  10,20,30,50,40, 30,50,20,10,30 };
    for (int i = 0 ; i < 10 ; ++i) printf("%u ", test[i]); printf("\n");
    hw_sort(test);
    for (int i = 1014 ; i < 1024 ; ++i) printf("%u ", test[i]); printf("\n");
    */
    
    // my_sort testing
    /*
    unsigned int test[10];

    for (int i = 0 ; i < 10 ; ++i) test[i] = DATA[i];
    for (int i = 0 ; i < 10 ; ++i) printf("%u ", test[i]); printf("\n");
    isort(test, 10);
    for (int i = 0 ; i < 10 ; ++i) printf("%u ", test[i]); printf("\n");

    for (int i = 0 ; i < 10 ; ++i) test[i] = DATA[i];
    for (int i = 0 ; i < 10 ; ++i) printf("%u ", test[i]); printf("\n");
    qsort1(test, 0,9);
    for (int i = 0 ; i < 10 ; ++i) printf("%u ", test[i]); printf("\n");
    */

    merge_sort(DATA, 0, 1024*1024-1);
}