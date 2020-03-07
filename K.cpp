#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
using ll = long long;
using namespace std;
const int maxn = 200010;
int n, q, dep[maxn];
struct Query {
  int u, v;
  ll ans;
} query[maxn];
vector<int> G[maxn];
vector<Query*> Q[maxn];
int fa[maxn];

int findfa(int son) {
  return fa[son] == son ? son : fa[son] = findfa(fa[son]);
}

void dfs(int p, int par = -1) {
  for (int t: G[p]) {
    if (t == par) continue;
    dep[t] = dep[p] + 1;
    dfs(t, p);
    fa[t] = p;
  }
  for (auto &que: Q[p]) {
    if (que->v == p) {
      swap(que->u, que->v);
    }
    if (!dep[que->v]) continue;
    int lca = findfa(que->v);
    ll L = dep[que->u] - dep[lca] + dep[que->v] - dep[lca] + 1;
    que->ans = L * (L + 1) / 2 + n - L;
  }
}

int main() {
  memset(dep, -1, sizeof(dep));
  scanf("%d%d", &n, &q);
  for (int i = 1; i < n; i++) {
    int x, y;
    scanf("%d%d", &x, &y);
    G[x].push_back(y);
    G[y].push_back(x);
  }
  for (int i = 1; i <= n; i++) {
    fa[i] = i;
  }
  for (int i = 1; i <= q; i++) {
    scanf("%d%d", &query[i].u, &query[i].v);
    Q[query[i].u].push_back(query + i);
    Q[query[i].v].push_back(query + i);
  }
  dep[1] = 1;
  dfs(1);
  for (int i = 1; i <= q; i++) {
    printf("%lld\n", query[i].ans);
  }
  return 0;
}