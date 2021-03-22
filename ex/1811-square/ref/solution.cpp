#define SIZE 64

int img[SIZE+1][SIZE+1];
int S[SIZE+1][SIZE+1];

int solve(unsigned char image[SIZE][SIZE]){
    // 편의를 위해 1-indexed 로 수정
    for(int i=1;i<=SIZE;i++) for(int j=1;j<=SIZE;j++) img[i][j] = image[i-1][j-1];
    for(int i=1;i<=SIZE;i++) for(int j=1;j<=SIZE;j++) S[i][j] = img[i][j] + img[i-1][j-1] - img[i-1][j] - img[i][j-1]; 

    int ans = 0;
    for(int len=9;len<=SIZE;len++){
        for(int y=1;y<=SIZE-len;y++) for(int x=1;x<=SIZE-len;x++){
            if( S[y][x] > 0 && S[y+len][x+len] > 0 && S[y+len][x] < 0 && S[y][x+len] < 0 ) ans++;
        }
    }

    return ans;
}
