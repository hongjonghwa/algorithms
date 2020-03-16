#include<stdio.h>
#define INF 987654321
#define N 80

template<class T>
inline void SWAP(T & a, T & b){
  T temp = a; a = b; b = temp;
}

struct Tri {
  int a, b, c;
  Tri(int _a, int _b, int _c): a(_a), b(_b), c(_c) {}
  Tri(): a(0), b(0), c(0) {}
  bool operator<(const Tri rhs){
    return a < rhs.a;
  }
};

template <class T>
struct MinHeap{
  T *x;
  int n;
  MinHeap(int capacity) :n(0) {
    x = new T[capacity+1];
  }
  ~MinHeap(){
    delete[] x;
  }
  void push(T t){ // insert
    x[++n] =t;
    // bottom up!
    int i, p;
    for (i = n ; i > 1 && x[i] < x[p = i/2]; i = p)
      SWAP(x[i], x[p]);
  }
  T pop(){ // extract
    T ret = x[1];
    x[1] = x[n--];
    int i, c;
    for ( i = 1 ; (c = i*2) <= n ; i = c ){
      if (c + 1 <= n && x[c+1] < x[c] )
        c++;
      if (x[i] < x[c])
        break;
      SWAP(x[c], x[i]); 

    }
    // top down
    return ret;
  }  
} ;

MinHeap<Tri> heap(128);

int X[N+1][N+1];
int D[N+2][N+2];

void report(){
  for (int y = 0 ; y < N+2 ; ++y){
    for (int x = 0 ; x < N+2 ; ++x)
      printf("%10d", D[y][x]);
    printf("\n");
  } 
  printf("\n");
}

inline int min(int a, int b, int c){
  int ret = a;
  if (b < ret) ret = b;
  if (c < ret) ret = c;
  return ret;
}

void solv(){  
  for (int y = 0 ; y < N+2 ; ++y)
    for (int x = 0 ; x < N+2 ; ++x)
      D[y][x] = INF;
  for (int i = 0 ; i <= N+1 ; ++i) 
    D[i][0] = D[0][i] = D[i][N+1] = D[N+1][i] = 0;
  //report();

  MinHeap<Tri> pq(6400);
  pq.push( Tri(0, 1, 1) ); // distance, y, x;
  while (pq.n>0){
    Tri top = pq.pop();
    if (D[top.b][top.c] <= top.a + X[top.b][top.c]) continue;
    D[top.b][top.c] = top.a + X[top.b][top.c];
    pq.push(Tri(D[top.b][top.c], top.b-1, top.c));
    pq.push(Tri(D[top.b][top.c], top.b+1, top.c));
    pq.push(Tri(D[top.b][top.c], top.b, top.c-1));
    pq.push(Tri(D[top.b][top.c], top.b, top.c+1));
  }

  int answer = D[N][N];
  //report();
  printf("Answer is %d\n", answer);
}

int main(){
  /* heap 검증 */
  /*
  MinHeap <int> _heap(128);
  int xxx[] { 9, 4, 2, 5, 3, 5, 8, 0, 5, 1};
  for (int i = 0 ; i < 10 ; ++i)
    _heap.push(xxx[i]);
  for (int i = 0 ; i < 10 ; ++i)
    printf("%d\n", _heap.pop());
  return 0;
  */

  if (N==5) freopen("p081-083_matrix_sample.txt", "rt", stdin);
  else if (N==80) freopen("p081-083_matrix.txt", "rt", stdin);
  else printf("Wrong!");

  char t;
  for (int y = 1 ; y <= N ; ++y){
    for (int x = 1 ; x <= N ; ++x){
      scanf("%d", &X[y][x]);
      scanf("%c", &t);
    }
  }
  solv();
}
