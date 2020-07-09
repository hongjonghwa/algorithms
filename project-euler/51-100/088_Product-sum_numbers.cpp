// ! 88
/*
k=2 : 4 = 2 × 2 = 2 + 2
k=3 : 6 = 1 × 2 × 3 = 1 + 2 + 3
k=4 : 8 = 1 × 1 × 2 × 4 = 1 + 1 + 2 + 4
k=5 : 8 = 1 × 1 × 2 × 2 × 2 = 1 + 1 + 2 + 2 + 2
k=6 : 12 = 1 × 1 × 1 × 1 × 2 × 6 = 1 + 1 + 1 + 1 + 2 + 6
k=7 : 숫자 7개로 만들수 있는 가장 작은 수 
k=8 : 
k=9 :
k=10:
k=11:
k=12:
*/

#include<stdio.h>
#include<assert.h>
#define MAXK 12000 // K값 
#define MAXN 24000 // 탐색범위 

bool used[MAXN+1]; // N 값의 사용 여부

int K[MAXK+1];     
int FACT[1000001];  // 최소 인수
inline bool isPrime(int i){ return i==FACT[i]; }
void e(){
  // for (int i =2 ; i <= 10000 ; ++i) PRIME[i] = 1;
  FACT[1] = -1;
  for (int i =2 ; i <= 1000000 ; ++i) FACT[i] = i;
  for (int i = 2 ; i <= 1000 ; ++i)
    if (FACT[i] == i)
      for (int j = i * i ; j <= 1000000 ; j += i)
        if (FACT[j] == j)
          FACT[j] = i;
}

// minimal product-sum
int minpsum(int k){
  return 0;
}

bool _D = 0;
int DEBUG[12000]; 

void bt(int n, int lvl, int sum, int product, int N, int gte){
  if (n < 1) assert(false);

  if (lvl >= 1){
    DEBUG[lvl] = n;
    int s = sum+n;
    int p = product*n;

    if (s <= p){
      int k = lvl + 1 + (p-s);

      if (k <= MAXK && !K[k]) {
        // _DEBUG
        if (_D){
          printf("  ");
          for (int i = 0 ; i <= lvl ; ++i)
            printf(" %d", DEBUG[i]);
          for (int i = 0 ; i < p - s ; ++i)
            printf(" 1");
          printf(" => cnt:%d\n", N);
          printf("   update : K:%d with %d\n", k, N );
        }
        
        K[k] = N;
        used[N] = 1;
      }
    }
  }

  for (int i = gte ; i*i <= n ; ++i){
    if (n % i == 0){
      DEBUG[lvl] = i;
      bt(n/i, lvl+1, sum+i, product*i, N, i);
    }
  }
}

void factorization (int n){ // x >= 2
  if (_D) printf("### N = %d ###\n", n);
  bt(n, 0, 0, 1, n, 2);
}


int main(){
  e();

  for (int i = 4 ; i <= MAXN ; ++i)
    if (!isPrime(i))
      factorization(i);

  for (int i = 2 ; i <= MAXK ; ++i)
    if (K[i] == 0){
      printf("K[%d] is null \n", i);
      return 0;
    }
  

  int sum = 0;
  for (int i = 4 ; i <= MAXN ; ++i)
    if (used[i]){
      // printf("%d\n", i);
      sum += i;
    }
  printf("Answer is %d\n", sum);
  // for (int i = 2 ; i <= K ; ++i)  printf("%d %d\n", i, minpsum(i));
}
// 2<=K<= 48 --> 621 