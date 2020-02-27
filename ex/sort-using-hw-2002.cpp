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
    for (int i = 0 ; i < 10 ; ++i){
    }
    for (int i = 0 ; i < SIZE ; ++i){
        assert(BAK_DATA[i] == DATA[i]);
    }

    clock_t total_duration = clock()-start_clk;
    printf("Execution time: %f\n", (double)total_duration / CLOCKS_PER_SEC);
    assert(total_duration < 2 * CLOCKS_PER_SEC); // 2 sec 제한
}

/* My implementation */
void my_sort(unsigned int DATA[SIZE]);


void my_sort(unsigned int DATA[SIZE]){
    qsort(DATA, SIZE, sizeof(unsigned int), comp_ui_gt);
}