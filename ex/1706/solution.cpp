#include<stdio.h>
typedef unsigned long long int ulint;

unsigned long long int B[6] = { 1, 36, 36*36, 36*36*36, 36*36*36*36, 36*36*36*36*36 };

int HEX[128] = {
    -1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,
    -1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,
    -1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,
     0, 1, 2, 3, 4, 5, 6, 7,  8, 9,-1,-1,-1,-1,-1,-1,
    -1,10,11,12,13,14,15,16, 17,18,19,20,21,22,23,24,
    25,26,27,28,29,30,31,32, 33,34,35,-1,-1,-1,-1,-1,
    -1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,
    -1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1
};
char ASC[36] = {
    '0','1','2','3','4','5','6','7','8','9',
    'A','B','C','D','E','F','G','H','I','J',
    'K','L','M','N','O','P','Q','R','S','T',
    'U','V','W','X','Y','Z' 
};


int strlen(char x[128]){
    int l;
    for (l = 0 ; x[l] != 0 && l < 128 ; ++l);
    return l;
}

void mul_simple(ulint aa[128], ulint bb[128], ulint cc[256], int aa_len, int bb_len){
    for (int i = 0 ; i < aa_len ; ++i){
        for (int j = 0 ; j < bb_len ; ++j){
            cc[i+j] += aa[i] * bb[j];
        }
    }
    for (int i = 0 ; i < 256; ++i) {
        if (cc[i] > 36){
            cc[i+1] += cc[i] / 36;
            cc[i] = cc[i] % 36;
        }
    }
}

void mul_5(ulint aa[128], ulint bb[128], ulint cc[256], int aa_len, int bb_len){
    // conv 1 -> 5
    aa_len = (aa_len + 4)/5, bb_len = (bb_len + 4)/5; // ceil
    for (int i = 0 ; i < aa_len ; ++i)
        aa[i] = aa[i*5] * B[0] 
            + aa[i*5+1] * B[1]
            + aa[i*5+2] * B[2]
            + aa[i*5+3] * B[3]
            + aa[i*5+4] * B[4];

    for (int i = 0 ; i < bb_len ; ++i)
        bb[i] = bb[i*5] * B[0] 
            + bb[i*5+1] * B[1]
            + bb[i*5+2] * B[2]
            + bb[i*5+3] * B[3]
            + bb[i*5+4] * B[4];

    for (int i = 0 ; i < aa_len ; ++i){
        for (int j = 0 ; j < bb_len ; ++j){
            cc[i+j] += aa[i] * bb[j];
        }
    }
    for (int i = 0 ; i < aa_len+bb_len-1; ++i) {
        if (cc[i] > B[5]){
            cc[i+1] += cc[i] / B[5];
            cc[i] = cc[i] % B[5];
        }
    }
    // 궂이 한 배열에서 계산할 필요는 없다. (속도 차이가 미미함)
    for (int i = aa_len + bb_len - 1 ; i >= 0 ; --i){
        cc[i*5+4] = cc[i] / B[4];
        cc[i] %= B[4];
        cc[i*5+3] = cc[i] / B[3];
        cc[i] %= B[3];
        cc[i*5+2] = cc[i] / B[2];
        cc[i] %= B[2];
        cc[i*5+1] = cc[i] / B[1];
        cc[i] %= B[1];
        cc[i*5] = cc[i];
    }
}

void mul(char a[128], char b[128], char c[256]){
    ulint aa[130], bb[130], cc[260];
    int aa_len, bb_len, cc_len;
    aa_len = strlen(a);
    bb_len = strlen(b);
    //printf(" A : %s \n", a);
    for (int i = 0, j = aa_len - 1 ; i < aa_len; ++i, --j) aa[i] = HEX[a[j]];
    for (int i = aa_len ; i < 130 ; ++i) aa[i] = 0;
    for (int i = 0, j = bb_len - 1 ; i < bb_len; ++i, --j) bb[i] = HEX[b[j]];
    for (int i = bb_len ; i < 130 ; ++i) bb[i] = 0;
    
    for (int i = 0 ; i < 256; ++i) cc[i] = 0 ;

    // 무압축
    // mul_simple(aa, bb, cc, aa_len, bb_len);
    // 5개씩
    mul_5(aa, bb, cc, aa_len, bb_len);

    for (int i = 0 ; i < 256; ++i) 
        if (cc[i]) cc_len = i+1;

    for (int i = 0, j = cc_len -1 ; i < cc_len; ++i, --j)
        c[j] = ASC[cc[i]];
    if (cc_len != 256) c[cc_len] = 0;

}
