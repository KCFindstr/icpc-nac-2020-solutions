#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <map>
using ull = unsigned long long;
using ll = long long;
using namespace std;
using SeqHash = pair<ull, int>;
const int maxn = 5650, mod = 998244353, mul = 31;
int n, m, a[12];
int f[12][maxn];
int seqN;

inline SeqHash GetHash(vector<int> &seq) {
  sort(seq.begin(), seq.end(), greater<int>());
  while (seq.back() == 0) seq.pop_back();
  SeqHash ret;
  for (int val: seq) {
    ret.first = ret.first * mul + val;
    ret.second = ((ll)ret.second * mul + val) % mod;
  }
  return ret;
}

inline int GetSeqFromInt(vector<int> &seq) {
  static map<SeqHash, int> seqToInt;
  auto hashVal = GetHash(seq);
  auto it = seqToInt.find(hashVal);
  if (it == seqToInt.end()) {
    seqToInt[hashVal] = ++seqN;
    return seqN;
  }
  return it->second;
}

int dp(int day, vector<int> S);
int helper(int day, int burger, vector<int> &S, vector<int> &add, int maxAdd = n) {
  if (burger < 0) {
    return 0;
  }
  if (S.empty()) {
    return burger == 0 ? dp(day + 1, add) : 0;
  }
  int v = S.back();
  S.pop_back();

  int lim = min(maxAdd, v);
  bool keepMax = S.empty() ? false: S.back() == v;

  int ret = 0;

  for (int i = 0; i <= lim; i++) {
    add.push_back(i);
    add.push_back(v - i);

    ret = max(ret, helper(day, burger - i, S, add, keepMax ? i : n));

    add.pop_back();
    add.pop_back();

    if (ret == n) break;
  }

  S.push_back(v);
  return ret;
}

int dp(int day, vector<int> S) {
  int state = GetSeqFromInt(S);
  int &ret = f[day][state];
  if (ret != -1) {
    return ret;
  }

  ret = 0;
  if (day > m) {
    for (int i: S) {
      ret += i == 1;
    }
    return ret;
  }

  vector<int> nS;

  ret = helper(day, a[day], S, nS);

  return ret;
}

int main() {
  cin >> n >> m;
  for (int i = 1; i <= m; i++) {
    cin >> a[i];
    a[i] = min(a[i], n - a[i]);
  }
  sort(a + 1, a + 1 + m, greater<int>());
  vector<int> init {n};
  memset(f, -1, sizeof(f));
  cout << dp(1, init);
  return 0;
}