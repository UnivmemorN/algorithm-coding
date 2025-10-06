/*
    本题的难点不在于线段树 而在于对题目询问的分析
    对于根会变的题目 我们通常可以假设 1 为根 然后维护换根的操作 而非真正的每次都换根
    
    考虑答案 假设目前的根是 rt 目前要查询的子树树根为 x
    那么如果 rt == x 显然就是全局的答案
    另外的情况 , 画图分析可以知道 如果 rt 的深度比 x 的深度不大 那么答案其实就是 x 的子树
    而 rt 深度比 x 深度大的情况下 也只有 x 为 rt 的祖先时 答案为去掉 x 在从 rt 到 x 的路径上那个儿子所在子树的剩下范围 其余情况答案均为 x 的子树

    这种题需要把树画的不那么简单(别总是画满二叉树) 然后定下 rt 的位置让 x 不断移动归纳答案
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
//constexpr int mod = 1e9 + 7;
constexpr ll inf = 1e18;
constexpr ld eps = 1e-8;
constexpr int intinf = 1e9;

#define lson(x) x << 1
#define rson(x) x << 1 | 1

ll gcd(ll x, ll y) {
    return(y == 0 ? x : gcd(y, x % y));
}

ll ksm(ll a, ll b) {
    if (b < 0) return 0;
    ll res = 1;
    while (b) {
        if (b & 1) res = res * a;// % mod;
        a = a * a;// % mod;
        b >>= 1;
    }
    return res;
}

int lowbit(int x) {
    return x & (-x);
}

constexpr int maxn = 4e5 + 10;
constexpr int N = 20;
constexpr int Base = 13;
constexpr int dx[] = { 0,0,1,-1 };
constexpr int dy[] = { 1,-1,0,0 };
constexpr int primes[] = { 2,3,5,7,11,13,17,19,23,29,31,37,41,43 };
//these primes' product > 1e16

int n, m, father[maxn], son[maxn], siz[maxn], dep[maxn], top[maxn], dfn[maxn], seg[maxn], tim, a[maxn];
int tr[maxn], lazy[maxn], f[maxn][N];

vector<int> edge[maxn];

void add(int u, int v) {
    edge[u].push_back(v);
}

void dfs1(int u, int fa) {
    siz[u] = 1;
    dep[u] = dep[fa] + 1;
    f[u][0] = fa;
    father[u] = fa;
    for (int i = 1; i < N; i++)
        f[u][i] = f[f[u][i - 1]][i - 1];
    for (auto v : edge[u]) {
        if (v == fa) continue;
        dfs1(v, u);
        siz[u] += siz[v];
        if (siz[son[u]] < siz[v]) son[u] = v;
    }
}

void dfs2(int u, int head) {
    top[u] = head;
    dfn[u] = ++tim; seg[tim] = u;
    if (son[u] == 0) return;
    dfs2(son[u], head);
    for (auto v : edge[u]) {
        if (v == father[u] || v == son[u]) continue;
        dfs2(v, v);
    }
}

void up(int x) {
    tr[x] = min(tr[lson(x)], tr[rson(x)]);
}

void down(int x) {
    if (lazy[x]) {
        tr[lson(x)] = lazy[x];
        tr[rson(x)] = lazy[x];
        lazy[lson(x)] = lazy[x];
        lazy[rson(x)] = lazy[x];
    }
    lazy[x] = 0;
}

void build(int x, int l, int r) {
    if (l == r) {
        tr[x] = a[seg[l]];
        return;
    }
    int mid = (l + r) / 2;
    build(lson(x), l, mid);
    build(rson(x), mid + 1, r);
    up(x);
}

void update(int ql, int qr, int x, int l, int r, int v) {
    if (ql <= l && r <= qr) {
        tr[x] = v;
        lazy[x] = v;
        return;
    }
    down(x);
    int mid = (l + r) / 2;
    if (ql <= mid) update(ql, qr, lson(x), l, mid, v);
    if (qr > mid) update(ql, qr, rson(x), mid + 1, r, v);
    up(x);
}

int query(int ql, int qr, int x, int l, int r) {
    if (ql <= l && r <= qr) return tr[x];
    int res = INT_MAX;
    down(x);
    int mid = (l + r) / 2;
    if (ql <= mid) res = min(res, query(ql, qr, lson(x), l, mid));
    if (qr > mid) res = min(res, query(ql, qr, rson(x), mid + 1, r));
    return res;
}

void updatePath(int u, int v, int w) {
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) swap(u, v);
        update(dfn[top[u]], dfn[u], 1, 1, n, w);
        u = father[top[u]];
    }
    update(min(dfn[u], dfn[v]), max(dfn[u], dfn[v]), 1, 1, n, w);
}

int check(int x, int fa) {
    int k = dep[x] - dep[fa] - 1;
    for (int i = N - 1; i >= 0; i--)
        if ((k >> i) & 1) x = f[x][i];
    if (f[x][0] == fa) return x;
    return -1;
}

void solve() {
    cin >> n >> m;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        add(u, v); add(v, u);
    }
    dfs1(1, 0);
    dfs2(1, 1);
    for (int i = 1; i <= n; i++) cin >> a[i];
    int rt; cin >> rt;
    build(1, 1, n);
    while (m--) {
        int op;
        cin >> op;
        if (op == 1) {
            int x; cin >> x;
            rt = x;
        }
        if (op == 2) {
            int x, y, v;
            cin >> x >> y >> v;
            updatePath(x, y, v);
        }
        if (op == 3) {
            int x; cin >> x;
            if (x == rt) cout << tr[1] << "\n";
            else {
                if (dep[rt] > dep[x]) {
                    int find = check(rt, x);
                    if (find == -1) {
                        cout << query(dfn[x], dfn[x] + siz[x] - 1, 1, 1, n) << "\n";
                    }
                    else {
                        int ans = INT_MAX;
                        ans = min(ans, query(1, dfn[find] - 1, 1, 1, n));
                        if (dfn[find] + siz[find] <= n)
                            ans = min(ans, query(dfn[find] + siz[find], n, 1, 1, n));
                        cout << ans << "\n";
                    }
                }
                else {
                    cout << query(dfn[x], dfn[x] + siz[x] - 1, 1, 1, n) << "\n";
                }
            }
        }
    }
}

signed main() { 
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int T = 1;
    //prework();
    //cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}
