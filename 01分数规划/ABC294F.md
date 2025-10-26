$ABC294F$

题目所求为分式 $\frac{x}{x + y}$ 又要求第 $k$ 大 该问题类似于**分数规划**

我们采取类似的思路 采用二分答案来解决这个问题

假设我们当前的答案为 $mid$ 那么考虑何时该答案是合法的

显然 我们去统计 $\ge mid$ 的混合方案有多少方案 

如果方案数 $\ge k$ 那么我们认为该答案合法 记录答案的同时让左端点 $l$ 向右移动即可

否则让 $r$ 向左移动

那么我们考虑如何统计 $\ge mid$ 的方案数

先单独考虑一个人的糖水浓度 $\frac{x}{x + y} \ge mid$ $\to$ $x \ge mid\times (x + y)$ $\therefore$ $x\ge \frac{mid \times y}{1 - k}$

因此我们可以采取与分数规划类似的想法 去计算每一杯糖水的**盈余** $lst[i]$

所以 分别计算出两个人的盈余 然后枚举一个人某一杯水的盈余

那么我们只需要去寻找另一个人有多少杯水的盈余 加上这一杯水的盈余是 $\ge 0$ 的 累加起来即可

也就是对于当前的 $\frac{mid \times y}{1 - k} + lst[p] \ge 0$ 其中 $p$ 为另一个人所有水的编号

也就是去寻找 $lst[p] \ge -\frac{mid \times y}{1 - k}$ 的 个数

因此 我们需要给另一个人的所有水的盈余进行排序 然后直接二分去查找即可

总体时间复杂度 $O(n\log n\log v)$

```cpp
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
using namespace std;
typedef long long ll;
typedef long double ld;
constexpr int maxn = 4e5 + 10;
constexpr int maxm = 500 + 10;
constexpr int mod = 998244353;
constexpr int mod1 = 1e9 + 7;
constexpr ll inf = 1e18 + 10;
constexpr int dx[] = { 1,-1,0,0 };
constexpr int dy[] = { 0,0,1,-1 };
constexpr ld eps = 1e-25;
ll n, m, k;
ld lst[maxn];
struct node {
	ll x, y;
} a[maxn],b[maxn];
void init() {
	cin >> n >> m >> k;
	for (int i = 1; i <= n; i++)
		cin >> a[i].x >> a[i].y;
	for (int i = 1; i <= m; i++)
		cin >> b[i].x >> b[i].y;
}
int find(ld x) {
	int l = 1, r = m, ans = 0;
	while (l<=r) {
		int mid = (l + r) / 2;
		if (lst[mid] >= x) {
			ans = mid;
			l = mid + 1;
		}
		else r = mid - 1;
	}
	return ans;
}
bool check(ld mid) {
	for (int i = 1; i <= m; i++)
		lst[i] = b[i].x - (mid) / (1 - mid) * b[i].y;
	sort(lst + 1, lst + m + 1);
	reverse(lst + 1, lst + m + 1);
	ll num = 0;
	for (int i = 1; i <= n; i++) {
		ld need = (mid) / (1 - mid) * a[i].y - a[i].x;
		ll pos=find(need);
		num += pos;
	}
	return num >= k;
}
void solve() {
	ld l = 0, r = 1, ans = 0;
	ll sum = 0;
	while (sum<100) {
		sum++;
		ld mid = (l + r) / 2;
		if (check(mid)) {
			ans = mid;
			l = mid;
		}
		else r = mid;
	}
	cout << fixed << setprecision(10) << ans * 100 << "\n";
}
int main() {
	init();
	solve();
	return 0;
}
```

