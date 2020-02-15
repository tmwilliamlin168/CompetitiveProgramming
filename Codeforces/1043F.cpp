#include <bits/stdc++.h>
using namespace std;

const int mxN=3e5;
int n, a[mxN], c[mxN+1], mo[mxN+1], lp[mxN+1], g, ans, dp[1<<6], e[1<<6];
vector<int> p;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	for(int i=2; i<=mxN; ++i) {
		if(!lp[i]) {
			lp[i]=i;
			p.push_back(i);
		}
		for(int j=0; j<p.size()&&p[j]<=lp[i]&&i*p[j]<=mxN; ++j)
			lp[i*p[j]]=p[j];
	}
	cin >> n;
	for(int i=0; i<n; ++i)
		cin >> a[i], ++c[a[i]];
	for(int i=1; i<=mxN; ++i) {
		if(!c[i])
			continue;
		for(int j=1; j*j<=i; ++j) {
			if(i%j)
				continue;
			++mo[j];
			if(j*j<i)
				++mo[i/j];
		}
		g=__gcd(i, g);
	}
	if(g>1) {
		cout << -1;
		return 0;
	}
	ans=n;	
	for(int i=1; i<=mxN; ++i) {
		if(!c[i])
			continue;
		vector<int> ps;
		int i2=i;
		while(i2>1) {
			int z=lp[i2];
			while(lp[i2]==z)
				i2/=z;
			ps.push_back(z);
		}
		for(int j=0; j<1<<ps.size(); ++j) {
			int b=1;
			for(int k=0; k<ps.size(); ++k)
				if(j>>k&1)
					b*=ps[k];
			dp[j]=mo[b];
		}
		for(int j=0; j<ps.size(); ++j)
			for(int k=0; k<1<<ps.size(); ++k)
				if(k>>j&1^1)
					dp[k]-=dp[k^1<<j];
		for(int j=0; j<1<<ps.size(); ++j)
			for(int k=0; k<ps.size(); ++k)
				if(j>>k&1)
					dp[j]=max(dp[j^1<<k], dp[j]);
		memset(e, 1, 4*(1<<ps.size()));
		e[(1<<ps.size())-1]=0;
		for(int j=(1<<ps.size())-1; j>=0; --j) {
			for(int m=j; ; m=(m-1)&j) {
				int f=((1<<ps.size())-1)^m;
				if(dp[f])
					e[j&f]=min(e[j]+1, e[j&f]);
				if(!m)
					break;
			}
		}
		ans=min(e[0]+1, ans);
	}
	cout << ans;
}
