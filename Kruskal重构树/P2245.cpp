最小化最大边权的模板题

直接采用 Kruskal 重构树的模板来解决 这里着重讲解代码实现



```cpp
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

constexpr int maxn = 3e5 + 10;
constexpr int N = 21;
constexpr int mod = 998244353;
constexpr ll inf = 2e14;
constexpr ld eps = 1e-8;
constexpr int intinf = 1e9;

int n, m, f[maxn], cnt, value[maxn], dep[maxn], fa[maxn][N];
vector<int> edge[maxn];

struct node {
    int u, v, w;
} e[maxn];

bool cmp(node c1, node c2) {
    return c1.w < c2.w;
}

int find(int x) {
    return (x == f[x] ? x : f[x] = find(f[x]));
}

void add(int u, int v) {
    edge[u].push_back(v);
}

void dfs(int u, int father) {
    dep[u] = dep[father] + 1;
    fa[u][0] = father;
    for (auto v : edge[u]) {
        if (v == father) continue;
        dfs(v, u);
    }
}

void ST() {
    for (int i = 1; i < N; i++)
        for (int j = 1; j <= cnt; j++)
            fa[j][i] = fa[fa[j][i - 1]][i - 1];
}

int get_lca(int u, int v) {
    if (dep[u] < dep[v]) swap(u, v);
    int k = dep[u] - dep[v];
    for (int i = 20; i >= 0; i--)
        if ((k >> i) & 1)
            u = fa[u][i];
    if (u == v) return u;
    for (int i = 20; i >= 0; i--)
        if (fa[u][i] != fa[v][i])
            u = fa[u][i], v = fa[v][i];
    return fa[u][0];
}

//dfs ST 和 get_lca 三个函数就是用来求 lca 的

void init(){
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        f[i] = i;
    for (int i = 1; i <= m; i++)
        cin >> e[i].u >> e[i].v >> e[i].w;
    sort(e + 1, e + m + 1, cmp);//要最小化最大边权 就要让边按照权值从小到大进行排序
    cnt = n;//初始树中的节点数为 n 
    for (int i = 1; i <= m; i++) {
        int u = find(e[i].u), v = find(e[i].v);
        if (u == v) continue;//如果两者已经联通则不需要合并
        cnt++;
        f[cnt] = cnt;
        f[u] = cnt; f[v] = cnt;//在并查集中 让 u v cnt 三者都指向 cnt
        add(cnt, u); add(cnt, v);//构建出重构树
        value[cnt] = e[i].w;//重构树上的点权即为原图中的边权
    }
    for (int i = 1; i <= cnt; i++)
        if (f[i] == i)//可能是重构森林 应该考虑每一棵树
            dfs(i, 0);
}

void solve() {
    init();
    ST();
    int Q; cin >> Q;
    while (Q--) {
        int u, v;
        cin >> u >> v;
        if (find(u) != find(v)) {//它们本身就不联通
            cout << "impossible\n";
            continue;
        }
        int lca = get_lca(u, v);
        cout << value[lca] << "\n";//否则 根据重构树的原理 两者的 lca 的点权就是最小的最大边权 也就是瓶颈路的边权
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    while (T--) 
        solve();
    return 0;
}
```



