#include <stdio.h>
#include <assert.h>
extern int check(unsigned char guess[200]);

inline void fillzero(unsigned char guess[200]){ for (register int i = 0 ; i < 200 ; ++i) guess[i] = 0; }
inline void fillval(int lo, int hi, int val, unsigned char guess[200]){ for (register int i = lo ; i <= hi ; ++i) guess[i] = val; }

bool exists ( int lo, int hi, int val, unsigned char guess[200]){
    fillzero(guess);
    fillval(lo, hi, val, guess);
    int r = check(guess);
    return r >> 8;
}

void test(unsigned char guess[200]){
    
    char answer[200] = {0};

    int c = 0;
    for (int i = 1; i < 256 ; ++i){
        if (c==200) break;
        if (exists(0, 199, i, guess) == 0) continue;

        c++;
        int lo = 0, hi = 199;
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

