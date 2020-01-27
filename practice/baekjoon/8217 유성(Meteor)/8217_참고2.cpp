// http://jason9319.tistory.com/282
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;
typedef long long ll;
ll n, m, k, x[300030], y[300030], z[300030], lo[300030], hi[300030], tree[300030], g[300030];
vector<vector<ll>> unv, qry;
void update(ll pos, ll val) {
    while (pos <= m) {
        tree[pos] += val;
        pos += (pos&-pos);
    }
}
ll query(int pos) {
    ll ret = 0;
    while (pos > 0) {
        ret += tree[pos];
        pos -= (pos&-pos);
    }
    return ret;
}
void go(int h) {
    if (y[h] >= x[h])
        update(x[h], z[h]), update(y[h] + 1, -z[h]);
    else
        update(1, z[h]), update(y[h] + 1, -z[h]), update(x[h], z[h]);
}
int main() {
    scanf("%lld%lld", &n, &m);
    unv.resize(n + 1);
    for (int i = 1, t; i <= m; i++) {
        scanf("%lld", &t);
        unv[t].push_back(i);
    }
    for (int i = 1; i <= n; i++)
        scanf("%lld", &g[i]);
    scanf("%lld", &k);
    qry.resize(k + 1);
    for (int i = 1; i <= k; i++) 
        scanf("%lld%lld%lld", &x[i], &y[i], &z[i]);
    for (int i = 1; i <= n; i++) 
        lo[i] = 1, hi[i] = k + 1;
    bool f = 1;
    while (f) {
        f = 0;
        memset(tree, 0, sizeof(tree));
        for (int i = 1; i <= n; i++) {
            if (lo[i] < hi[i]) {
                qry[(lo[i] + hi[i]) >> 1].push_back(i);
                f = 1;
            }
        }
        for (int i = 1; i <= k; i++) {
            go(i);
            while (qry[i].size()) {
                int idx = qry[i].back();
                qry[i].pop_back();
                ll sum = 0;
                for (auto next : unv[idx]) {
                    sum += query(next);
                    if (sum >= g[idx])break;
                }
                if (sum >= g[idx])
                    hi[idx] = i;
                else
                    lo[idx] = i + 1;
            }
        }
    }
    for (int i = 1; i <= n; i++)
        if (lo[i] == k + 1)
            puts("NIE");
        else
            printf("%d\n", lo[i]);
    return 0;
}

