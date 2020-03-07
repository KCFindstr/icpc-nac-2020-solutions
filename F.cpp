#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int maxn = 55;

int G[maxn][maxn];
int n, k;
int dp[maxn][maxn];
vector<pii> P[maxn * maxn];

int main() {
  cin >> n >> k;
  int ans = 0x3f3f3f3f;
  memset(dp, 0x3f, sizeof(dp));
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      cin >> G[i][j];
      if (G[i][j] == 1) {
        dp[i][j] = 0;
        if (k == 1) {
          ans = 0;
        }
      }
      P[G[i][j]].emplace_back(i, j);
    }
  }
  for (int v = 2; v <= k; v++) {
    for (auto &f: P[v-1]) {
      for (auto &t: P[v]) {
        dp[t.first][t.second] = min(dp[t.first][t.second],
          dp[f.first][f.second] + abs(t.first - f.first) + abs(t.second - f.second));
        if (v == k) {
          ans = min(ans, dp[t.first][t.second]);
        }
      }
    }
  }
  cout << (ans == 0x3f3f3f3f ? -1 : ans);
  return 0;
}