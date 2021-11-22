#include <bits/stdc++.h>

using namespace std;

// prime
const int MAXN = 1000000;
bool PRIME[MAXN+5];
void eratosthenes_sieve(){
  memset(PRIME, 1, sizeof(PRIME));
  PRIME[0] = PRIME[1] = 0;
  for (int i = 2 ; i <= 1000 ; ++i)
    if (PRIME[i])
      for (int j = i*i ; j <= MAXN ; j += i)
        PRIME[j] = 0;
  // for (int i = 0, c = 0 ; i <= 100 ; ++i) if (P[i]) cout << ++c << ":" << i << "\n"; // test
}


// union 횟수
int merge_cnt;

// union-find
int parent[MAXN+5];
void init(int sz){ 
  merge_cnt = 0;
  for (int i = 0 ; i < sz ; ++i) parent[i] = i; 
}
int find(int u){ 
  return u == parent[u] ? u : parent[u] = find(parent[u]); 
}
void merge(int u, int v){ 
  u = find(u), v = find(v); 
  if (u==v) return;
  merge_cnt++;
  parent[v] = u;
}


long long solv(long long a, long long b, long long p){
  int sz = b-a+1;
  init(sz);

  int e = min(MAXN, sz);
  for (long long i = p ; i <= e ; i++){
    if (PRIME[i]){
      // first node
      long long first = (a-1)/i*i + i;
      // if (first > b) break; // 불필요
      for (long long next = first + i ; next <= b ; next += i)
        merge(first-a, next-a);
    }
  }
  return sz - merge_cnt;
}


int main(){
  ios::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
  
  long long C, A, B, P;
  cin >> C;
  eratosthenes_sieve();

  for (int test = 1 ; test <= C ; ++test){
    cin >> A >> B >> P;
    long long answer = solv(A, B, P);
    cout << "Case #" << test << ": " << answer << "\n";
  }
  
}