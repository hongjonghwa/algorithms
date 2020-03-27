// Project Euler Answer : 101524
/* 
 * WRONG!!! 좀 더 정교한 Markov Chain 이지만, 예문의 확률과 다르다
 *  --> 제대로 짠 것 같은데 Jail을 너무 자주 방문한다. 뭐가 틀렸나 ?
 * 
 */
#include <stdio.h>
#include <assert.h>
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

double D[13][2]; // dice sum, double 여부 확률 
double C[40][3][40][3];
double P[2][40][3];
int FACT[21];

int ncr(int n, int r){
    return FACT[n]/FACT[r]/FACT[n-r];
}

void probability(){
    for (int i = 1 ; i <= NN ; ++i)
        for (int j = 1 ; j <= NN ; ++j){
            if (i==j) D[i+j][1]++;
            else D[i+j][0]++;
        }
    for (int i = 2 ; i <= NN*2 ; ++i){
        D[i][0] /= NN*NN;
        D[i][1] /= NN*NN;
    }
    for (int i = 2 ; i <= NN*2 ; ++i)
        printf("DICE PROB: %d\t%f\t%f\n", i, D[i][0], D[i][1]);

    for (int i1 = 0 ; i1 < N ; ++i1)
        for (int i2 = 0 ; i2 < 3 ; ++i2)
            for (int j = 2 ; j <= NN*2 ; ++j){
                int next = (i1+j)%N;

                if (next == 10) { // jail 로  가는 경우
                    C[i1][i2][10][0] += D[j][0] + D[j][1];
                } else if (i2 == 2) { // 2 더블 상태일 때
                    C[i1][i2][next][i2] += D[j][0];
                    C[i1][i2][10][0] += D[j][1]; // 3 더블
                } else { // 그 외
                    C[i1][i2][next][i2] += D[j][0];
                    C[i1][i2][next][i2+1] += D[j][1];
                }
            }



}

void verify_probability(){
    double s;
    for (int i1 = 0 ; i1 < N ; ++i1)
        for (int i2 = 0 ; i2 < 3 ; ++i2){
            s = 0;
            for (int j1 = 0 ; j1 < N ; ++j1)
                for (int j2 = 0 ; j2 < 3 ; ++j2)
                    s += C[i1][i2][j1][j2];
            assert ( s > -1e-9 && s < 1e9); // outgoing
        }
    for (int j1 = 0 ; j1 < N ; ++j1)
        for (int j2 = 0 ; j2 < 3 ; ++j2){
            s = 0;
            for (int i1 = 0 ; i1 < N ; ++i1)
                for (int i2 = 0 ; i2 < 3 ; ++i2)
                    s += C[i1][i2][j1][j2];
            assert ( s > -1e-9 && s < 1e9); //ingoing
        }
}

void report(int idx){
    printf("[### %d ###]", idx);
    for (int i = 0 ; i < N; ++i){
        if (i%10==0) printf("\n");
        double p = P[idx%2][i][0] + P[idx%2][i][1] + P[idx%2][i][2]; 
        printf("%.2f ", int(p*10000+0.5)/100.0 );
    }
    printf("\n\n");
}
void report_detail(){
    printf("[### REPORT DETAIL ###]");
    for (int i2 = 0 ; i2 < 3 ; ++i2){
        printf(" \n# double : %d ", i2);
        for (int i1 = 0 ; i1 < N; ++i1){
            if (i1%10==0) printf("\n");
            double p = P[0][i1][i2]; 
            printf("%.2f ", int(p*10000+0.5)/100.0 );
        }
    }

    printf(" \n# total ");
    for (int i1 = 0 ; i1 < N; ++i1){
        if (i1%10==0) printf("\n");
        double p = P[0][i1][0] + P[0][i1][1] + P[0][i1][2]; 
        printf("%.2f ", int(p*10000+0.5)/100.0 );
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
    FACT[0] = 1;
    for (int i = 1 ; i <= 20 ; ++i)
        FACT[i] = FACT[i-1] * i;
    
    probability();
    verify_probability();

    //G2J
    for (int i1 = 0 ; i1 < N ; ++i1)
        for (int i2 = 0 ; i2 < 3 ; ++i2){
            C[i1][i2][10][0] += C[i1][i2][30][0] + C[i1][i2][30][1] + C[i1][i2][30][2];
            C[i1][i2][30][0] = C[i1][i2][30][1] = C[i1][i2][30][2] = 0;
        }
    verify_probability();

    //CC
    int cc[] = {2,17,33};
    for (int c = 0 ; c < 3 ; ++c)
        for (int i1 = 0 ; i1 < N ; ++i1)
            for (int i2 = 0 ; i2 < 3 ; ++i2)
                for (int j2 = 0 ; j2 < 3 ; ++j2){
                    C[i1][i2][0][j2] += C[i1][i2][cc[c]][j2] / 16; // CC --> GO
                    C[i1][i2][10][0] += C[i1][i2][cc[c]][j2] / 16; // CC --> JAIL
                    C[i1][i2][cc[c]][j2] -= C[i1][i2][cc[c]][j2] / 8;
                }
    verify_probability();

    // CH
    int ch[] = {7,22,36};
    for (int c = 0 ; c < 3 ; ++c)
        for (int i1 = 0 ; i1 < N ; ++i1)
            for (int i2 = 0 ; i2 < 3 ; ++i2)
                for (int j2 = 0 ; j2 < 3 ; ++j2){
                    C[i1][i2][0][j2] += C[i1][i2][ch[c]][j2] / 16; // CH --> GO
                    C[i1][i2][10][0] += C[i1][i2][ch[c]][j2] / 16; // CH --> JAIL
                    C[i1][i2][11][j2] += C[i1][i2][ch[c]][j2] / 16; // CH --> C1
                    C[i1][i2][24][j2] += C[i1][i2][ch[c]][j2] / 16; // CH --> E3
                    C[i1][i2][39][j2] += C[i1][i2][ch[c]][j2] / 16; // CH --> H2

                    C[i1][i2][5][j2] += C[i1][i2][ch[c]][j2] / 16; // CH --> R1
                    C[i1][i2][next_r(ch[c])][j2] += C[i1][i2][ch[c]][j2] / 8; // CH --> next R
                    C[i1][i2][next_u(ch[c])][j2] += C[i1][i2][ch[c]][j2] / 16; // CH --> next U
                    C[i1][i2][ch[c]-3][j2] += C[i1][i2][ch[c]][j2] / 16; // CH --> 3 ahead

                    C[i1][i2][ch[c]][j2] -= C[i1][i2][ch[c]][j2] * 10 / 16;
                }
    verify_probability();
        /*
    */

    P[0][0][0] = 1;
    // report(0);

    for (int t = 1 ; t <= 1000 ; ++t){
        int prev = (t-1) % 2, cur = t % 2;

        for (int j1 = 0 ; j1 < N ; ++j1)
            for (int j2 = 0 ; j2 < 3 ; ++j2){    
                P[cur][j1][j2] = 0;            
                for (int i1 = 0 ; i1 < N ; ++i1)
                    for (int i2 = 0 ; i2 < 3 ; ++i2)
                        P[cur][j1][j2] += P[prev][i1][i2] * C[i1][i2][j1][j2];

            }
    }

    report(0);

    // sorting
    Pair pairs[N];
    double check = 0;
    for (int i = 0 ; i < N ; ++i){
        double p = P[0][i][0]+P[0][i][1]+P[0][i][2];
        pairs[i] = Pair(p, i);
        check += p;
    }
    printf(" sum prob check %f \n", check);
    for (int i = 0 ; i < N ; ++i)
        printf("%2d  ==> %f%% \n", i, pairs[i].first / 100 );
    
    for (int i = 1 ; i < N ; ++i)
        for (int j = i; j > 0 ; --j)
            if (pairs[j-1]<pairs[j])
                SWAP(pairs[j-1], pairs[j]);

    for (int i = 0 ; i < 3 ; ++i)
        printf("%f %d\n", pairs[i].first / 100, pairs[i].second);

    report_detail();
}
