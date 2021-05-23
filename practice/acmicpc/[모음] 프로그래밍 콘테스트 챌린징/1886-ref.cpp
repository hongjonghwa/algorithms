#include<cstdio>
#include<iostream>
#include<cstring>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;
const int INF = 0x3f3f3f3f;
const int maxn1 = 15;
const int maxn2 = 100000;
int n, m;
int dis[maxn1][maxn1][maxn1][maxn1], go[4][2] = { 1,0,-1,0,0,1,0,-1 };
// dis: the first two savers, the last two savers
char maps[maxn1][maxn1];
vector<int> px, py, dx, dy;  //px= people_x     dx=door_x
vector<int> V[maxn2]; // for bipartite graphs
int match[maxn2], used[maxn2]; //divisional graph
typedef pair<int, int> P;
void bfs(int a, int b) {
	queue<P> Q;
	queue<int> S;
	Q.push(P(a, b));
	S.push(1);
	while (!Q.empty()) {
		P p = Q.front();
		int step = S.front();
		Q.pop(); S.pop();
		for (int i = 0; i < 4; i++) {
			int xx = p.first + go[i][0], yy = p.second + go[i][1];
			if (xx > 1 && xx < n && yy>1 && yy < m) {
				if (dis[xx][yy][a][b] > step && maps[xx][yy] == '.') { 
					dis[xx][yy][a][b] = step;
					Q.push(P(xx, yy));
					S.push(step + 1);
				}
			}
		}
	}
}
bool dfs(int aim) {
	used[aim] = 1;
	for (int i = 0; i < V[aim].size(); i++) {
		int to = V[aim][i];
		if (match[to] == -1 || !used[match[to]] && dfs(match[to])) {
			match[aim] = to;
			match[to] = aim;
			return 1;
		}
	}
	return false;
}
inline void Connect(int a, int b) {
	V[a].push_back(b);
	V[b].push_back(a);
}
int main() {
	int T = 1;
	while (T--) {
		memset(dis, INF, sizeof(dis));
		px.clear(); py.clear();
		dx.clear(); dy.clear();
		cin >> n >> m;
		int all = n * m;
		char s[maxn1];
		for (int i = 1; i <= n; i++) { 
			scanf("%s", s);
			int end = strlen(s);
			for (int j = 0; j < end; j++) {
				maps[i][j + 1] = s[j];
				if (s[j] == 'D') {
					dx.push_back(i);
					dy.push_back(j + 1);
				}
				else if (s[j] == '.') {
					px.push_back(i);
					py.push_back(j + 1);
				}
			}
		}
		int ds = dx.size(), ps = px.size();  //ds= dx_size = door_x.size         
		for (int i = 0; i < ds; i++) {
			bfs(dx[i], dy[i]);
		}
		int max_d = all * ds;  //max_d = max_door
		int clear_flag = all * ds + ps;
		for (int i = 0; i <= clear_flag; i++) V[i].clear();
		for (int i = 0; i < ds; i++) {
			for (int j = 0; j < ps; j++) {
				if (dis[px[j]][py[j]][dx[i]][dy[i]] != INF) {
					for (int k = dis[px[j]][py[j]][dx[i]][dy[i]]; k <= all; k++) { //k <= ps
						Connect((k - 1)*ds + i, max_d + j);
					}
				}
			}
		}
		if (ps == 0) {
			cout << 0 << endl;
			continue;
		}
		memset(match, -1, sizeof(match));
		int ok = 0;
		int res = 0;
		for (int i = 0; i < max_d; i++) { // bipartite graph
			memset(used, 0, sizeof(used));
			if (dfs(i)) {
				if (++res == ps) {
					cout << (i / ds) + 1 << endl;
					ok = 1;
					break;
				}
			}
		}
		if (ok == 0) cout << "impossible" << endl;
	}
	return 0;
}