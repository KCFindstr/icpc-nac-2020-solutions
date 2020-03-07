#include <iostream>
#include <cstdio>
#include <string>
#include <cmath>
#include <queue>
#include <algorithm>
using ll = long long;
using namespace std;
const int maxn = 200010;
int n, p, q, s;
int A[maxn], B[maxn];
struct itv {
  int l, r, id;
  bool operator < (const itv &rhs) const {
    return l < rhs.l;
  }
} inv[maxn];

struct itvCmp {
  bool operator () (const itv &lhs, const itv &rhs) const {
    if (lhs.r != rhs.r) {
      return lhs.r > rhs.r;
    }
    return lhs.id < rhs.id;
  }
};

bool check(int diff) {
  // printf("=> solve: diff=%d\n", diff);
  for (int i = 1; i <= p; i++) {
    int r1 = upper_bound(B + 1, B + q + 1, A[i] + diff) - B - 1;
    int r2 = upper_bound(B + 1, B + q + 1, s - A[i]) - B - 1;
    inv[i].r = min(r1, r2);
    inv[i].l = lower_bound(B + 1, B + q + 1, A[i] - diff) - B;
    inv[i].id = i;
    // printf("%d: %d-%d\n", A[i], inv[i].l, inv[i].r);
  }
  sort(inv+1, inv+1+p);
  int head = 1, ans = 0;
  priority_queue<itv, vector<itv>, itvCmp> Q;
  for (int i = 1; i <= q; i++) {
    while (head <= p && inv[head].l <= i) {
      if (inv[head].l <= inv[head].r) {
        Q.push(inv[head]);
      }
      head++;
    }
    while (!Q.empty()) {
      auto top = Q.top();
      Q.pop();
      if (top.r < i) continue;
      ans++;
      break;
    }
  }
  // printf("result: %d\n", ans);
  return ans >= n;
}

int main() {
  scanf("%d%d%d%d", &n, &p, &q, &s);
  for (int i = 1; i <= p; i++) {
    scanf("%d", A + i);
  }
  for (int i = 1; i <= q; i++) {
    scanf("%d", B + i);
  }
  sort(B + 1, B + 1 + q);
  int l = 0, r = s + 1;
  while (r > l) {
    int mid = (l + r) >> 1;
    if (check(mid)) {
      r = mid;
    } else {
      l = mid + 1;
    }
  }
  cout << (l > s ? -1 : l);
  return 0;
}