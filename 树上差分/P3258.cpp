点差分模板题

#include<iostream>
#include<cmath>
#include<cstdio>
#include<random>
#include<cstring>
#include<string>
#include<algorithm>
#include<queue>
#include<map>
#include<set>
#include<cstdlib>
#include<vector>
#include<iomanip>
#include<utility>
#include<unordered_map>
#include<unordered_set>
#include<bitset> 
using namespace std;
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
constexpr int maxn = 6e5 + 10;
constexpr int maxm = 6e6 + 10;
constexpr int intinf = 1e9 + 10;
constexpr int mod = 998244353;
constexpr ll mods[] = { 998244353,1000000007,1000000009 };
constexpr ll inf = 1e15 + 10;
constexpr int dx[] = { 1,-1,0,0 };
constexpr int dy[] = { 0,0,1,-1 };
constexpr ld eps = 1e-12;
using namespace std;
int n, q, sum[maxn], dep[maxn], f[maxn], father[maxn], ans[maxn], a[maxn];
bool vis[maxn];
vector<int> edge[maxn];
vector<pair<int,int>> ask[maxn];

int find(int x) {
	return(x == f[x] ? x : f[x] = find(f[x]));
}

void add(int u, int v) {
	edge[u].push_back(v);
}

void init() {
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	for (int i = 1; i <= n; i++)
		f[i] = i;
	for (int i = 1; i < n; i++) {
		int u, v;
		cin >> u >> v;
		add(u, v); add(v, u);
	}
}

void dfs(int u, int fa) {
	vis[u] = 1;
	father[u] = fa;
	for (auto v : edge[u]) {
		if (v == fa) continue;
		dfs(v, u);
		f[v] = u;
	}
	for (auto [v, num] : ask[u])
		if (vis[v])
			ans[num] = find(v);
}

void doit(int u, int fa) {
	for (auto v : edge[u]) {
		if (v == fa) continue;
		doit(v, u);
		sum[u] += sum[v];
	}
}

void solve() {
	for (int i = 1; i < n; i++) {
		int u = a[i], v = a[i + 1];
		ask[u].push_back({ v,i });
		ask[v].push_back({ u,i });
		sum[u]++;
	}
	dfs(1, 0);
	for (int i = 1; i < n; i++) {
		sum[father[a[i + 1]]]++;
		sum[ans[i]]--;
		sum[father[ans[i]]]--;
	}
	doit(1, 0);
}

void query() {
	int res = 0;
	for (int i = 1; i <= n; i++)
		cout << sum[i] << "\n";
	cout << "\n";
}

int main() {
	ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
	init();
	solve();
	query();
	return 0;
}
