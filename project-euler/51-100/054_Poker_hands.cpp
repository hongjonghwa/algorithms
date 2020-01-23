#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<assert.h>
#define ABS(a) ((a)<0 ? -(a) : (a))
#define MAX(a, b) ((a)>(b)?(a):(b))
#define MIN(a, b) ((a)<(b)?(a):(b))

/*
 * High Card: Highest value card.
 * One Pair: Two cards of the same value.
 * Two Pairs: Two different pairs.
 * Three of a Kind: Three cards of the same value.
 * Straight: All cards are consecutive values.
 * Flush: All cards of the same suit.
 * Full House: Three of a kind and a pair.
 * Four of a Kind: Four cards of the same value.
 * Straight Flush: All cards are consecutive values of same suit.
 * Royal Flush: Ten, Jack, Queen, King, Ace, in same suit.
 *
 * The cards are valued in the order:
 * 2, 3, 4, 5, 6, 7, 8, 9, 10, Jack, Queen, King, Ace.
 *
 * If two players have the same ranked hands then the rank made up of the highest value wins
 * ; for example, a pair of eights beats a pair of fives (see example 1 below). 
 * But if two ranks tie, for example, both players have a pair of queens, 
 * then highest cards in each hand are compared (see example 4 below)
 * ; if the highest cards tie then the next highest cards are compared, and so on.
 */

template <class T>
inline void SWAP(T & a, T & b){
    T tmp = a;
    a = b;
    b = tmp;
}
inline int conv(char p){
    if (p == 'A') return 14;
    if (p == 'K') return 13;
    if (p == 'Q') return 12;
    if (p == 'J') return 11;
    if (p == 'T') return 10;
    return p - '0';
}

int is_straight (int n[5]){
    if (n[0]+1 == n[1] && 
        n[1]+1 == n[2] &&
        n[2]+1 == n[3] &&
        n[3]+1 == n[4])
    {
        if (n[4] == 14) return 99; // 로얄스트레이트는 특별함
        return n[4]; // highest
    }
    if (n[0] == 2 && n[1] == 3 && n[2] == 4 && n[3] == 5 && n[4] == 14) return 14;
    return 0;
}
int is_4s(int n[5]){
    if (n[0] == n[3]) return (n[0] <<4) + n[4];
    if (n[1] == n[4]) return (n[1] <<4) + n[0];
    return 0;
}
int is_32s(int n[5]){
    if (n[0] == n[2] && n[3] == n[4]) return (n[0]<<4) + n[3];
    if (n[0] == n[1] && n[2] == n[4]) return (n[2]<<4) + n[0];
    return 0;
}
int is_3s(int n[5]){
    if (n[0] == n[2] ) return (n[0]<<8) + (n[4]<<4) + n[3];
    if (n[1] == n[3] ) return (n[1]<<8) + (n[4]<<4) + n[0];
    if (n[2] == n[4] ) return (n[2]<<8) + (n[1]<<4) + n[0];
    return 0;
}
int is_22s(int n[5]){
    if (n[0] == n[1] && n[2] == n[3]) return (n[2]<<8) + (n[0]<<4) + n[4];
    if (n[0] == n[1] && n[3] == n[4]) return (n[3]<<8) + (n[0]<<4) + n[2];
    if (n[1] == n[2] && n[3] == n[4]) return (n[3]<<8) + (n[1]<<4) + n[0];
    return 0;
}
int is_2s(int n[5]){
    if (n[0] == n[1]) return (n[0]<<12) + (n[4]<<8) + (n[3]<<4) + n[2];
    if (n[1] == n[2]) return (n[1]<<12) + (n[4]<<8) + (n[3]<<4) + n[0];
    if (n[2] == n[3]) return (n[2]<<12) + (n[4]<<8) + (n[1]<<4) + n[0];
    if (n[3] == n[4]) return (n[3]<<12) + (n[2]<<8) + (n[1]<<4) + n[0];
    return 0;
}

int score(char c[10]){
    bool flush = (c[1] == c[3] && c[3] == c[5] && c[5] == c[7] && c[7] == c[9]);

    int n[5];
    for (int i = 0 ; i < 5; ++i) n[i] = conv(c[i*2]);
    for (int i = 1; i < 5; ++i)
        for (int j = i ; j > 0 && n[j-1]>n[j] ; --j)
            SWAP(n[j-1], n[j]);
    // assert
    for (int i = 0; i < 4; ++i) assert(n[i] <= n[i+1]);

    int straight = is_straight(n);
    if (flush && straight>0) return 8e6 + straight; // 스트레이트 플러시

    int t = is_4s(n);
    if (t>0) return 7e6 + t; // 4카드
    t = is_32s(n);
    if (t>0) return 6e6 + t; // 풀하우스

    if (flush) return 5e6 + (n[4]<<16) + (n[3]<<12) + (n[2]<<8) + (n[1]<<4) + n[0]; // 플러시

    if (straight) return 4e6 + straight; // 스트레이트

    t = is_3s(n);
    if (t>0) return 3e6 + t; // 3카드

    t = is_22s(n);
    if (t>0) return 2e6 + t; // 2페어

    t = is_2s(n);
    if (t>0) return 1e6 + t; // 1페어

    return (n[4]<<16) + (n[3]<<12) + (n[2]<<8) + (n[1]<<4) + n[0];
}
char debug_rev(int score, int offset){
    int mask = 15;
    while(offset--) score >>= 4;
    int c = score & mask;
    if (c == 14) return 'A';
    if (c == 13) return 'K';
    if (c == 12) return 'Q';
    if (c == 11) return 'J';
    if (c == 10) return 'T';
    return c + '0';
}

void debug2(int score){
    printf("(");
    int N[5];
    for (int i = 0 ; i < 5 ; ++i)
        N[i] = debug_rev(score%1000000, i);
    if (score == 8000099) printf("Royal Flush : A K Q J T");
    else if (score >= 8000000) printf("Straight Flush : %c%c%c%c%c", N[0], N[0]-1, N[0]-2, N[0]-3, N[0]-4 );
    else if (score >= 7000000) printf("Four of a Kind : 4%c %c", N[1], N[0]);
    else if (score >= 6000000) printf("Full House : 3%c 2%c", N[1], N[0]);
    else if (score >= 5000000) printf("Flush : %c%c%c%c%c", N[4],N[3],N[2],N[1],N[0]);
    else if (score >= 4000000) printf("Straight Flush : %c%c%c%c%c", N[0], N[0]-1, N[0]-2, N[0]-3, N[0]-4 );
    else if (score >= 3000000) printf("Three of a Kind : 3%c %c %c", N[2],N[1],N[0]);
    else if (score >= 2000000) printf("Two Pairs : 2%c 2%c %c", N[2],N[1],N[0]);
    else if (score >= 1000000) printf("One Pair : 2%c %c %c %c" ,N[3],N[2],N[1],N[0]);
    else printf("High Card : %c%c%c%c%c", N[4],N[3],N[2],N[1],N[0]);
    printf(")");
}

void debug(char b[20], int s1, int s2){
    for (int i = 0 ; i < 10 ; i+=2) printf("%c%c ", b[i], b[i+1]);
    printf("vs ");
    for (int i = 10 ; i < 20 ; i+=2) printf("%c%c ", b[i], b[i+1]);
    printf("\n");

    printf("\t%d ", s1);
    debug2(s1);
    if (s1==s2) printf(" = ");
    else if (s1>s2) printf(" > ");
    else printf(" < ");
    printf("%d ", s2);
    debug2(s2);
    printf("\n");
}
int main(){
    freopen("p054_poker.txt", "rt", stdin);
    char buf[20];
    int answer = 0;
    for (int i = 0 ; i < 1000 ; ++i){
        for (int j = 0 ; j < 20 ; j+=2)
            scanf("%s", buf+j);
        
        int s1 = score(buf); 
        int s2 = score(buf+10); 

        if (s1 > s2) answer++;

        printf("[%d] ", i+1);
        debug(buf, s1, s2);
        
    }
    printf("Answer is %d\n", answer);

}



