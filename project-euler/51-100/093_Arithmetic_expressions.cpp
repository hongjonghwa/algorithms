// ! 93
#include <stdio.h>
#define N 4
#define LIMIT 1000

template <class T>
inline void SWAP(T& a, T& b){
    T tmp = a; a = b; b = tmp;
}

int gcd (int p, int q){
    return q==0 ? p : gcd(q, p%q);
}
struct Frac{
    int n, d; // numerator, denominator;    
    Frac() {n = 0; d = 1;}
    Frac(int _n) {n = _n; d = 1;}
    Frac(int _n, int _d) { n = _n; d = _d; }
};
Frac operator+(const Frac& lhs, const Frac& rhs) {
    Frac ret;
    ret.n = lhs.n*rhs.d + rhs.n*lhs.d;
    ret.d = lhs.d*rhs.d;
    return ret;
}
Frac operator-(const Frac& lhs, const Frac& rhs) {
    Frac ret;
    ret.n = lhs.n*rhs.d - rhs.n*lhs.d;
    ret.d = lhs.d*rhs.d;
    return ret;
}
Frac operator*(const Frac& lhs, const Frac& rhs) {
    Frac ret;
    ret.n = lhs.n*rhs.n;
    ret.d = lhs.d*rhs.d;
    return ret;
}
Frac operator/(const Frac& lhs, const Frac& rhs) {
    Frac ret;
    ret.n = lhs.n*rhs.d;
    ret.d = lhs.d*rhs.n;
    return ret;
}

int X[4] = {1,2,4,8};
bool VISIT[LIMIT+1];

void report(){ for (int i = 0 ; i < 4 ; ++i) printf("%d ", X[i]);  printf("\n"); }
void bt(int idx, Frac f){
    if (idx == 4){
        if (f.n % f.d == 0) {
            int t = f.n/f.d;
            if (t >= 0 && t <= LIMIT)
                VISIT[t] = 1;
        }
        return ;
    }
    if (idx == 1){
        bt(idx+1, Frac(X[0]) + Frac(X[1]));
        bt(idx+1, Frac(X[0]) - Frac(X[1]));
        bt(idx+1, Frac(X[0]) * Frac(X[1]));
        if (X[1]) bt(idx+1, Frac(X[0]) / Frac(X[1]));
        return;
    }
    bt(idx+1, f + Frac(X[idx]));
    bt(idx+1, f - Frac(X[idx]));
    bt(idx+1, f * Frac(X[idx]));
    if (X[idx]) bt(idx+1, f / Frac(X[idx]));
    bt(idx+1, Frac(X[idx]) + f);
    bt(idx+1, Frac(X[idx]) - f);
    bt(idx+1, Frac(X[idx]) * f);
    if (f.n) bt(idx+1, Frac(X[idx]) / f);
    return;
}

void perm(int l, int r){
    if (l == r){
        Frac f;
        bt(1, f);
        return;
    }
    for (int i = l ; i <= r ; ++i){
        SWAP(X[l],X[i]);
        perm(l+1, r);
        SWAP(X[l],X[i]);
    }
}

int solv(){
    for (int i = 1 ; i <= LIMIT ; ++i) VISIT[i] = 0;
    perm(0, 3);
    int ret;
    for (ret = 1 ; VISIT[ret+1] ; ++ret);
    return ret;
}
int main(){
    setbuf(stdout, 0);
    int longest = 0;
    for (int a = 1 ; a < 10 ; ++a){
        X[0] = a;
        for (int b = a+1 ; b < 10 ; ++b){
            X[1] = b;
            for (int c = b+1 ; c < 10 ; ++c){
                X[2] = c;
                for (int d = c+1; d < 10 ; ++d){
                    X[3] = d;
                    int t = solv();
                    if (t > longest){
                        longest = t;
                        printf(" %d %d %d %d  ==> %d \n", a,b,c,d,t);
                    }
                }
            }
        }
    }
    // X = {1,2,3,4};
}
