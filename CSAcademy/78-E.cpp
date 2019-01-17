/*
	- https://csacademy.com/contest/round-78/task/xor-transform/solution/
*/

#include <bits/stdc++.h>
using namespace std;

int n, m, q, dp[1<<23];
unsigned long long x, ha;
vector<vector<int>> a;

unsigned long long nextInt() {
	unsigned long long z=(x+=0x9E3779B97F4A7C15ULL);
	z=(z^z>>30)*0xBF58476D1CE4E5B9ULL;
	z=(z^z>>27)*0x94D049BB133111EBULL;
	return z^z>>31;
}

int rng() {
	return 1+(nextInt()>>33);
}

int main() {
	cin >> n >> m >> q >> x;
	for(int i=0; i<n; ++i)
		for(int j=0; j<m; ++j)
			dp[i|j]^=rng();
	for(int k=0; k<23; ++k)
		for(int i=0; i<1<<23; ++i)
			if(i>>k&1)
				dp[i]^=dp[i^1<<k];
	for(int i=1; i<=q; ++i)
		ha^=(unsigned long long)i*dp[rng()&((1<<23)-1)];
	cout << ha;
}
