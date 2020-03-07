#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>
#include <set>
using ll = long long;
using namespace std;
using pii = pair<int, int>;
const int maxn = 200010, inf = 0x3f3f3f3f;
#define Sqr(x) ((ll)(x) * (x))

int cX, n, q;
int ans[maxn];

struct Circle {
  int x, y, r, id, par;
  int dp[2];
  vector<int> E;
} C[maxn];

struct Arc {
  Circle *c;
  bool isUp;

  Arc() {}
  Arc(Circle *_c, bool _up): c(_c), isUp(_up) {}

  double eval(int X) const {
    if (X < c->x - c->r || X > c->x + c->r)
      return -inf;
    ll dy2 = Sqr(c->r) - Sqr(X - c->x);
    double dy = sqrt(dy2);
    return isUp ? c->y + dy : c->y - dy;
  }
  
  bool operator < (const Arc &rhs) const {
    if (c->id == rhs.c->id) {
      return isUp < rhs.isUp;
    }
    return eval(cX) < rhs.eval(cX);
  }
} A[maxn << 1];

pii events[maxn << 1];
int en;

void ProcessCircles() {
  set<Arc> st;
  sort(events + 1, events + 1 + en);
  for (int i = 1; i <= en; i++) {
    cX = events[i].first;
    int id = abs(events[i].second);
    if (events[i].second > 0) {
      // Add
      auto top = st.upper_bound(A[id << 1]);
      if (top != st.end()) {
        C[id].par = top->isUp ? top->c->id : top->c->par;
      }
      st.insert(A[id << 1]);
      st.insert(A[(id << 1) | 1]);
    }
    else {
      // Remove
      st.erase(A[id << 1]);
      st.erase(A[(id << 1) | 1]);
    }
  }

  for (int i = 1; i <= n + q; i++) {
    // printf("circle %d: (%d,%d) r=%d, par=%d\n", i, C[i].x, C[i].y, C[i].r, C[i].par);
    C[C[i].par].E.push_back(i);
  }
}

void DP(int p) {
  Circle &cur = C[p];
  cur.dp[0] = 0;
  cur.dp[1] = 1;
  for (int t: cur.E) {
    DP(t);
    cur.dp[0] += max(C[t].dp[0], C[t].dp[1]);
    cur.dp[1] += C[t].dp[0];
  }
  if (p > n) {
    ans[p - n] = max(cur.dp[0], cur.dp[1]);
    cur.dp[0] = 0;
    cur.dp[1] = 0;
    for (int t: cur.E) {
      cur.dp[0] += C[t].dp[0];
      cur.dp[1] += max(C[t].dp[0], C[t].dp[1]);
    }
  }
}

int main() {
  C[0].par = -1;
  scanf("%d%d", &n, &q);
  for (int i = 1; i <= n + q; i++) {
    scanf("%d%d%d", &C[i].x, &C[i].y, &C[i].r);
    C[i].id = i;
    A[i << 1] = Arc(C + i, false);
    A[(i << 1) | 1] = Arc(C + i, true);
    events[++en] = pii(C[i].x - C[i].r, i);
    events[++en] = pii(C[i].x + C[i].r, -i);
  }

  ProcessCircles();
  DP(0);

  for (int i = 1; i <= q; i++) {
    printf("%d\n", ans[i]);
  }
  return 0;
}