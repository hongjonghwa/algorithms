#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<assert.h>
#include<limits.h>
#define ABS(a) ((a)<0 ? -(a) : (a))
#define MAX(a, b) ((a)>(b)?(a):(b))
#define MIN(a, b) ((a)<(b)?(a):(b))

/*
 * ASCII  : 32(0x20) -> SPACE
 *          126(0x7E) -> ~
 *          127(0x7F) -> (DEL)
 */


int X[2000];
bool fail[3][26];
int numOfSpaces[3][26];

int main(){
    freopen("p059_cipher.txt", "rt", stdin);
    for (int i  = 0 ; i < 1455 ; ++i){
        scanf("%d,", &X[i]);
        //printf("%d \n", X[i]);
    }
    for (int i = 0 ; i < 3 ; ++i)
        for (int j = 0 ; j < 26; ++j){
            for (int k = i ; k < 1455 ; k += 3){
                int dec = X[k] ^ ('a'+j);
                if (dec == 32) numOfSpaces[i][j]++;
                if (dec < 32 || dec > 126){
                    fail[i][j] = true;
                    break;
                }
            }
        }
   
    for (int i = 0 ; i < 3 ; ++i)
        for (int j = 0 ; j < 26; ++j)
            if (fail[i][j] == false)
                printf( " Candidate : %d %c cnt:%d\n", i, 'a'+j, numOfSpaces[i][j]);
    // return 0;
    // All candidates Decode
    /*
    for (int i = 0 ; i < 26 ; ++i)
        for (int j = 0 ; j < 26 ; ++j)
            for (int k = 0 ; k < 26 ; ++k)
                if (!fail[0][i] && !fail[1][j] && !fail[2][k]){
                    printf("%c%c%c: ", i+'a', j+'a', k+'a');
                    for (int t = 0 ; t < 50 ; t += 3)
                        printf("%c%c%c", X[t]^(i+'a'), X[t+1]^(j+'a'), X[t+2]^(k+'a'));
                    printf("\n");
                }
    */
    int answer = 0;
    printf ("Text: ");
    char pw[3] = {'e','x','p'};
    for (int k = 0 ; k < 1455 ; ++k){
        char dec = X[k]^pw[k%3];
        printf("%c", dec);
        answer += dec;
    }
    printf("\n");
    printf("Answer: %d\n", answer);

}



