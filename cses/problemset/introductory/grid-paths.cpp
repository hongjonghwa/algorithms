#include<stdio.h>
#define OPTIMIZE3 0

char S[49];
int M[7][7];
int C[7][7];

int D[4][2] = {{1,0},{-1,0},{0,-1},{0,1}}; // D U L R

void report_C(){
  for (int y = 0 ; y < 7 ; ++y){
    for (int x = 0 ; x < 7 ; ++x)
      printf("%d", C[y][x]);
    printf("\n");
  }  
  printf("\n");
}

void report_X(){
  for (int y = 0 ; y < 7 ; ++y){
    for (int x = 0 ; x < 7 ; ++x)
      printf("%c", M[y][x] ? 'O' : '.');
    printf("\n");
  }  
  printf("\n");
}

int bt(int s, int y, int x){
  // printf("%d %d %d\n", s, y, x);
  if (y < 0 || y >= 7 || x < 0 || x >= 7 || M[y][x]) return 0;
  if (s == 48) return 1;
  if (y == 6 && x == 0 ) return 0;

  // pruning
  // 1)
  if (y == 0 && x > 0 && !M[y][x-1]) return 0;
  if (x == 0 && y > 0 && !M[y-1][x]) return 0;
  if (x == 6 && y > 0 && !M[y-1][x]) return 0;
  if (y == 6 && x < 6 && !M[y][x+1]) return 0;
  // 2) 폐쇄된 라인이 그려졌을 때 양쪽 모두 비어있으면 갈 방법이 없다.
  if (x > 0 && x < 6 && y > 0 && y < 6){
    if (M[y][x-1] && M[y][x+1] && !M[y-1][x] && !M[y+1][x]) return 0;
    if (!M[y][x-1] && !M[y][x+1] && M[y-1][x] && M[y+1][x]) return 0;
  }

  M[y][x] = 1;

  // 3) 도달 불가능한 단일 노드가 생긴다. --> 안하는 게 빠름
  int ret = 0;
  char impossible = 0;
  if (OPTIMIZE3)
    for (int d = 0 ; d < 4 ; ++d){
      int newy = y + D[d][0], newx = x + D[d][1];
      if (newy >= 0 && newy < 7 && newx >= 0 && newx < 7){
        C[newy][newx]--;
        if ( C[newy][newx] <= 0 && !M[newy][newx] && !(newy==6 && newx==0))
          impossible = 1;
      }
    }

  if (impossible) {
    // report_C();
    // report_X();
  }
  else if (S[s] == '?'){
    ret += bt(s+1, y+D[0][0], x+D[0][1]);
    ret += bt(s+1, y+D[1][0], x+D[1][1]);
    ret += bt(s+1, y+D[2][0], x+D[2][1]);
    ret += bt(s+1, y+D[3][0], x+D[3][1]);
  }
  else if (S[s] == 'D') ret += bt(s+1, y+D[0][0], x+D[0][1]);
  else if (S[s] == 'U') ret += bt(s+1, y+D[1][0], x+D[1][1]);
  else if (S[s] == 'L') ret += bt(s+1, y+D[2][0], x+D[2][1]);
  else if (S[s] == 'R') ret += bt(s+1, y+D[3][0], x+D[3][1]);

  M[y][x] = 0;
  if (OPTIMIZE3)
    for (int d = 0 ; d < 4 ; ++d){
      int newy = y + D[d][0], newx = x + D[d][1];
      if (newy >= 0 && newy < 7 && newx >= 0 && newx < 7)
        C[newy][newx]++;
    }


  return ret;
}

int main(){
  if (OPTIMIZE3)
    for (int y = 0 ; y < 7 ; ++y)
      for (int x = 0 ; x < 7 ; ++x)
        for (int d = 0 ; d < 4 ; ++d){
          int newy = y + D[d][0], newx = x + D[d][1];
          if (newy >= 0 && newy < 7 && newx >= 0 && newx < 7)
            C[newy][newx]++;
        }
  //report_C();

  if (scanf("%s", S) != 1) return -1;
  printf("%d", bt(0, 0, 0));
}