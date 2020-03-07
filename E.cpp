#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <ctime>
#include <bitset>
#include <algorithm>
using ll = long long;
using namespace std;
int mod;

ll qpow(ll num, ll po) {
  ll ret = 1;
  for (; po; po >>= 1) {
    if (po & 1) {
      ret = ret * num % mod;
    }
    num = num * num % mod;
  }
  return ret;
}

namespace Hard {
  int n, m;
  int po2n;

  #define bit(x, y) (((x) >> (y)) & 1)
  #define T(S, l, r, p) (\
    ((l) << 12) |\
    ((r) << 16) |\
    ((p) << 20) |\
    (S))
  #define T_S(x) ((x) & 0x0fff)
  #define T_L(x) (((x) >> 12) & 0xf)
  #define T_R(x) (((x) >> 16) & 0xf)
  #define T_P(x) (((x) >> 20) & 0xf)

  vector<int> trans[2][1 << 12];

  void addTrans(int f, int t) {
    for (int i = 0; i < n; i++) {
      if (bit(f, i) && !bit(t, i)) return;
    }
    // Find 01
    int prev01 = 0;
    int prev10 = -1;
    int L[13], R[13];
    L[0] = 0;
    R[0] = n;
    L[n] = 0;
    R[n] = n;
    for (int i = 1; i <= n; i++) {
      if (i != n &&
        (bit(f, i-1) ^ bit(t, i-1)) ||
        (bit(f, i) ^ bit(t, i))
      ) continue;
      if (i == n || (!bit(f, i-1) && bit(f, i))) {
        // 01
        // |..x.
        // |x...
        //  ...x|
        //  .x..|
        trans[1][f].push_back(T(t, prev01, i-1, i+1));
        prev01 = i;
      }
      if (i == n || (bit(f, i-1) && !bit(f, i))) {
        // 10
        //  .x..|
        //  ...x|
        // |x...
        // |..x.
        trans[0][f].push_back(T(t, prev10+1, i, max(0, prev10)));
        prev10 = i;
      }
    }
  }

  string bitStr(int num) {
    string str = bitset<2>(num).to_string('_', '-');
    reverse(str.begin(), str.end());
    return str;
  }

  void debug() {
    int totTrans = 0, hasTrans = 0;
    for (int i = 0; i <= 1; i++) {
      for (int j = 0; j < po2n; j++) {
        totTrans += trans[i][j].size();
        hasTrans += trans[i][j].size() > 0;
        /*
        printf("=> %d %s:\n", i, bitStr(j).c_str());
        for (int k: trans[i][j]) {
          printf("%s [%d,%d]\n", bitStr(T_S(k)).c_str(), T_L(k), T_R(k));
        }
        */
      }
    }

    printf("%d / %d\n", totTrans, hasTrans);
  }

  ll f[2][14][1 << 12];
  ll DP() {
    for (int i = 0; i <= n; i++) {
      for (int j = 0; j < po2n; j++) {
        f[1][i][j] = 1;
      }
    }
    for (int i = 1; i < m; i++) {
      bool c = i & 1;
      for (int j = 1; j <= n; j++) {
        for (int k = 0; k < po2n; k++) {
          f[c][j][k] += f[c][j-1][k];
          f[c][j][k] %= mod;
        }
      }
      for (int k = 0; k < po2n; k++) {
        for (int t: trans[0][k]) {
          ll lval = T_L(t) == 0 ? 0 : f[c][T_L(t)-1][k];
          f[c^1][T_P(t)][T_S(t)] += f[c][T_R(t)][k] - lval;
        }
        for (int t: trans[1][k]) {
          ll lval = T_L(t) == 0 ? 0 : f[c][T_L(t)-1][k];
          f[c^1][T_P(t)][T_S(t)] -= f[c][T_R(t)][k] - lval;
        }
      }
      for (int k = 0; k < po2n; k++) {
        f[c^1][0][k] %= mod;
        f[c][0][k] = 0;
      }
      for (int j = 1; j <= n; j++) {
        for (int k = 0; k < po2n; k++) {
          f[c^1][j][k] += f[c^1][j-1][k];
          f[c^1][j][k] %= mod;
          f[c][j][k] = 0;
        }
      }
    }
    bool c = m & 1;
    ll ret = 0;
    for (int k = 0; k < po2n; k++) {
      for (int j = 0; j <= n; j++) {
        ret += f[c][j][k];
      }
    }
    ret %= mod;
    if (ret < 0) ret += mod;
    return ret;
  }

  void initTrans() {
    for (int i = 0; i < po2n; i++) {
      for (int j = 0; j < po2n; j++) {
        addTrans(i, j);
      }
    }
  }

  int solve2(int _n, int _m) {
    n = _n >> 1;
    m = _m >> 1;
    po2n = 1 << n;
    initTrans();
    // printf("%f\n", (float)clock() / CLOCKS_PER_SEC);
    debug();
    return DP();
  }
}

int solve1(int n, int m) {
  int po = max(1, n >> 1);
  return qpow(m / 2 + 1, po);
}

int main() {
  int n, m;
  cin >> n >> m >> mod;
  if ((n & 1) && (m & 1)) {
    cout << 1;
  } else if (n & 1) {
    cout << solve1(n, m);
  } else if (m & 1) {
    cout << solve1(m, n);
  } else {
    cout << Hard::solve2(n, m);
  }
  return 0;
}