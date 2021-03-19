/*
[1] CHECK 1469, FAIL 0, time 0.071162
[2] CHECK 1473, FAIL 0, time 0.071231
[3] CHECK 1469, FAIL 0, time 0.071089
[4] CHECK 1462, FAIL 0, time 0.070903
[5] CHECK 1465, FAIL 0, time 0.071086
[6] CHECK 1465, FAIL 0, time 0.071037
[7] CHECK 1470, FAIL 0, time 0.071353
[8] CHECK 1463, FAIL 0, time 0.070865
[9] CHECK 1464, FAIL 0, time 0.071061
[10] CHECK 1476, FAIL 0, time 0.071384
Score is 708

real    0m0.713s
user    0m0.705s
sys     0m0.008s
*/

#include <stdio.h>
#include <assert.h>
extern int check(unsigned char guess[200]);

inline void fillzero(unsigned char guess[200]){ for (register int i = 0 ; i < 200 ; ++i) guess[i] = 0; }
inline void fillval(int lo, int hi, int val, unsigned char guess[200]){ for (register int i = lo ; i <= hi ; ++i) guess[i] = val;  }

int check_wrap ( int lo, int hi, int val, unsigned char guess[200]){
    fillzero(guess);
    fillval(lo, hi, val, guess);
    return check(guess);
}


bool exists ( int lo, int hi, int val, unsigned char guess[200]){
    return check_wrap(lo, hi, val, guess) >> 8;
}

void test(unsigned char guess[200]){
    
    char answer[200] = {0};

    int c = 0, lo, hi;
    for (int i = 1; i < 256 ; ++i){
        if (c==200) break;
        int r = check_wrap(0, 99, i, guess);
        if (r == 0) continue; // 사용 안 함

        c++;
        /* check 횟수를 1번 줄임 */
        if ( (r>>8) ) lo = 0, hi = 99;
        else lo = 100, hi = 199; 

        while (lo < hi){
            while (answer[lo] > 0) ++lo;
            while (answer[hi] > 0) --hi;

            assert (lo <= hi);
            if (lo == hi) break;
            
            int m = (lo+hi)/2;
            if (exists(lo, m, i, guess)) hi = m;
            else lo = m+1;
        }
        // printf(" %d %d %d %d \n", lo, hi, i,i);
        assert(lo == hi);
        answer[lo] = i;
    }
    
    for (int i = 0 ; i < 200 ; ++i) guess[i] = answer[i];

    // solv_naive(guess);
}

