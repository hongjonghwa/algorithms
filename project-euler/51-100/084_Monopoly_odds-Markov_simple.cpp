// Answer : 101524
/* 
 * 아래 MARKOV-CHAIN 은 완벽하지 않다.
 * JAIL에 들어가는 경우 double 카운트가 초기화 되는데
 * 이전 단계의 이전 2 state의 double 여부를 기억해야 한다.
 *
 *
 * 하지만, 무작위로 DICE를 던지는 것 보다는 훨씬 정확하다
 *
 */
#include <stdio.h>
#define N 40
#define NN 4


struct Pair{
    double first;
    int second;
    Pair(double f, int s): first(f), second(s){}
    Pair(){}
    bool operator<(const Pair rhs){
        if (first<rhs.first) return true;
        if (first>rhs.first) return false;
        return second < rhs.second;
    }
};

template<class T>
inline void SWAP(T & a, T & b){
    T tmp = a;
    a = b;
    b = tmp;
}

double C[40][40];
double P[2][40];

void dice6_probability(){
    double d2, n2;
    for (int i = 0 ; i < N ; ++i){
        if (i == 10){ // IN JAIL
            d2 = 0.0; // 2 doble
            n2 = 1.0; // not 2 doble
        }else{
            d2 = 1e0/6/6; // 2 doble
            n2 = 1e0 - d2; // not 2 doble
        }
        C[i][(i+2)%N] += n2*1/36;
        C[i][(i+3)%N] += n2*2/36;
        C[i][(i+4)%N] += n2*3/36;
        C[i][(i+5)%N] += n2*4/36;
        C[i][(i+6)%N] += n2*5/36;
        C[i][(i+7)%N] += n2*6/36;
        C[i][(i+8)%N] += n2*5/36;
        C[i][(i+9)%N] += n2*4/36;
        C[i][(i+10)%N] += n2*3/36;
        C[i][(i+11)%N] += n2*2/36;
        C[i][(i+12)%N] += n2*1/36;
 
        C[i][(i+3)%N] += d2*2/36;
        C[i][(i+4)%N] += d2*2/36;
        C[i][(i+5)%N] += d2*4/36;
        C[i][(i+6)%N] += d2*4/36;
        C[i][(i+7)%N] += d2*6/36;
        C[i][(i+8)%N] += d2*4/36;
        C[i][(i+9)%N] += d2*4/36;
        C[i][(i+10)%N] += d2*2/36;
        C[i][(i+11)%N] += d2*2/36;

        C[i][10] += d2/6;
    }
}
void dice4_probability(){
    double d2, n2;
    for (int i = 0 ; i < N ; ++i){
        if (i == 10){ // IN JAIL
            d2 = 0.0; // 2 doble
            n2 = 1.0; // not 2 doble
        }else{
            d2 = 1e0/4/4; // 2 doble
            n2 = 1e0 - d2; // not 2 doble
        }
        C[i][(i+2)%N] += n2*1/16;
        C[i][(i+3)%N] += n2*2/16;
        C[i][(i+4)%N] += n2*3/16;
        C[i][(i+5)%N] += n2*4/16;
        C[i][(i+6)%N] += n2*3/16;
        C[i][(i+7)%N] += n2*2/16;
        C[i][(i+8)%N] += n2*1/16;
  
        C[i][(i+3)%N] += d2*2/16;
        C[i][(i+4)%N] += d2*2/16;
        C[i][(i+5)%N] += d2*4/16;
        C[i][(i+6)%N] += d2*2/16;
        C[i][(i+7)%N] += d2*2/16;

        C[i][10] += d2/4;
 
    }
}
void verify_dice_probability(){
    double s;
    for (int i = 0 ; i < N ; ++i){
        s = 0;
        for (int j = 0 ; j < N ; ++j)
            s += C[i][j];
        printf("VERIFY %d %f \n", i, s);
    }
}

void report_c(){
    for (int i = 0 ; i < N; ++i){
        for (int j = 0 ; j < N; ++j)
            printf("%f ", C[i][j]);
        printf("\n");
    }
    printf("\n");
}

void report(int idx){
    printf("[### %d ###]", idx);
    for (int i = 0 ; i < N; ++i){
        if (i%10==0) printf("\n");
        printf("%.2f ", int(P[idx%2][i]*10000+0.5)/100.0 );
    }
    printf("\n\n");
}

int next_r(int cur){
    if (cur < 5) return 5;
    if (cur < 15) return 15;
    if (cur < 25) return 25;
    if (cur < 35) return 35;
    return 5;
}
int next_u(int cur){
    if (cur < 12) return 12;
    if (cur < 28) return 28;
    return 12;
}

int main(){
    if (NN == 6) dice6_probability();
    else if (NN == 4) dice4_probability();
    else return 0;
    //verify_dice_probability(); return 0;

    //G2J
    for (int i = 0 ; i < N ; ++i){
        C[i][10] += C[i][30]; // G2J --> JAIL
        C[i][30] = 0; 
    }

    //CC
    int cc[] = {2,17,33};
    for (int i = 0 ; i < 3 ; ++i){
        for (int j = 0 ; j < N ; ++j){
            C[j][0] += C[j][cc[i]]/16; // CC --> GO
            C[j][10] += C[j][cc[i]]/16; // CC --> JAIL
            C[j][cc[i]] -= C[j][cc[i]]/8; // CC --> JAIL
        }
    }

    // CH
    int ch[] = {7,22,36};
    for (int i = 0 ; i < 3 ; ++i){
        for (int j = 0 ; j < N ; ++j){
            C[j][0] += C[j][ch[i]]/16; // CH --> GO
            C[j][10] += C[j][ch[i]]/16; // CH --> JAIL
            C[j][11] += C[j][ch[i]]/16; // CH --> C1
            C[j][24] += C[j][ch[i]]/16; // CH --> E3
            C[j][39] += C[j][ch[i]]/16; // CH --> H2

            C[j][5] += C[j][ch[i]]/16; // CH --> R1
            C[j][next_r(ch[i])] += C[j][ch[i]]/8; // CH --> next R
            C[j][next_u(ch[i])] += C[j][ch[i]]/16; // CH --> next U
            C[j][ch[i]-3] += C[j][ch[i]]/16; // CH --> 3 back

            C[j][ch[i]] -= C[j][ch[i]]*10/16; 

        }
    }
    // report_c();

    P[0][0] = 1;
    // report(0);
    for (int t = 1 ; t <= 200 ; ++t){
        int prev = (t-1) % 2, cur = t % 2;
        for (int to = 0 ; to < N ; ++to){
            P[cur][to] = 0;
            for (int from = 0 ; from < N ; ++from)
                P[cur][to] += P[prev][from] * C[from][to];
        } 
        // report(t);
    }
    report(1);

    // assertion 
    /*
    double sum1 = 0, sum2 = 0;
    for (int i = 0 ; i < N ; ++i){
        sum1 += P[0][i];
        sum2 += P[1][i];
    }
    printf("Assertion %f %f\n", sum1, sum2);
    */

    // sorting
    Pair pairs[N];
    for (int i = 0 ; i < N ; ++i)
        pairs[i] = Pair(P[0][i], i);
    for (int i = 1 ; i < N ; ++i)
        for (int j = i; j > 0 ; --j)
            if (pairs[j-1]<pairs[j])
                SWAP(pairs[j-1], pairs[j]);
    for (int i = 0 ; i < 3 ; ++i)
        printf("%f %d\n", pairs[i].first, pairs[i].second);
}
