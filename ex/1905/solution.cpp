#include<stdio.h>
#include<assert.h>
#define BSIZE 20
#define BCNT 10
extern int check(unsigned char guess[200]);

void report(unsigned char guess[200]){
    for (int i = 0 ; i< 200 ; ++i){
        printf("%d\t", guess[i]);
        if (i%10 == 9) printf("\n");
    }
}

void test3(unsigned char guess[200]){
    unsigned char ans[200];
    int ret;

    for (int i = 1, c = 0 ; i < 256 && c < 200 ; ++i){

        bool exxx = false;
        // 아래랑 합쳐서 1번 줄이자 
        /*
        for (int j = 0 ; j < 200 ; ++j) guess[j] = i;
        ret = check(guess);
        if (ret == 0) continue;
        */

        // i는 사용한다
        int mask = 1, pos = 0;
        while (mask<256 && !exxx){
           for (int j = 0 ; j < 200 ; ++j) guess[j] = (j & mask ? i : 0); 
           ret = check(guess);
           if (ret == 0) {
               exxx = true;
               break;
           }
           //printf("%d %d \n", i, ret);
           if (ret>>8  > 0) pos += mask;
           mask *= 2;
        }
        if (exxx) continue;
        assert(pos < 200);
        c++;
        ans[pos] = i;
    }
    for (int i = 0 ; i < 200 ; ++i) guess[i] = ans[i];
    
    return;
}

void test2(unsigned char guess[200]){
    int _debug_cnt = 0;
    for (int i = 0 ; i < 200 ; ++i) guess[i] = 0;
    bool num_using[256]; // no exists
    bool num_pick[256]; // pick
    for (int i = 0 ; i < 256 ; ++i) num_using[i] = true;
    for (int i = 0 ; i < 256 ; ++i) num_pick[i] = false;
    // num pick
    int nums[10][20];
    for (int i = 0 ; i < 10 ; ++i){
        int cnt = 0 ;

        for (int j = 1 ; j <= 255 ; ++j){
            if (!num_using[j] || num_pick[j]) continue;
            for ( int k = i*20 ; k < (i+1)*20 ; k++) guess[k] = j;
            int ret = check(guess); _debug_cnt++;
            if (ret == 0){
                num_using[j] = false;
                continue;
            }
            if (ret & 256){
                // printf("Pick %d\t%d\t%d\n", i, j, cnt);
                num_pick[j] = true;
                nums[i][cnt++] = j;
                if (cnt == 20) break;
            }
        }
        for ( int k = i*20 ; k < (i+1)*20 ; k++) guess[k] = 0;
    }
    printf("  Pick %d ,", _debug_cnt);
    _debug_cnt = 0;
    // arrange
    int corr = 0;
    for (int i = 0 ; i < 10 ; ++i){
        int s = i*20, e = (i+1)*20;
        bool pick[20] = { 0 };

        for (int j = s ; j < e ; ++j){
            for (int k = 0 ; k < 20 ; ++k){
                if (pick[k]) continue;
                guess[j] = nums[i][k];
                int ret = check(guess); _debug_cnt++;
                int pos = ret >> 8;
                if (pos>corr){
                    pick[k] = true;
                    corr = pos;
                    break;
                }

            }
        }
    }
    // printf("Corr %d \n ", corr);
    assert(corr == 200);
    printf(" Arrange %d\n", _debug_cnt);
    // report(guess);
    return;
}


// 200 * 255 * 1/2 = 25500
void test1(unsigned char guess[200]){
    for (int i = 0 ; i < 200 ; ++i) guess[i] = 0;
    for (int i = 0 ; i < 200 ; ++i){
        for (int j = 1 ; j <= 255 ; ++j){
           guess[i] = j;
           int ret = check(guess);
           int pos = ret >> 8; 
           if (pos == i + 1) break;
        }
    }
    report(guess);
}
void test(unsigned char guess[200]){
    // test1(guess); // 25500 풀이 -> SWAP 해봤자 절반
    // test2(guess); // 2200 ~ 2300 풀이
    test3(guess); // 1650
}
