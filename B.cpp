#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using ll = long long;
using namespace std;
const int maxn = 10;
int n, k;
char G[maxn][maxn];
bool grid[maxn][maxn];
int s[maxn];

int solve(int m) {
  if (m > k) {
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++) {
        if (G[i][j] == 'O' && !grid[i][j]) {
          return 0;
        }
      }
    }
    return 1;
  }
  int ans = 0;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      if (i + s[m] - 1 <= n) {
        bool suc = true;
        for (int k = i; k <= i + s[m] - 1; k++) {
          if (grid[k][j] || G[k][j] == 'X') {
            suc = false;
            break;
          }
        }
        if (suc) {
          for (int k = i; k <= i + s[m] - 1; k++) {
            grid[k][j] = 1;
          }
          ans += solve(m+1);
          for (int k = i; k <= i + s[m] - 1; k++) {
            grid[k][j] = 0;
          }
        }
      }
      if (s[m] == 1) continue;
      if (j + s[m] - 1 <= n) {
        bool suc = true;
        for (int k = j; k <= j + s[m] - 1; k++) {
          if (grid[i][k] || G[i][k] == 'X') {
            suc = false;
            break;
          }
        }
        if (suc) {
          for (int k = j; k <= j + s[m] - 1; k++) {
            grid[i][k] = 1;
          }
          ans += solve(m+1);
          for (int k = j; k <= j + s[m] - 1; k++) {
            grid[i][k] = 0;
          }
        }
      }
    }
  }
  return ans;
}

int main() {
  cin >> n >> k;
  for (int i = 1; i <= n; i++) {
    cin >> (G[i] + 1);
  }
  memset(grid, 0, sizeof(grid));
  for (int i = 1; i <= k; i++) {
    cin >> s[i];
  }
  cout << solve(1) << endl;
  return 0;
}