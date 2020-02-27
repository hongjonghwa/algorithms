#include <bits/stdc++.h>
#define F first
#define S second
#define PB push_back
#define MP make_pair
#define REP(i,a,b) for (int i = a; i <= b; ++i)

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> pi;

const int n = 10;
vi permutation;
bool chosen[n+1];

void permutation_search(){
  if (permutation.size() == n){
    // 순열을 처리한다
  }else{
    for (int i = 1 ; i <= n ; ++i){
      if (chosen[i]) continue;
      chosen[i] = true;
      permutation.push_back(i);
      permutation_search();
      chosen[i] = false;
      permutation.pop_back();
    }
  }
}

int main(){
  ios::sync_with_stdio(0);
  cin.tie(0);

  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
  
  long long x = 123456789123456789LL;
  __int128_t bigint = 1; // 128bit 정수형 (-1e38 ~ 1e38)
  long double precisefloat= 1.0; //80bit 실수형, double 은 64bit
  
  vector<pi> v;
  v.PB(MP(1,2));
  v.PB(MP(3,4));
  int d = v[1].F + v[1].S;

  int r = 0;
  REP(i,1,n){
    r+= i;
  }

  // permutation 1
  permutation_search();
  // permutation 2
  do{
    // 순열을 처리한다
  } while (next_permutation(permutation.begin(), permutation.end()))
  
}