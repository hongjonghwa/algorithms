#include<stdio.h>
#include<assert.h>
#include<string.h>
#include"alpha.h"
#define INF 987654321

static int _offset;
static int _debug_flag = 1;
static int _debug_answer = 0;






// blacks number
int blacks_partial_sum[65];
void calc_blacks_sum(char photo[16][64]){
    blacks_partial_sum[0] = 0;
    for (int x = 0 ; x < 64 ; ++x){
        int t = 0;
        for (int y = 0 ; y < 16 ; ++y)
            if (photo[y][x] == 8) 
                t++;
        blacks_partial_sum[x+1] = blacks_partial_sum[x] + t;
    }
}
int blacks_sum(int l, int u){
    return blacks_partial_sum[u] - blacks_partial_sum[l];
}
// best candidate;
char best_pick[57];
int best_pick_noises[57];
void calc_best_candidate(char photo[16][64]){
    for (int x = 0 ; x < 57; ++x){
        best_pick_noises[x] = 9999;
        int temp_blacks =  blacks_sum(x, x+8);
        
        for (int dy = 0 ; dy < 9 ; ++dy){
            for (int a = 0 ; a <= 9 ; ++a ){
                int n = temp_blacks;
                for (int yy = 0 ; yy < 8 ; ++yy)
                    for (int xx =0 ; xx < 8 ; ++xx){
                        if (alpha[a][yy][xx] == 8){
                            if (photo[dy+yy][x+xx]== 8) n--; // 88 이면 노이즈를 줄인다.
                            else n++;  // photo 에서는 0 이나 alpha 가 1 이면 노이즈를 늘린다
                        }
                    }
                if (n < best_pick_noises[x]){
                    best_pick_noises[x] = n;
                    best_pick[x] = a;
                }
            }
        }
    }
}

// 재귀
int rsolv_best_pick = 0;
int rsolv_last_noise;

void rsolv(int remains, int x_lo, int cum_noise, int pick){
    if (remains==0){
        cum_noise += blacks_sum(x_lo, 56); // 중요! 남아있는 noise 포함
        if (cum_noise < rsolv_last_noise){

            rsolv_last_noise = cum_noise;
            rsolv_best_pick  = pick;
            // printf ("%d %d\n",rsolv_best_pick, rsolv_last_noise );
        }
        return;
    }
    if (x_lo >= 57) return;

    for (int i = x_lo ; i < 57 && i <= x_lo + 8 ; ++i)
        rsolv(
            remains - 1, 
            i + 8 , 
            cum_noise + best_pick_noises[i] + blacks_sum(x_lo, i) , // 중요! 문자 사이사이의 noise 포함
            pick * 10 + best_pick[i]);
}

int recog(char photo[16][64]) {
    calc_blacks_sum(photo);
    calc_best_candidate(photo);
    // for (int i = 0 ; i < 57 ; ++i) printf("%d %d '%d' %d \n", i, blacks_sum(i, i+8), best_pick[i], best_pick_noises[i]);

    rsolv_last_noise = INF;
    rsolv(4, 0, 0, 0);
	return rsolv_best_pick;
}