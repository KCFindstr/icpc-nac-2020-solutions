#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>
using ll = long long;
using namespace std;
string s[3];
const int maxn = 5020;
bool suc[3][maxn];

int main() {
  for (auto &S: s) {
    cin >> S;
  }
  int n = s[0].length();
  int ans = 0x3f3f3f3f;
  memset(suc, true, sizeof(suc));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (s[0][j] == s[1][(i+j)%n]) {
        suc[1][i] = false;
      }
      if (s[0][j] == s[2][(i+j)%n]) {
        suc[2][i] = false;
      }
      if (s[1][j] == s[2][(i+j)%n]) {
        suc[0][i] = false;
      }
    }
  }
  for (int i = 0; i < n; i++) {
    // printf("suc %d=%d %d %d\n", i, suc[0][i], suc[1][i], suc[2][i]);
    for (int j = 0; j < n; j++) {
      if (suc[1][i] && suc[2][j] && suc[0][(j+n-i)%n]) {
        ans = min(ans, max(n-i, n-j));
        ans = min(ans, max(i, j));
        ans = min(ans, min(i, n-i) + min(j, n-j));
      }
    }
  }
  cout << (ans == 0x3f3f3f3f ? -1 : ans);
  return 0;
}