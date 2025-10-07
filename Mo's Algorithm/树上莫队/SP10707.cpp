/*
  树上莫队模板题
  按照步骤将树上问题转化为普通莫队即可 注意经过两次的认为没有经过
*/

#include<algorithm>
#include<bitset>
#include<climits>
#include<cmath>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iomanip>
#include<iostream>
#include<map>
#include<queue>
#include<set>
#include<string>
#include<unordered_map>
#include<unordered_set>
#include<vector>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
constexpr int mod = 998244353;
constexpr ll inf = 1e18;
constexpr ld eps = 1e-8;
constexpr int intinf = 1e9;

constexpr int maxn = 2e5 + 10;
constexpr int N = 20;
constexpr int Base = 13;
constexpr int dx[] = { 0,0,1,-1 };
constexpr int dy[] = { 1,-1,0,0 };
constexpr int primes[] = { 2,3,5,7,11,13,17,19,23,29,31,37,41,43 };
//these primes' product > 1e16

int n, m, a[maxn], b[maxn], f[maxn], tim, st[maxn], ed[maxn], seg[maxn], fa[maxn][N], dep[maxn];
int ans, res[maxn];
bool vis[maxn];


struct node {
    int l, r, kl, id, lca;
} q[maxn];

bool cmp(node c1, node c2) {
    if (c1.kl == c2.kl) return c1.r < c2.r;
    return c1.kl < c2.kl;
}

vector<int> edge[maxn];

void add(int u, int v) {
    edge[u].push_back(v);
}

void dfs(int u, int father) {
    st[u] = ++tim; seg[tim] = u;
    fa[u][0] = father;
    dep[u] = dep[father] + 1;
    for (int i = 1; i < N; i++)
        fa[u][i] = fa[fa[u][i - 1]][i - 1];
    for (auto v : edge[u]) {
        if (v == father) continue;
        dfs(v, u);
    }
    ed[u] = ++tim; seg[tim] = u;
}

int get_lca(int u, int v) {
    if (dep[u] < dep[v]) swap(u, v);
    int k = dep[u] - dep[v];
    for (int i = N - 1; i >= 0; i--)
        if ((k >> i) & 1) u = fa[u][i];
    if (u == v) return u;
    for (int i = N - 1; i >= 0; i--)
        if (fa[u][i] != fa[v][i])
            u = fa[u][i], v = fa[v][i];
    return fa[u][0];
}

void change(int x) {
    int c = a[x];
    if (vis[x]) {
        f[c]--;
        if (f[c] == 0) ans--;
    }
    else {
        f[c]++;
        if (f[c] == 1) ans++;
    }
    vis[x] ^= 1;
}

void solve() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> a[i], b[i] = a[i];
    sort(b + 1, b + n + 1);
    int len = unique(b + 1, b + n + 1) - b - 1;
    for (int i = 1; i <= n; i++)
        a[i] = lower_bound(b + 1, b + len + 1, a[i]) - b;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        add(u, v); add(v, u);
    }
    dfs(1, 0);
    int B = sqrt(tim);
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        int lca = get_lca(u, v);
        if (dep[u] > dep[v]) swap(u, v);
        q[i].id = i;
        if (u == lca) {
            q[i].l = st[u]; q[i].r = st[v];
            q[i].kl = (q[i].l - 1) / B + 1;
            q[i].lca = 0;
        }
        else {
            q[i].l = ed[u]; q[i].r = st[v];
            q[i].kl = (q[i].l - 1) / B + 1;
            q[i].lca = lca;
        }
    }
    sort(q + 1, q + m + 1, cmp);
    int l = 1, r = 0;
    for (int i = 1; i <= m; i++) {
        while (l > q[i].l) change(seg[--l]);
        while (r < q[i].r) change(seg[++r]);
        while (l < q[i].l) change(seg[l++]);
        while (r > q[i].r) change(seg[r--]);
        if (q[i].lca != 0) {
            change(q[i].lca);
            res[q[i].id] = ans;
            change(q[i].lca);
        }
        else res[q[i].id] = ans;
    }
    for (int i = 1; i <= m; i++)
        cout << res[i] << "\n";
}

signed main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int T = 1;
    while (T--) {
        solve();
    }
    return 0;
}
