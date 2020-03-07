#include <iostream>
#include <cstdio>
#include <cstring>
#include <map>
#include <algorithm>
using ll = long long;
using namespace std;
using pii = pair<int, int>;
const int maxn = 520;
int n, m;
char G[maxn][maxn];
int dx[] = {0, 0, -1, 1};
int dy[] = {-1, 1, 0, 0};
pii nxt[maxn][maxn][4];
int posToInt[maxn][maxn];

struct Node {
  pii nxt[4];
  int vis;
  bool isV;
  bool assignV;
  bool computed;
} nodes[maxn * maxn];
int timeStamp;

pii FindNext(int x, int y, int enter) {
  if (posToInt[x][y])
    return pii(posToInt[x][y], enter);
  int out = enter;
  if (x < 1 || x > n || y < 1 || y > m) {
    out = enter ^ 1;
  }
  else if (G[x][y] == '/') {
    out = 3 - enter;
  }
  else if (G[x][y] == '\\') {
    out = enter ^ 2;
  }
  auto &ret = nxt[x][y][out];
  if (!ret.first) {
    ret = FindNext(x + dx[out], y + dy[out], out);
  }
  return ret;
}

void fill(int p) {
  if (p == -1) return;
  Node &cur = nodes[p];
  if (cur.computed) return;
  cur.computed = true;
  for (auto &t: cur.nxt) {
    fill(t.first);
  }
}

int dfs(int p, bool isV) {
  Node &cur = nodes[p];
  if (cur.vis == timeStamp) {
    if (isV != cur.assignV) {
      // printf("Inconsistent at %d, isV=%d\n", p, isV);
      return -1;
    }
    return 0;
  }
  // printf("%d isV = %d\n", p, isV);
  cur.vis = timeStamp;
  cur.assignV = isV;
  int ret = nodes[p].isV ^ isV;
  // isV == d > 1

  for (int d = 0; d < 4; d++) {
    auto &edge = nodes[p].nxt[d];
    bool shouldTurn = (d > 1) ^ isV;
    if (edge.first == -1) {
      if (shouldTurn) continue;
      // printf("fail at %d, isV=%d\n", p, isV);
      return -1;
    }
    int tmp = dfs(edge.first, shouldTurn ^ (edge.second > 1));
    if (tmp == -1)
      return -1;
    ret += tmp;
  }

  return ret;
}

int main() {
  cin >> n >> m;
  int cnt = 0;
  for (int i = 1; i <= n; i++) {
    cin >> (G[i] + 1);
    for (int j = 1; j <= m; j++) {
      if (G[i][j] == 'V' || G[i][j] == 'H') {
        posToInt[i][j] = ++cnt;
      }
      else if (G[i][j] == '#') {
        posToInt[i][j] = -1;
      }
    }
  }

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      int id = posToInt[i][j];
      if (id > 0) {
        nodes[id].isV = G[i][j] == 'V';
        for (int d = 0; d < 4; d++) {
          nodes[id].nxt[d] = FindNext(i + dx[d], j + dy[d], d);
          // printf("[%d] (%d,%d): nxt = %d, dir=%d->%d\n", id, i, j, nodes[id].nxt[d].first, d, nodes[id].nxt[d].second);
        }
      }
    }
  }

  int ans = 0;
  for (int i = 1; i <= cnt; i++) {
    if (nodes[i].computed) continue;
    timeStamp++;
    int ans1 = dfs(i, 0);
    timeStamp++;
    int ans2 = dfs(i, 1);
    fill(i);
    if (max(ans1, ans2) == -1) {
      ans = -1;
      break;
    }
    if (ans1 == -1) ans1 = ans2;
    if (ans2 == -1) ans2 = ans1;
    int acc = min(ans1, ans2);
    // printf("acc = %d\n", acc);
    ans += acc;
  }

  cout << ans << endl;

  return 0;
}