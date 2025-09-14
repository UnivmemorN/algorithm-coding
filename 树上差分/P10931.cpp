要在两个不同部分分别破坏掉边 那么可以分开来考虑
对于每一条旧的边 显然如果经过他的新边数目为 0 那么只要这条边断开 新边可以任意断开
如果经过他的新边数目为 1 那么只能恰好断开经过他的那条新边
否则如果经过他的新边数量 > 1 那么至少要断开两条新边 显然不符合题意 无解
然后将题目转化为边差分的题目


#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<map>
#include<cmath>
#include<cstring>
#include<string>
#include<set>
#include<unordered_set>
#include<unordered_map>
#include<queue>
#include<cstdlib>
#include<iomanip>
#include<climits>
#include<bitset>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;

#define lson(x) x << 1
#define rson(x) x << 1 | 1

int gcd(int x, int y) {
    return(y == 0 ? x : gcd(y, x % y));
}

constexpr int maxn = 4e5 + 10;
constexpr int N = 21;
constexpr int B = 2e5;
constexpr int mod = 1e9 + 7;
constexpr ll inf = 4e18;
constexpr ld eps = 1e-8;
constexpr int intinf = 1e9;
constexpr int dx[] = { 1,1,-1,-1,2,2,-2,-2 };
constexpr int dy[] = { 2,-2,2,-2,1,-1,1,-1 };
constexpr int primes[] = { 2,3,5,7,11,13,17,19,23,29 };
//these primes' product > 1e9

int n, m, dep[maxn], f[maxn][N], num[maxn], sum[maxn];
vector<pair<int, int>> edge[maxn];

void add(int u, int v,int w) {
    edge[u].push_back({ v,w });
}

void dfs(int u, int fa) {
    dep[u] = dep[fa] + 1;
    f[u][0] = fa;
    for (int i = 1; i < N; i++)
        f[u][i] = f[f[u][i - 1]][i - 1];
    for (auto [v, _] : edge[u]) {
        if (v == fa) continue;
        dfs(v, u);
    }
}

int get_lca(int u, int v) {
    if (dep[u] < dep[v]) swap(u, v);
    int k = dep[u] - dep[v];
    for (int i = N - 1; i >= 0; i--)
        if ((k >> i) & 1)
            u = f[u][i];
    if (u == v) return u;
    for (int i = N - 1; i >= 0; i--)
        if (f[u][i] != f[v][i])
            u = f[u][i], v = f[v][i];
    return f[u][0];
}

void query(int u, int fa) {
    for (auto [v, w] : edge[u]) {
        if (v == fa) continue;
        query(v, u);
        num[u] += num[v];
        sum[w] += num[v];
    }
}

void solve() {
    cin >> n >> m;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        add(u, v, i);
        add(v, u, i);
    }
    dfs(1, 0);
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        num[u]++; num[v]++; num[get_lca(u, v)] -= 2;
    }
    query(1, 0);
    int ans = 0;
    for (int i = 1; i < n; i++) {
        if (sum[i] == 0) ans += m;
        if (sum[i] == 1) ans += 1;
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int T = 1;
    //prework();
    //cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}
