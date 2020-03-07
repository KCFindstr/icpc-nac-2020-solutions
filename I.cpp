#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cmath>
#include <algorithm>
using ll = long long;
using namespace std;
const int mod = 998244353;
char S[12];
char cmap[26];
int d, n, m, maxS;

char pre[12][12];

ll f[22][59049];

inline void Decode(char* dest, int init, int s) {
  dest[0] = init;
  for (int i = 1; i <= n; i++) {
    dest[i] = dest[i-1] + s % 3 - 1;
    s /= 3;
  }
}

inline int Encode(char* src) {
  int ret = 0;
  for (int i = n; i >= 1; i--) {
    ret = ret * 3 + 1 + src[i] - src[i-1];
  }
  return ret;
}

inline void print(char *src) {
  for (int i = 0; i <= n; i++) {
    printf("%d%c", src[i], " \n"[i == n]);
  }
}

ll dp(int init, int s) {
  ll &ret = f[init][s];
  if (ret != -1) {
    return ret;
  }
  ret = 0;
  char edit[12];
  Decode(edit, init, s);
  if (edit[n] == d) ret++;
  
  char tmp[12];

  for (int i = 0; i <= m; i++) {
    tmp[0] = edit[0] + 1;
    for (int j = 1; j <= n; j++) {
      int last = pre[j][i];
      int cmin = min(edit[j] + 1, edit[j - 1] + (i != S[j]));
      if (last != -1) {
        cmin = min(cmin, edit[last - 1] + j - last);
      }
      tmp[j] = cmin;
    }
    int curS = Encode(tmp);
    if (i == 0) {
      ret += dp(init + 1, curS) * (26 - m);
    } else {
      ret += dp(init + 1, curS);
    }
  }

  ret %= mod;
  return ret;
}

int main() {
  scanf("%s%d", S + 1, &d);
  n = strlen(S + 1);
  for (int i = 1; i <= n; i++) {
    char &c = S[i];
    c -= 'A';
    if (!cmap[c]) {
      cmap[c] = ++m;
    }
    c = cmap[c];
    // putchar(c + 'A');
  }
  // puts("\n===");
  memset(pre, -1, sizeof(pre));
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j <= m; j++) {
      if (S[i] == j) {
        pre[i][j] = i;
      } else {
        pre[i][j] = pre[i-1][j];
      }
    }
  }

  memset(f, -1, sizeof(f));
  maxS = 1;
  for (int i = 1; i <= n; i++) {
    maxS *= 3;
  }

  int startS = 0;
  for (int i = 1; i <= n; i++) {
    startS = startS * 3 + 2;
  }

  for (int j = 0; j <= n + d + 1; j++) {
    for (int i = 0; i < maxS; i++) {
      char dest[12];
      Decode(dest, j, i);
      bool possible = false;
      for (int k = 0; k <= n; k++) {
        if (dest[k] <= d) {
          possible = true;
          break;
        }
      }
      if (!possible) {
        f[j][i] = 0;
      }
    }
  }

  cout << dp(0, startS) << endl;
  return 0;
}