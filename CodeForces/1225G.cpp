#include <bits/stdc++.h>
using namespace std;

const int mxN=16, mxA=2000;
int n, k, a[mxN];
bitset<mxA+1> dp[1<<mxN];
vector<int> v[151];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> k;
	for(int i=0; i<n; ++i)
		cin >> a[i];
	dp[0][0]=1;
	for(int i=0; i<1<<n; ++i) {
		for(int j=mxA/k; j; --j)
			dp[i][j]=dp[i][j]|dp[i][j*k];
		for(int j=0; j<n; ++j)
			if(i>>j&1^1)
				dp[i^1<<j]|=dp[i]<<a[j];
	}
	if(!dp[(1<<n)-1][1]) {
		cout << "NO";
		return 0;
	}
	cout << "YES\n";
	for(int i=(1<<n)-1, j=1, l=0; i; ) {
		for(; j*k<=mxA&&dp[i][j*k]; j*=k, ++l);
		int m=0;
		for(; i>>m&1^1||j<a[m]||!dp[i^1<<m][j-a[m]]; ++m);
		i^=1<<m;
		j-=a[m];
		v[l].push_back(a[m]);
	}
	for(int i=150; i; --i) {
		while(v[i].size()) {
			cout << v[i].back() << " " << v[i][v[i].size()-2] << "\n";
			int x=v[i].back()+v[i][v[i].size()-2], j=i;
			v[i].pop_back();
			v[i].pop_back();
			for(; x%k<1; x/=k, --j);
			v[j].push_back(x);
		}
	}
}
