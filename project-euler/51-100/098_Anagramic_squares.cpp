#include <stdio.h>
#include <assert.h>

void solve(char * s, char * s1, char * s2, int len);
void bt(int idx);
void probe();

char words[2000][20];
int words_len[2000];
int words_total; 
char words_sorted[2000][20];

int integer_square_root(int n){
  int lo = 0, hi = n+1;
  while(lo + 1 < hi){
    int m = (lo + hi)/2;
    if (m*m > n) hi = m;
    else lo = m;
  }
  return lo*lo == n ? lo : -1;
}


int main(){
  freopen("p098_words.txt", "r", stdin);

  char str[20000];
  int str_len = 0;

  scanf("%s", str);
  while (str[str_len]) ++str_len;
  assert(str_len == 16345);

  bool opened = false;
  for (int i =  0 ; i < str_len ; ++i)
    if (str[i] == '"'){
      if (opened) ++words_total;
      opened = !opened;
    }else if (opened){
      words[words_total][words_len[words_total]++] = str[i];
    }

  // all words sort
  for (int k = 0 ; k < words_total ; ++k){
    for (int i = 0 ; i < words_len[k] ; ++i) words_sorted[k][i] = words[k][i];
    for (int i = 1 ; i < words_len[k] ; ++i){
      char t = words_sorted[k][i];
      int j;
      for (j = i ; j > 0 && words_sorted[k][j-1] > t ; --j)
        words_sorted[k][j] = words_sorted[k][j-1];
      words_sorted[k][j] = t;
    }
  }

  // test
  printf("### ASSERT : sort\n");
  int longest = 0;
  for (int i = 0 ; i < words_total ; ++i){
    if (words_len[i] < longest) continue;
    if (words_len[i] > longest) longest = words_len[i];
    printf("%d\t%d\t", i, words_len[i]);
    printf("%s %s \n", words[i], words_sorted[i]);
  }

  // report all anagram set
  printf("### Anagrams\n");
  int cnt = 0;
  for (int i = 0 ; i < words_total ; ++i){
    for (int j = i+1 ; j < words_total ; ++j){
      if (words_len[i] != words_len[j]) continue;
      bool palindromic = 1;
      for (int k = 0 ; k < words_len[i]; ++k)
        if (words_sorted[i][k] != words_sorted[j][k]){
          palindromic = 0;
          break;
        }
      if (!palindromic) continue;

      printf("[%d]\t", ++cnt);
      solve(words_sorted[i], words[i], words[j], words_len[i]);
    }
    // if (cnt >= 4) break;
  }
}

char * sorted;
char * str1;
char * str2;
int str_len;
int str1map[20];
int str2map[20];
bool used_digit[10];
int nums[20];

void solve(char * s, char * s1, char * s2, int len){

  // to global variable
  sorted = s;
  str1 = s1;
  str2 = s2;
  str_len = len;

  // init
  for (int i = 0 ; i < str_len ; ++i) str1map[i] = str2map[i] = -1;
  for (int i = 0 ; i < 10 ; ++i) used_digit[i] = 0;

  for (int i = 0 ; i < str_len ; )
    for (int j = 0 ; j < str_len ; ++j)
      if (sorted[j] == str1[i])
         str1map[i++] = j;

  for (int i = 0 ; i < str_len ; )
    for (int j = 0 ; j < str_len ; ++j)
      if (sorted[j] == str2[i])
         str2map[i++] = j;


  // report
  for (int i = 0 ; i < str_len ; ++i) printf("%c", sorted[i]); 
  printf(" ");
  for (int i = 0 ; i < str_len ; ++i) printf("%c", str1[i]);
  printf(" ");
  for (int i = 0 ; i < str_len ; ++i) printf("%c", str2[i]); 

  printf("\t(mapping ");

  for (int i = 0 ; i < str_len ; ++i) printf("%d", str1map[i]); 
  printf(" ");
  for (int i = 0 ; i < str_len ; ++i) printf("%d", str2map[i]); 
  printf(")\n");

  bt(0);
}



void bt(int idx){
  // printf("bt %d %d \n", idx, str_len);
  if (idx == str_len){
    probe();
    return ;
  }
  if (idx > 0 && sorted[idx] == sorted[idx-1]){
    nums[idx] = nums[idx-1];
    bt(idx+1);
    return;
  }
  // printf("search \n");
  for (int i = 0 ; i < 10 ; ++i){
    if (used_digit[i]) continue;
    used_digit[i] = 1;
    nums[idx] = i;
    bt(idx+1);
    used_digit[i] = 0;
  }

}

void probe(){
  if (nums[str1map[0]] == 0 || nums[str2map[0]] == 0) return ; // leading zero 

  long long int num1 = 0, num2=0;
  for (int i = 0 ; i < str_len ; ++i){
    num1 *= 10;
    num1 += nums[str1map[i]];
  }
  for (int i = 0 ; i < str_len ; ++i){
    num2 *= 10;
    num2 += nums[str2map[i]];
  }

  int num1_sqrt = integer_square_root(num1);
  int num2_sqrt = integer_square_root(num2);
  if (num1_sqrt == -1 || num2_sqrt == -1) return;

  // report
  printf("    (");
  for (int i = 0 ; i < str_len ; ++i) printf("%d", nums[i]); 
  printf(")\t");
  printf("%I64d = %d*%d \t %I64d = %d*%d", num1, num1_sqrt, num1_sqrt, num2, num2_sqrt, num2_sqrt);
  printf("\n");


}




