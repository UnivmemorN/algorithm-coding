/*
    本题为题目提供的信息为边权的模板题，将其转化为点权再树剖、线段树即可
/*

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

constexpr int maxn = 8e5 + 10;
constexpr int N = 20;
constexpr int Base = 13;
constexpr int dx[] = { 0,0,1,-1 };
constexpr int dy[] = { 1,-1,0,0 };
constexpr int primes[] = { 2,3,5,7,11,13,17,19,23,29,31,37,41,43 };
//these primes' product > 1e16

int n, m, siz[maxn], son[maxn], father[maxn], top[maxn], dep[maxn], dfn[maxn], seg[maxn], tim;
int tr[maxn], lazy[maxn];

vector<int> edge[maxn];

void add(int u, int v) {
    edge[u].push_back(v);
}

void dfs1(int u, int fa) {
    siz[u] = 1;
    father[u] = fa;
    dep[u] = dep[fa] + 1;
    for (auto v : edge[u]) {
        if (v == fa) continue;
        dfs1(v, u);
        siz[u] += siz[v];
        if (siz[v] > siz[son[u]]) son[u] = v;
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
    tr[x] = tr[lson(x)] + tr[rson(x)];
}

void down(int x) {
    if (lazy[x]) {
        int p = lazy[x];
        tr[lson(x)] += p;
        tr[rson(x)] += p;
        lazy[lson(x)] += p;
        lazy[rson(x)] += p;
    }
    lazy[x] = 0;
}

void update(int ql,int qr,int x,int l,int r){
    if (ql <= l && r <= qr) {
        tr[x]++;
        lazy[x]++;
        return;
    }
    down(x);
    int mid = (l + r) / 2;
    if (ql <= mid) update(ql, qr, lson(x), l, mid);
    if (qr > mid) update(ql, qr, rson(x), mid + 1, r);
    up(x);
}

void addPath(int u, int v) {
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) swap(u, v);
        update(dfn[top[u]], dfn[u], 1, 1, n);
        u = father[top[u]];
    }
    if (dfn[u] > dfn[v]) swap(u, v);
    u = son[u];
    if (u && dfn[u] <= dfn[v]) update(dfn[u], dfn[v], 1, 1, n);
}

int query(int qid, int x, int l, int r) {
    if (qid == l && qid == r) 
        return tr[x];
    down(x);
    int mid = (l + r) / 2;
    if (qid <= mid) return query(qid, lson(x), l, mid);
    if (qid > mid) return query(qid, rson(x), mid + 1, r);
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
    while (m--) {
        char op; int x, y;
        cin >> op >> x >> y;
        if (op == 'P') {
            addPath(x, y);
        }
        else {
            int u = (dep[x] > dep[y] ? x : y);
            cout << query(dfn[u], 1, 1, n) << "\n";
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
