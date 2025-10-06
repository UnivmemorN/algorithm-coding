/*
  链接 : https://www.luogu.com.cn/problem/P5027
  按照题意解方程即可
  需要注意的是 虽然题目中所有数据都是整数 也要求解全部为整数 但是解方程过程中仍然可能会出现小数!!!
  最终判断是否全部为整数解利用 x 和 (int) x 的关系来判断即可
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
#include<random>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
constexpr int mod = 998244353;
constexpr ll inf = 1e18;
constexpr ld eps = 1e-7;
constexpr int intinf = 1e9 + 10;

constexpr int maxn = 2e5 + 10;
constexpr int N = 21;
constexpr int Base = 13;
constexpr int dx[] = { 0,0,1,-1 };
constexpr int dy[] = { 1,-1,0,0 };
constexpr int primes[] = { 2,3,5,7,11,13,17,19,23,29,31,37,41,43 };
//these primes' product > 1e16

int n, f[150][150];
ld a[150][150];

int Gauss() {
    for (int i = 1; i <= n; i++) {
        int maxline = i;
        for (int j = 1; j <= n; j++) {
            if (j < i && a[j][j] >= eps) continue;
            if (abs(a[maxline][i]) < abs(a[j][i])) maxline = j;
        }
        swap(a[maxline], a[i]);
        if (abs(a[i][i]) < eps) return -1;
        ld tmp = a[i][i];
        for (int j = 1; j <= n + 1; j++) 
            a[i][j] /= tmp;
        for (int j = 1; j <= n; j++)
            if (j != i) {
                ld tmp = a[j][i];
                for (int k = 1; k <= n + 1; k++) {
                    a[j][k] -= tmp * a[i][k];
                }
            }
    }
    for (int i = 1; i <= n; i++)
        if (abs(a[i][n + 1] - (int)(a[i][n + 1])) > eps) return -1;
    int res = 0;
    for (int i = 1; i <= n; i++)
        if (a[i][n + 1] <= 0) return -1;
    for (int i = 1; i <= n; i++)
        if (a[i][n + 1] > a[res][n + 1]) res = i;
    for (int i = 1; i <= n; i++)
        if (i != res && a[i][n + 1] == a[res][n + 1]) return -1;
    return res;
}

void solve() {
    cin >> n;
    for (int i = 1; i <= n + 1; i++) {
        cin >> f[i][0];
        for (int j = 1; j <= f[i][0]; j++)
            cin >> f[i][j];
        cin >> f[i][n + 1];
    }
    int ans = -1;
    for (int ex = 1; ex <= n + 1; ex++) {
        int cnt = 0;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n + 1; j++)
                a[i][j] = 0;
        for (int i = 1; i <= n + 1; i++) {
            if (ex == i) continue;
            cnt++;
            for (int j = 1; j <= f[i][0]; j++)
                a[cnt][f[i][j]]++;
            a[cnt][n + 1] = f[i][n + 1];
        }
        int flag = Gauss();
        if (flag != -1 && ans != -1) {
            cout << "illegal\n";
            return;
        }
        else if (flag != -1) ans = flag;
    }
    if (ans == -1) {
        cout << "illegal\n";
        return;
    }
    else cout << ans << "\n";
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
