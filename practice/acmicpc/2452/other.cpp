#include <stdio.h>
#include <memory.h>
#include <queue>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;


int arr[102][102];
int arr2[102][102];
vector<int> v[10001];

vector< pair<int, int> > pv;
int pvIdx[10001];
int q[1000001];
int rear = 0, front = 0;

int check[10001];

int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

int main(){
    int T,M,N;

	freopen("eval_input.txt","rt",stdin);    
    scanf("%d", &T);
    
    for(int t = 1; t <= T; ++t){
        
        rear = 0, front = 0;
        pv.clear();
        for(int i = 0 ; i < 10001; ++i){
            v[i].clear();
            check[i] = 0;
        }
        
        
        scanf("%d%d", &M,&N);
        
        memset(arr, -1, sizeof(arr));
        memset(arr2, -1, sizeof(arr2));
        
        for(int i = 1; i<=M; i++){
            for(int j = 1; j<=N; j++){
                scanf("%d", &arr[i][j]);
            }
        }
        
        int group = 0;
        int cp = 0, row, col;
        for(int i = 1; i<=M; i++){
            for(int j = 1; j<=N; j++){
                if(arr2[i][j] == -1){
                    cp = arr[i][j];
                    ++group;
                    
                    rear = 0;
                    front = 0;
                    
                    q[++rear] = i;
                    q[++rear] = j;
                    arr2[i][j] = group;
                    
                    while(rear - front){
                        row = q[++front];
                        col = q[++front];
                        
                        for(int d = 0; d < 4; ++d){
                            if(arr[row + dy[d]][col + dx[d]] == cp && arr2[row + dy[d]][col + dx[d]] == -1) {
                                q[++rear] = row+dy[d];
                                q[++rear] = col+dx[d];
                                arr2[row + dy[d]][col + dx[d]] = group;
                            } else if(arr2[row + dy[d]][col+ dx[d]] != -1 && arr2[row][col] != arr2[row + dy[d]][col+ dx[d]]){
                                pv.push_back(make_pair(arr2[row + dy[d]][col + dx[d]], arr2[row][col]));
                                pv.push_back(make_pair(arr2[row][col], arr2[row + dy[d]][col + dx[d]]));
                            }
                        }
                    }
                }
            }
        }
        
        sort(pv.begin(), pv.end());
        pv.erase(unique(pv.begin(), pv.end()), pv.end());
        
        int pvSize = (int)pv.size();
        for(int i = 0; i < pvSize; ++i){
            pvIdx[pv[i].first] = i+1;
        }
        
        int limit = M*N;
        limit = limit / 4;
        int min = 0x7fffffff;
        int cnt = 0;
        int hg = group/2;
        int acnt = 0;
        for(int i = hg; i <= group; ++i){
            if(++acnt > limit) break;
            cnt = -1;
            memset(check, 0, sizeof(check));
            
            rear = 0;
            front = 0;
            q[++rear] = i;
            check[i] = 1;
            int size = rear - front;
            
            while(size){
                cnt++;
                if(cnt >= min) break;
                for(int j = 0; j < size; ++j){
                    int a = q[++front];
                    for(int k= pvIdx[a-1] ; k < pvIdx[a]; ++k){
                        if(!check[pv[k].second]){
                            check[pv[k].second] = 1;
                            q[++rear] = pv[k].second;
                        }
                    }
                }
                size = (int)rear - front;
            }
            min = min > cnt ? cnt : min;
        }
        
        acnt = 0;
        for(int i = hg -1; i >=1 ; --i){
            if(++acnt > limit) break;
            cnt = -1;
            memset(check, 0, sizeof(check));
            
            rear = 0;
            front = 0;
            q[++rear] = i;
            check[i] = 1;
            int size = rear - front;
            
            while(size){
                cnt++;
                if(cnt >= min) break;
                for(int j = 0; j < size; ++j){
                    int a = q[++front];
                    for(int k= pvIdx[a-1] ; k < pvIdx[a]; ++k){
                        if(!check[pv[k].second]){
                            check[pv[k].second] = 1;
                            q[++rear] = pv[k].second;
                        }
                    }
                }
                size = (int)rear - front;
            }
            min = min > cnt ? cnt : min;
        }
        printf("#%d %d\n", t,min);

    }
    return 0;
}
