#include<stdio.h>
/*       0 
 *        \
 *         1     2
 *       /   \  / 
 *     9       3
 *    / \     /
 *   8   7 - 5 - 4
 *        \
 *         6
 */


int D[10] = { 1,2,3,4,5,6,7,8,9,10 };

bool magic(){
    int sum = D[0] + D[1] + D[3];
    if (sum != D[2] + D[3] + D[5]) return false;
    if (sum != D[4] + D[5] + D[7]) return false;
    if (sum != D[6] + D[7] + D[9]) return false;
    if (sum != D[8] + D[9] + D[1]) return false;
    return true;
}
int SEQUENCE[15] = { 0,1,3, 2,3,5, 4,5,7, 6,7,9, 8,9,1 };
long long int seq() {
    long long int ret = 0;
    for (int i = 0 ; i < 15 ; ++i){
        if (D[SEQUENCE[i]] >= 10) ret *= 100;
        else ret *= 10;
        ret += D[SEQUENCE[i]];
    }
    return ret;
}
template<class T>
inline void SWAP(T &a, T &b){
    T tmp = a;
    a = b;
    b = tmp;
}

void permutation_test(int n, int idx){
    if (idx == n-1){
        printf("#");
        for (int i = 0 ; i < n ; ++i)
            printf(" %d", D[i]);
        printf("\n");
        return;
    }
    for (int i = idx; i < n ; ++i){
        SWAP(D[idx], D[i]);
        permutation_test(n, idx+1);
        SWAP(D[idx], D[i]);
    }
}
long long int best = -1;

void check(){
    if (D[1]==10 || D[3]==10 || D[5]==10 || D[7]==10 || D[9]==10) return; // 17 digits

    // D[0] is lowest external node
    if (D[0] > D[2]) return;
    if (D[0] > D[4]) return;
    if (D[0] > D[6]) return;
    if (D[0] > D[8]) return;

    if (!magic()) return;
    long long int t = seq();
    if (t > best) best = t;
}
void permutation(int n, int idx){
    if (idx == n-1){
        check();
        return;
    }
    for (int i = idx; i < n ; ++i){
        SWAP(D[idx], D[i]);
        permutation(n, idx+1);
        SWAP(D[idx], D[i]);
    }
}


int main(){
    permutation_test(4, 0);
    permutation(10, 0);
    printf("Answer is %lld\n", best);
}
