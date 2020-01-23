#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define ABS(a) ((a)<0 ? -(a) : (a))
#define MAX(a, b) ((a)>(b)?(a):(b))
#define MIN(a, b) ((a)<(b)?(a):(b))

struct pair{
    int first, second;
    pair(int f, int s){
        first = f;
        second = s;
    }
};


int minFactor[101];
void e(){
    minFactor[0] = minFactor[1] = -1;
    for (int i = 2 ; i <= 100 ; ++i) minFactor[i] = i;

    for (int i = 2 ; i <= 10 ; ++i)
        if (minFactor[i] == i)
            for (int j = i * i ; j <= 100 ; j += i)
                if (minFactor[j] == j)
                    minFactor[j] = i;
    
}

int X[101][101][25]; // b, a, factors, 

int P[25]; // Prime array
int R[101]; // reverse array

bool isEqual(int b1, int a1, int b2, int a2){
    for (int i = 0 ; i < 25; ++i)
        if (X[b1][a1][i] != X[b2][a2][i])
            return false;
    return true;
}
int main (){
    e();
    int c = 0;
    for (int i = 0 ; i <=100 ; ++i){
        if (minFactor[i] == i){
            // printf("%d %d\n", c, i);
            R[i] = c;
            P[c++] = i;
        }else{
            R[i] = -1;
        }
    }
    for (int a = 2 ; a <= 100 ; ++a){
        int k = a;
        while(k>1){
            X[1][a][R[minFactor[k]]] ++;
            // printf("%d %d %d\n", a, minFactor[k], R[minFactor[k]]);
            k /= minFactor[k];
        }
    }
    for (int b = 2; b <= 100 ; ++b)
        for (int a= 2 ; a <= 100 ; ++a)
            for (int k = 0 ; k < 25 ; ++k)
                X[b][a][k] = X[1][a][k] * b;

    int ret = 0;
    for (int b1 = 2 ; b1 <= 100 ; ++b1){
        for (int a1 = 2 ; a1 <= 100 ; ++a1){
            bool uniq = true;
            for (int b2 = 2 ; b2<= b1 ; ++b2){
                int a2_end = b1==b2 ? a1 - 1 : 100;
                for (int a2 = 2 ; a2 <= a2_end ; ++a2){
                    if (isEqual(b1,a1,b2,a2)){
                        printf ("conflict %d %d  %d %d is uniq \n",  b1, a1, b2, a2);
                        uniq = false;
                        break;
                    }
                }
                if (uniq == false) break;
            }
            if (uniq){
                ret++;
                printf ("[%d] %d %d is uniq \n", ret, b1, a1);
            }
        }
    }
    printf("Answer is %d\n", ret);
    
}
