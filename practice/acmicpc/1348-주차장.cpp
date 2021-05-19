#include<iostream>
#include<cstring>
#include<vector>
#include<queue>
#define y first
#define x second
using namespace std;

int R, C;
char map[51][51];
vector <pair<int, int>> car, park;
int cpdist[100][100];

int DX[4] = {0,0,1,-1};
int DY[4] = {1,-1,0,0};
bool bound(int x, int y){
    if (y < 0 || y > R-1) return false;
    if (x < 0 || x > C-1) return false;
    return true;
}


// bfs
int dist[51][51];
queue<pair<int, int>> q;
void bfs(int c){
    memset(dist, 63, sizeof(dist));
    dist[car[c].y][car[c].x] = 0;
    q.push(make_pair(car[c].y, car[c].x));
    while (q.size()){
        int here_y = q.front().y, here_x = q.front().x; q.pop();
        for (int d = 0 ; d < 4 ; ++d){
            int there_y = here_y + DY[d], there_x = here_x + DX[d];
            if (bound(there_x, there_y) && map[there_y][there_x] != 'X' && dist[there_y][there_x] > dist[here_y][here_x]+1){
                dist[there_y][there_x] = dist[here_y][here_x]+1;
                q.push(make_pair(there_y, there_x));
            }
        }
    }
}
void report_dist(){
    for (int y = 0 ; y < R ; ++y){
        for (int x = 0 ; x < C ; ++x)
            cout << dist[y][x] << "\t";
        cout << "\n";
    }
}

void report_map(){
    for (int y = 0 ; y < R ; ++y){
        for (int x = 0 ; x < C ; ++x)
            cout << map[y][x];
        cout << "\n";
    }
}


int aMatch[100], bMatch[100];
bool aVisited[100];

bool dfs(int c, int cut){
    if (aVisited[c]) return false;
    aVisited[c] = true;
    for (unsigned p = 0 ; p < park.size() ; ++p){
        if (cpdist[c][p] > cut) continue;
        if (bMatch[p] == -1 || dfs(bMatch[p], cut)){
            bMatch[p] = c;
            aMatch[c] = p;
            return true;
        }
    }
    return false;
}

unsigned bipartite(int cut){
    memset(aMatch, -1, sizeof(aMatch));
    memset(bMatch, -1, sizeof(bMatch));
    unsigned ret = 0;
    for (unsigned c = 0 ; c < car.size() ; ++c){
        memset(aVisited, 0, sizeof(aVisited));
        if (dfs(c, cut)) ret++;
    }
    return ret;
}

int solv(){
    if (car.size() == 0) return 0;
    
    // bfs
    for (unsigned c = 0 ; c < car.size() ; ++c){
        bfs(c);
        // report_dist();
        for (unsigned p = 0 ; p < park.size() ; ++p){
            cpdist[c][p] = dist[park[p].y][park[p].x];
            // cout << c << " - " << p << " => " << cpdist[c][p] << "\n";
        }
    }

    // bs
    int ulimit = R*C+1, llimit = 0;
    int u = ulimit, l = llimit;
    while (l+1 < u){
        int m = (u+l)/2;
        if (bipartite(m) == car.size()) u = m;
        else l = m;
    }
    return u==ulimit ? -1 : u;
}


int main(){
    cin >> R >> C;
    
    for (int y = 0 ; y < R ; ++y){
        cin >> map[y];
        for (int x = 0 ; x < C ; ++x)
            switch (map[y][x]){
                case 'P': 
                    park.push_back(make_pair(y,x));
                    break;
                case 'C':
                    car.push_back(make_pair(y,x));
                    break;
            }
    }
    cout << solv() << "\n";
}