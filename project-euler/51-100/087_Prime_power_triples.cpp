#include<stdio.h>
#include<time.h>

bool P[10001];
int X[1229];
int R[2000000];

void e(){
  for (int i = 2 ; i <= 10000 ; ++i)
    P[i] = 1;
  
  for (int i = 1 ; i <= 100 ; ++i)
    if (P[i])
      for (int j = i*i ; j <= 10000 ; j+=i)
        P[j] = 0;
}
template<class T>
inline void SWAP(T &a, T & b){
  T t = a; a = b; b = t;
}
void qsort (int lo, int hi){
  if (lo >= hi) return;
  int m = lo;
  for (int i = lo+1; i <=  hi ; ++i)
    if (R[lo] > R[i]) 
      SWAP(R[++m], R[i]);
  SWAP(R[lo], R[m]);

  qsort(lo, m-1);
  qsort(m+1, hi);
}
int diffcnt (int lo, int hi){
  int cnt = 0;
  for (int i = 1; i<= hi ; ++i)
    if (R[i-1] == R[i])
      ++cnt;
  return hi - lo + 1 - cnt;
}


int main(){
  long long int clk = clock();
  e();
  int cnt = 0;
  for (int i = 1 ; i <= 10000 ; ++i)
    if (P[i]) 
      X[cnt++] = i;
  // printf("[%d] \n", cnt );
  // for (int i = 0 ; i < cnt ; ++i)  printf("[%d] %d\n", i, X[i]);

  int res = 0;
  int T = 50000000; // 50000000
  for (int i =  0 ; i < cnt ; ++i){
    int i4 = X[i]*X[i]*X[i]*X[i];
    if (i4 >= T) break;
    for (int j =  0 ; j < cnt ; ++j){
      int j3 = X[j]*X[j]*X[j];
      if (j3 >= T) break;
      // 최적화 (Binary Search) 불필요, 복잡도 N
      for (int k =  0 ; k < cnt ; ++k){
        int k2 = X[k]*X[k];
        int v = i4 + j3 + k2;
        if (v > T) break;
        R[res] = v;
        res++;
        
      }
    }
  }
  printf("RES :%d \n", res);

  // ? 복잡도 N Log N --> 정렬 없이는 못하나
  qsort(0, res-1);
  int uniq = diffcnt(0, res-1);
  printf("UNIQ :%d \n", uniq);

  printf("Execution time :%f \n", ((double)clock()-clk)/CLOCKS_PER_SEC);
}
