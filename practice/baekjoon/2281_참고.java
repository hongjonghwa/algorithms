/*
이 소스는 봐도 이해가 안됨
2281_데스노트.java
https://www.acmicpc.net/problem/2281
*/

import java.util.*;

public class Main {
  static int l[] = new int[1001];
  static int d[][] = new int[1001][1001];

  public static void main(String args[]){
    Scanner sc = new Scanner(System.in);

    int N = sc.nextInt();
    int M = sc.nextInt();
    for(int i = 1; i <= N; i++)
      l[i] = sc.nextInt();

    Arrays.fill(d[0], 1000000001);
    d[0][M] = 0;

    for(int i = 1; i <= N; i++){
      Arrays.fill(d[i], 1000000001);
      for(int j = 1; j <= M; j++){
        if(j + l[i] + 1 <= M) d[i][j + l[i] + 1] = d[i - 1][j];
        d[i][l[i]] = Math.min(d[i][l[i]], d[i - 1][j] + (M - j) * (M - j));
      }
    }

    int ans = d[N][1];
    for(int i = 2; i <= M; i++)
      ans = Math.min(ans, d[N][i]);

    System.out.println(ans);
  }
}