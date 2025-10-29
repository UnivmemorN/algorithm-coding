本题作为一道整体二分模板题，思路在算法思想中已经完全讲述，所以本题以注释的方式便于理解整体二分上实现上的一些细节

```cpp
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
constexpr int mod = 1e9 + 7;
constexpr ll inf = 1e18;
constexpr ld eps = 1e-8;
constexpr int intinf = 1e9;

#define lson(x) x << 1
#define rson(x) x << 1 | 1


int lowbit(int x) {
    return x & (-x);
}

constexpr int maxn = 2e5 + 10;
constexpr int N = 20;
constexpr int Base = 13;
constexpr int dx[] = { 0,0,1,-1 };
constexpr int dy[] = { 1,-1,0,0 };
constexpr int primes[] = { 2,3,5,7,11,13,17,19,23,29,31,37,41,43 };
//these primes' product > 1e16

int n, m, l[maxn], r[maxn], ans[maxn], q[maxn], tr[maxn], rk[maxn], L[maxn], R[maxn];

struct node {
    int v, id;
} a[maxn];

bool cmp(node c1, node c2) {
    return c1.v < c2.v;
}

void add(int x, int y) {
    for (int i = x; i <= n; i += lowbit(i))
        tr[i] += y;
}

int query(int x) {
    int res = 0;
    for (int i = x; i >= 1; i -= lowbit(i))
        res += tr[i];
    return res;
}
//以上为树状数组 由于涉及到单点修改 区间查询 我们采用树状数组来维护这个过程

void work(int ql, int qr, int cl, int cr) {
    if (cl == cr) {//答案的值域只剩下了一个点 那么无须继续二分下去 cl 就是答案
        for (int i = ql; i <= qr; i++)
            ans[q[i]] = a[cl].v;//注意不能写成 ans[i] = ... 因为我们将询问离线了 q[i] 才是询问真正的编号
        return;
    }
    int mid = (cl + cr) / 2, lnum = 0, rnum = 0;//mid 表示二分中点 lnum 是左组内询问个数 rnum 是右组内询问个数
    for (int i = cl; i <= mid; i++)
        add(a[i].id, 1);//修改操作 在该数所对应原本的位置上 +1 
    for (int i = ql; i <= qr; i++) {
        int num = q[i];
        int cur = query(r[num]) - query(l[num] - 1);//查询当前询问 num 的 l 和 r 范围有多少 <= mid 的数
        if (cur >= rk[num]) {//如果满足了要求 进入左组 用 L 数组保存询问编号
            lnum++;
            L[lnum] = num;
        }
        else {
			//否则不满足要求 进入右组 用 R 数组保存询问编号 
            //同时让询问的第 k 大的 k (代码中的 rk ) 减去 l - mid 区间内已经满足的个数 这才是它进入右区间后正确的 "k"
            rk[num] -= cur;
            rnum++;
            R[rnum] = num;
        }
    }
    for (int i = 1; i <= lnum; i++) q[ql + i - 1] = L[i];
    for (int i = 1; i <= rnum; i++) q[ql + lnum + i - 1] = R[i];
    //用 L 和 R 数组重新将 ql - qr 区间内的 q 数组重新拼回来
    for (int i = cl; i <= mid; i++)
        add(a[i].id, -1);//撤销操作 防止对后续干扰
    work(ql, ql + lnum - 1, cl, mid);//左组的询问进入左区间
    work(ql + lnum, ql + lnum + rnum - 1, mid + 1, cr);//右组的询问进入右区间
}

void solve() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i].v;
        a[i].id = i;
    }//因为 a[i] 后续要根据 v 的大小排序 所以我们需要额外开一个 id 来保存这个元素在原本的顺序中的位置
    sort(a + 1, a + n + 1, cmp);//为了满足二分的条件 将 a 数组按照 v 的值从小到大排序
    for (int i = 1; i <= m; i++)
        cin >> l[i] >> r[i] >> rk[i];
    for (int i = 1; i <= m; i++) q[i] = i;
    //q 数组非常重要 它是我们整体二分过程中 正在处理的询问的编号
    work(1, m, 1, n);//分别表示询问区间和答案值域区间 
    //但是我们并不真的将值域定为1 - 1e9 而是 1 - n 这是因为区间第 k 大一定是数组中出现过的元素 而且我们已经让 a 数组按照值从小到大排序了 满足二分的单调性
    for (int i = 1; i <= m; i++)
        cout << ans[i] << "\n";
}

signed main() { 
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int T = 1;
    while (T--) {
        solve();
    }
    return 0;
}
```
