#include <stdio.h>
#include <assert.h>
extern int check(unsigned char guess[200]);


inline void fillzero(unsigned char guess[200]){ for (register int i = 0 ; i < 200 ; ++i) guess[i] = 0; }
inline void fillval(int lo, int hi, int val, unsigned char guess[200]){ for (register int i = lo ; i <= hi ; ++i) guess[i] = val; }

void solv_naive(unsigned char guess[200]){
    fillzero(guess);
    int best = 0;
    for (int i = 0 ; i < 200 ; ++i){
        for (int j = 1 ; j < 256 ; ++j){
            guess[i] = j;
            int ret = check(guess);
            int pos = ret >> 8;
            int equal = ret & 0xFF;
            if (pos > best){
                best = pos;
                break;
            }
        }
    }
}

bool exists ( int lo, int hi, int val, unsigned char guess[200]){
    fillzero(guess);
    fillval(lo, hi, val, guess);
    int r = check(guess);
    return r >> 8;
}

void test(unsigned char guess[200]){
    
    char answer[200];

    for (int i = 1; i < 256 ; ++i){
        if (exists(0, 199, i, guess) == 0) continue;

        assert (exists(0, 199, i, guess) > 0);
        int lo = 0, hi = 199;
        while (lo < hi){
            int m = (lo+hi)/2;
            if (exists(lo, m, i, guess)) hi = m;
            else lo = m+1;
        }
        assert(lo == hi);
        answer[lo] = i;
    }
    
    for (int i = 0 ; i < 200 ; ++i) guess[i] = answer[i];

    // solv_naive(guess);
}

