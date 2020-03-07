#include <iostream>
#include <cstring>
#include <cstdio>
using ll = long long;
using namespace std;
const int maxn = 1000100, mod = 998244353;
char mu[maxn];
bool notPrime[maxn];
int prime[maxn / 8], pn;

ll qpow(ll N, int po = mod - 2) {
	ll cur = 1;
	for (; po; po >>= 1) {
		if (po & 1) {
			cur = cur * N % mod;
		}
		N = N * N % mod;
	}
	return cur;
}

void linearSieve(int N) {
	notPrime[1] = notPrime[0] = true;
	mu[1] = 1;
	for (int i = 2; i <= N; i++) {
		if (!notPrime[i]) {
			prime[pn++] = i;
			mu[i] = -1;
		}
		for (int j = 0; j < pn; j++) {
			if ((ll)i * prime[j] > N) break;
			notPrime[i * prime[j]] = true;
			if (i % prime[j] == 0) {
				break;
			} else {
				mu[i * prime[j]] = mu[i] * mu[prime[j]];
			}
		}
	}
}

inline void cmod(ll &val) {
	val %= mod;
	if (val < 0)
		val += mod;
}

ll ways(int m, int k) {
	ll tot = 1;
	for (int i = 1; i <= k; i++) {
		tot += mu[i] * (qpow(k / i * 2 + 1, m) - 1);
	}
	cmod(tot);
	return tot;
}

int main() {
	int m, k;
	cin >> m >> k;
	linearSieve(k);
	ll ans = ways(m, k);
	cmod(ans);
	cout << ans << endl; 
	return 0;
}
