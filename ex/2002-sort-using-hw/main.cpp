#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<algorithm>
#include<time.h>
#include <functional>
#include "BST.cpp"


#define SIZE 1048576
#define IDX 2048


void my_sort(unsigned int DATA[SIZE]);

unsigned int DATA[SIZE];
unsigned int BAK_DATA[SIZE];
unsigned int idx1[IDX], idx2[IDX];

long long int SCORE = 0;

static unsigned int g_seed = 42;
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



int bs (int val, int * x, int l, int u){
    if (l+1 == u) return l;
    int m = (l+u) / 2;
    if (val < x[m]) return bs(val, x, l, m);
    else return bs(val, x, m, u);
}

/* My implementation */
void my_sort(unsigned int DATA[SIZE]){  


    for (int i = 0 ; i < SIZE; ++i){
        if (i == 5) break;
        // printf("%u\n", DATA[i]);
    }

    // hw_sort testing
    /*
    short test[1024] = {  10,20,30,50,40, 30,50,20,10,30 };
    for (int i = 0 ; i < 10 ; ++i) printf("%u ", test[i]); printf("\n");
    hw_sort(test);
    for (int i = 1014 ; i < 1024 ; ++i) printf("%u ", test[i]); printf("\n");
    */
    BST<int> idx1, idx2;
    for (int i = 0 ; i < SIZE; ++i){
        // if (i == 5) break; // jh

        int val1 = DATA[i] >> 16;
        int val2 = DATA[i] & 0xFFFF;
        idx1.insert(val1);
        idx2.insert(val2);
    }
    // printf("%d %d\n", idx1.size(), idx2.size());
    int cnt1 = idx1.size(), cnt2 = idx2.size();
    int arr1[2048], arr2[2048];
    idx1.report(arr1);
    idx2.report(arr2);


    //printf("arr1 : "); for (int i = 0 ; i < cnt1 ; ++i) printf("%d ", arr1[i]); printf("\n");
    //printf("arr2 : "); for (int i = 0 ; i < cnt2 ; ++i) printf("%d ", arr2[i]); printf("\n");


    char mat[2048][2048];
    for (int i = 0 ; i < 2048 ; ++i)
        for (int j = 0 ; j < 2048 ; ++j)
            mat[i][j] = 0;
    for (int i = 0 ; i < SIZE; ++i){
        // if (i == 5) break; // jh
        int val1 = DATA[i] >> 16;
        int val2 = DATA[i] & 0xFFFF;
        int s1 = bs (val1, arr1, 0, cnt1);
        int s2 = bs (val2, arr2, 0, cnt2);
        // printf( "%d %d %d %d\n", val1, val2, s1, s2);
        mat[s1][s2]++;
    }

    int vn = 0;
    for (int i = cnt1 - 1 ; i >= 0 ; --i){
        unsigned int precalc = (((unsigned int)arr1[i]) << 16 );
        for (int j = cnt2 - 1 ; j >= 0 ; --j){
            for (int k = 0 ; k < mat[i][j]; ++k){
                // printf("%u\n", precalc + arr2[j]);
                DATA[vn++] = precalc + arr2[j];
            }
        }
    }

    return;
    
}
