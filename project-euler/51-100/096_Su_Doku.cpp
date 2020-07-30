#include <stdio.h>
int BIT_LEN[1023];

void init();
void report(char grid[9][9]);

void assign(int y, int x, int c, int candidates[9][9]){
  for (int i = 0 ; i < 9 ; ++i)
    candidates[y][i] &= ~(1<<c); // unset
  for (int i = 0 ; i < 9 ; ++i)
    candidates[i][x] &= ~(1<<c); // unset
  int offset_y = (y/3)*3 , offset_x = (x/3)*3;
  for (int dy = 0 ; dy < 3 ; ++dy)
    for (int dx = 0 ; dx < 3 ; ++dx)
      candidates[offset_y+dy][offset_x+dx] &= ~(1<<c); // unset
}

int bt(char prev_grid[9][9], int candidates[9][9]){
  char grid[9][9]; // copy of grid
  for (int y = 0 ; y < 9 ; ++y)
    for (int x = 0 ; x < 9 ; ++x)
      grid[y][x] = prev_grid[y][x];

  int find_y = -1, find_x = -1, best = 987654321;
  for (int y = 0 ; y < 9 ; ++y)
    for (int x = 0 ; x < 9 ; ++x)
      if (!grid[y][x]){
        int num_of_candidates = BIT_LEN[candidates[y][x]];
        if (num_of_candidates == 0) return 0; // conflict
        if (num_of_candidates < best){
          find_y = y, find_x = x, best = num_of_candidates;
        }
      }
  if (find_y == -1) {
    report(grid);
    return grid[0][0] * 100 + grid[0][1] * 10 + grid[0][2]; // answer
  }

  for (int c = 1 ; c < 10 ; ++c)
    if (candidates[find_y][find_x] & (1<<c)){
      grid[find_y][find_x] = c;
      int copy_of_candidates[9][9];  // copy of candidates
      for (int y = 0 ; y < 9 ; ++y)
        for (int x = 0 ; x < 9 ; ++x)
          copy_of_candidates[y][x] = candidates[y][x];
      assign(find_y, find_x, c, copy_of_candidates);
      int ret = bt(grid, copy_of_candidates);
      if (ret) return ret;
    }

  return 0;
    
}
int solve(char grid[9][9]){
  int candidates[9][9];
  for (int y = 0 ; y < 9 ; ++y)
    for (int x = 0 ; x < 9 ; ++x)
      candidates[y][x] = 1022;
  for (int y = 0 ; y < 9 ; ++y)
    for (int x = 0 ; x < 9 ; ++x)
      if (grid[y][x])
        assign(y, x, grid[y][x], candidates);
  return bt(grid, candidates);
}

int main(){
  init();
  freopen("p096_sudoku.txt", "r", stdin);
  char t1[10], t2[10];
  char grid[9][9];
  int answer = 0;
  for (int i = 0 ; i < 50 ; ++i){
    // input
    scanf("%s%s", t1, t2 );
    printf("\n\n## %s %s ##\n\n", t1, t2);
    for (int j = 0 ; j < 9 ; ++j){
      scanf("%s", t1);
      for (int k = 0 ; k < 9 ; ++k)
        grid[j][k] = t1[k]-'0';
    }
    // report
    report(grid);
    // solve
    int ret = solve(grid);
    printf("%d \n", ret);
    answer += ret;
    // if (i == 2) break;
  }
  printf("Answer is %d\n", answer);
}

void init(){
  for (int i = 2 ; i < 1023 ; i += 2){
    int x = i;
    while (x){
      if (x&1) BIT_LEN[i]++;
      x /= 2;
    }
  }
}

void report(char grid[9][9]){
  for (int y = 0 ; y < 9 ; ++y){
    if (y % 3 == 0) 
      printf("+---+---+---+\n");
    printf("|");
    for (int x = 0 ; x < 9 ; ++x){
      if (grid[y][x]) 
        printf("%d", grid[y][x]);
      else 
        printf(" ");
      if (x % 3 == 2) printf("|");
    }
    printf("\n");
  }
  printf("+---+---+---+\n");
}
