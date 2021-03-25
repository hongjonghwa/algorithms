#include<stdio.h>
#include<assert.h>
#define NDEBUG

typedef unsigned long long int ulint;

unsigned long long int B[7] = { 1, 36, 36*36, 36*36*36, 36*36*36*36, 36*36*36*36*36, 36ull*36*36*36*36*36 };

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
        aa[i] = aa[i*5]
            + aa[i*5+1] * B[1]
            + aa[i*5+2] * B[2]
            + aa[i*5+3] * B[3]
            + aa[i*5+4] * B[4];

    for (int i = 0 ; i < bb_len ; ++i)
        bb[i] = bb[i*5]
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

void multiply(char a[128], char b[128], char c[256]){
    
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

    // 1) 무압축
    // mul_simple(aa, bb, cc, aa_len, bb_len);
    // 2) 5개씩
    mul_5(aa, bb, cc, aa_len, bb_len);

    for (int i = 0 ; i < 256; ++i) 
        if (cc[i]) cc_len = i+1;

    for (int i = 0, j = cc_len -1 ; i < cc_len; ++i, --j)
        c[j] = ASC[cc[i]];
    if (cc_len != 256) c[cc_len] = 0;

}


// 2021.3.25 다시 작성
void multiply_6(char a[128], char b[128], char c[256]){    
    int a_len = strlen(a);
    unsigned long long int aa[22] = {0};
    for (int i = a_len-1, j = 0; i >= 0 ; i -= 6, j++){
        aa[j] += HEX[a[i]]; if (i == 0) break;
        aa[j] += HEX[a[i-1]] * B[1]; if (i == 1) break;
        aa[j] += HEX[a[i-2]] * B[2]; if (i == 2) break;
        aa[j] += HEX[a[i-3]] * B[3]; if (i == 3) break;
        aa[j] += HEX[a[i-4]] * B[4]; if (i == 4) break;
        aa[j] += HEX[a[i-5]] * B[5]; if (i == 5) break;
    }

    int b_len = strlen(b);
    unsigned long long int bb[22] = {0};
    for (int i = b_len-1, j = 0; i >= 0 ; i -= 6, j++){
        bb[j] += HEX[b[i]]; if (i == 0) break;
        bb[j] += HEX[b[i-1]] * B[1]; if (i == 1) break;
        bb[j] += HEX[b[i-2]] * B[2]; if (i == 2) break;
        bb[j] += HEX[b[i-3]] * B[3]; if (i == 3) break;
        bb[j] += HEX[b[i-4]] * B[4]; if (i == 4) break;
        bb[j] += HEX[b[i-5]] * B[5]; if (i == 5) break;
    }

    unsigned int umax = -1;
    for (int i = 0 ; i < 22 ; ++i) assert(aa[i] <= umax && bb[i] <= umax);

    unsigned long long int cc[44] = {0};
    for (int i = 0 ; i < 22 ; ++i)
        for (int j = 0 ; j < 22 ; ++j){
            cc[i+j] += aa[i] * bb[j];
            // maybe - 36^6 BASE 일 때는 overflow가 날 수 있어 매 연산마다 확인이 필요하다. 
            if (cc[i+j] >= B[6]){ // overflow check
                cc[i+j+1] += cc[i+j] / B[6];
                cc[i+j] %= B[6];
            }
        }
 
    char temp_c[44*6] = {0};
    for (int i = 0, j = 0 ; i < 44 ; ++i, j+=6){
        temp_c[j] = ASC[ cc[i] % 36 ];
        temp_c[j+1] = ASC[ (cc[i] /= 36) % 36 ];
        temp_c[j+2] = ASC[ (cc[i] /= 36) % 36 ];
        temp_c[j+3] = ASC[ (cc[i] /= 36) % 36 ];
        temp_c[j+4] = ASC[ (cc[i] /= 36) % 36 ];
        temp_c[j+5] = ASC[ (cc[i] /= 36) % 36 ];
    }
    
    int c_len = 44*6; // 263
    while (temp_c[c_len-1] == '0') c_len--;
    assert (c_len <= 256);

    for (int i = c_len-1 , j = 0;  i >= 0  ; --i, ++j)
        c[i] = temp_c[j];
}
void mul(char a[128], char b[128], char c[256]){
    multiply(a,b,c); // 12.9s
    // multiply_6(a,b,c); // 14.3s
    // --> 6개 씩 묶을 경우 단위 연산마다 overflow 체크가 필요하여 오히려 더 느려진다, 5개 씩 묶는 것이 최적!
}


void test_run(char a[128], char b[128]){
    // custom data
    /*
    for (int i = 0 ; i < 128 ; ++i) a[i] = b[i] = 0;
    a[0] = b[0] = '1';
    for (int i = 1 ; i < 8; ++i) a[i] = b[i] = '0';
    */


    printf ("### TEST RUN ###\n");
    char c1[256], c2[256];
    multiply (a, b, c1);
    multiply_6 (a, b, c2);
    printf ("A: %s\n", a);
    printf ("B: %s\n", b);
    printf ("C: %s\n", c1);
    // for (int i = 0; i < 256 && c1[i] ; ++i) printf("%d %c %c\n", i, c1[i], c2[i]);
    for (int i = 0; i < 256 && c1[i] && c2[i] ; ++i) assert(c1[i] == c2[i]);


    // ### MAIN RUN



    printf ("### TEST RUN END. ###\n");
}