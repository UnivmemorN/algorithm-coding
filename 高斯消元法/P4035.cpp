/*
  链接 : https://www.luogu.com.cn/problem/P4035
  根据球心到各点距离相同列方程即可
  本题中 , 保证有解弱化了判断情况
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

int n;
ld a[50][50], p[50][50];

ld sqr(ld x) {
    return x * x;
}

void solve() {
    cin >> n;
    for (int i = 1; i <= n + 1; i++)
        for (int j = 1; j <= n; j++)
            cin >> p[i][j];
    for (int i = 1; i <= n; i++) {
        ld sum = 0;
        for (int j = 1; j <= n; j++) {
            a[i][j] = 2 * (p[i + 1][j] - p[i][j]);
            sum += sqr(p[i + 1][j]) - sqr(p[i][j]);
        }
        a[i][n + 1] = sum;
    }
    for (int i = 1; i <= n; i++) {//主元为 i 
        int maxline = i;
        for (int j = 1; j <= n; j++) {
            if (j < i && a[j][j] >= eps) continue;
            if (abs(a[maxline][i]) < abs(a[j][i])) maxline = j;
        }
        swap(a[maxline], a[i]);
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
        cout << fixed << setprecision(3) <<  a[i][n + 1] << " ";
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
