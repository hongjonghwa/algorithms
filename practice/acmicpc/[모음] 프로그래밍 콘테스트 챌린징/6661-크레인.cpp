#include<cstdio>
#include<algorithm>
#include <math.h> 
#define PI 3.14159265358979323846  // 소수 20자리 까지

// const PI = acos(-1.0);  // ==> 소수 15자리까지는 정확
// 3.141592653589793 116 ()


typedef std::pair<double, double> pdd;

using namespace std;


int N, C; //  1 ≤ n ≤ 10 000 and c ≥ 0
int L[10001]; // len
pdd P[10001];
short A[10001];

void report(){
    for (int i = 1 ; i <= N ; ++i)
        printf("[%d] x %.2f, y %.2f, a %d\n", i, P[i].first, P[i].second, A[i]);
}
pdd rotation(pdd point, int angle){
    double radian = PI * angle / 180;
    double &x = point.first;
    double &y = point.second;
    return make_pair(x*cos(radian)  - y * sin(radian), x*sin(radian) + y*cos(radian) );
}
pdd rotation_from(pdd point, int angle, pdd from){
    pdd v = make_pair(point.first - from.first, point.second - from.second);
    pdd v2 = rotation(v, angle);
    return make_pair(v2.first + from.first, v2.second + from.second);
}

void calc(int s, int a){
    int d_a = a-A[s];
    // printf("rotation %d degree at %d\n", d_a, s);
    for (int i = s+1; i <= N ; ++i)
        P[i] = rotation_from(P[i], d_a, P[s]);
    printf ("%.2f %.2f\n", P[N].first, P[N].second);
    A[s] = a;
}

int main(){


    for (;;){
        if ( scanf("%d %d\n", &N, &C) != 2 ) break;
        P[0].first = P[0].second = 0.0;
        for (int i = 1 ; i <= N ; ++i){
            if ( scanf("%d", &L[i]) != 1 ) return 1;
            P[i].first = 0.0; // x
            P[i].second = P[i-1].second + L[i];  // y
            A[i] = 180;
        }
        // report();
        for (int i = 0 ; i < C ; ++i){
            int s, a;
            if ( scanf("%d %d\n", &s, &a) != 2 ) return 1;
            calc(s, a);
            // report();
        }
        printf("\n");
    }
}