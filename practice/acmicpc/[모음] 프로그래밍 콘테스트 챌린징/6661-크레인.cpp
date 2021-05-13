#include<cstdio>
#include<cstring>
#include<algorithm>
#include <math.h> 
#define PI 3.14159265358979323846  // 소수 20자리 까지

typedef std::pair<double, double> pdd;

using namespace std;

int N, C; //  1 ≤ n ≤ 10 000 and c ≥ 0
int L[10001]; // len
pdd P[10001];
short A[10001];

// segment tree
pdd ST[40001];
int LAZY[40001];

pdd rotation(pdd point, int angle){
    double radian = PI * angle / 180;
    double &x = point.first;
    double &y = point.second;
    return make_pair(x*cos(radian)  - y * sin(radian), x*sin(radian) + y*cos(radian) );
}

void segtree_init(int node, int left, int right){
    if (left == right){
        ST[node] = P[left]; // leaf init
        return;
    }
    int mid = (left + right)/2;
    segtree_init(node*2, left, mid);
    segtree_init(node*2+1, mid+1, right);
    ST[node].first = ST[node*2].first + ST[node*2+1].first;
    ST[node].second = ST[node*2].second + ST[node*2+1].second;
}
void segtree_update(int upd_val, int upd_left, int upd_right,  int node, int node_left, int node_right){
    // lazy resolve...
    if (LAZY[node] != 0){
        ST[node] = rotation(ST[node], LAZY[node]);
        if (node_left != node_right){
            LAZY[node*2] += LAZY[node];
            LAZY[node*2+1] += LAZY[node];
        }
        LAZY[node] = 0;
    }

    if (upd_right < node_left || node_right < upd_left) return;

    // lazy update...
    if (upd_left <= node_left && node_right <= upd_right ){
        ST[node] = rotation(ST[node], upd_val);
        if (node_left != node_right){
            LAZY[node*2] += upd_val;
            LAZY[node*2+1] += upd_val;
        }
        return;
    }


    int node_mid = (node_left + node_right)/2;
    segtree_update(upd_val, upd_left, upd_right, node*2, node_left, node_mid);
    segtree_update(upd_val, upd_left, upd_right, node*2+1, node_mid+1, node_right);
    ST[node].first = ST[node*2].first + ST[node*2+1].first;
    ST[node].second = ST[node*2].second + ST[node*2+1].second;
}
void update(int upd_val, int upd_left, int upd_right){
    segtree_update(upd_val, upd_left, upd_right, 1, 1, N);
}

void calc(int s, int a){
    int delta_angle = a-A[s];
    if (delta_angle != 0)
        update(delta_angle, s+1, N);
    A[s] = a;

    printf ("%.2f %.2f\n", ST[1].first, ST[1].second);
}

int main(){

    for (;;){
        if ( scanf("%d %d\n", &N, &C) != 2 ) break;

        for (int i = 1 ; i <= N ; ++i){
            if ( scanf("%d", &L[i]) != 1 ) return 1;
            P[i].first = 0.0; // x
            P[i].second = L[i];  // y
            A[i] = 180;
        }
        segtree_init(1, 1, N);
        memset(LAZY, 0, sizeof(LAZY));        
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