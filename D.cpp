#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using ll = long long;
using namespace std;
const int maxn = 100010, mod = 998244353;
int n, t;
int a[maxn];

ll qpow(ll num, int po = mod - 2) {
  ll ret = 1;
  for (; po; po >>= 1) {
    if (po & 1)
      ret = ret * num % mod;
    num = num * num % mod;
  }
  return ret;
}

int main() {
  cin >> n >> t;
  int sumt = 0;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    sumt += a[i];
  }
  int free = t - sumt + 1;
  ll ans = 1;
  sumt = 0;
  for (int i = 1; i <= n; i++) {
    ans *= sumt + free + (n - i + 1);
    ans %= mod;
    sumt += a[i];
  }
  ans = ans * free % mod;
  ans = ans * qpow(free + n) % mod;
  cout << ans << endl;
  return 0;
}
