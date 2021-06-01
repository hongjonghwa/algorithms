#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<assert.h>

double X[100000][3], X_BAK[100000][3];
inline int myrand(){ // 원래는 fast-rand
    //return rand() % 32768;
    return rand() & 0x7fff;
}

void build(){
    srand(42);
    for (int i = 0 ; i < 100000 ; ++i)
        for (int j = 0 ; j < 3 ; ++j)
            X[i][j] = X_BAK[i][j] = double(myrand()) / (myrand() + 1);
}
inline double sq(double n) { return n*n;} 
double distance(double a[3], double b[3]){
    double s = 0;
    for (int j = 0 ; j < 3; ++j)
        s += sq(a[j]-b[j]);
    return sqrt(s);
}

void solution (double X[100000][3], int result[3]);

int main(){
    build();
    int result[3] = {0,0,0};
    solution(X, result);
    double score=0;
    for (int i = 0 ; i < 100000 ; ++i){
        double dist = 1e20;
        for (int j = 0 ; j < 3; ++j){
            double d = distance(X_BAK[i], X_BAK[result[0]]);
            if (dist>d) dist = d;
        }
        score += dist;
    }

    printf("SCORE is %f\n", score);
    // 1st 142만, 2nd/3rd 143만, 나는 144만
    
}

// --------------------------------------------------------------
void solution (double X[100000][3], int result[3]){
    // calculation codes.
    return;
}