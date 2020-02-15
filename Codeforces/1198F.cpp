#include <bits/stdc++.h>
using namespace std;

const int mxN=1e5;
int n, a[mxN], b[mxN], c;
vector<int> v[9];
array<int, 4> dp[512][512];

vector<int> pf(int x) {
	vector<int> p;
	for(int i=2; i*i<=x; ++i) {
		if(x%i)
			continue;
		p.push_back(i);
		while(x%i==0)
			x/=i;
	}
	if(x>1)
		p.push_back(x);
	return p;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n;
	for(int i=0; i<n; ++i)
		cin >> a[i];
	while(~c) {
		b[c]=1;
		int g1=0, g2=0;
		for(int i=0; i<n; ++i)
			if(b[i]==1)
				g1=__gcd(g1, a[i]);
		vector<int> p1=pf(g1);
		for(int i=0; i<n; ++i) {
			if(b[i]==1)
				continue;
			b[i]=2;
			for(int j=0; j<p1.size(); ++j) {
				if(a[i]%p1[j]&&v[j].size()<p1.size()+9) {
					v[j].push_back(i);
					b[i]=0;
				}
			}
			if(b[i])
				g2=__gcd(g2, a[i]);
		}
		c=-1;
		if(!g2) {
			for(int i=0; i<n; ++i) {
				if(!b[i]) {
					b[i]=2;
					g2=a[i];
					c=i;
					break;
				}
			}
			if(c<0)
				break;
		}
		vector<int> p2=pf(g2);
		memset(dp, 0, sizeof(dp[0])<<p1.size());
		dp[0][0][0]=1;
		for(int i=0; i<n; ++i) {
			if(b[i])
				continue;
			int m=0;
			for(int j=0; j<p1.size(); ++j)
				m|=(a[i]%p1[j]>0)<<j;
			for(int j=0; j<1<<p1.size(); ++j)
				for(int k=0; k<1<<p2.size(); ++k)
					if(dp[j][k][0]&&!dp[j|m][k][0])
						dp[j|m][k]={1, i, j, k};
			m=0;
			for(int j=0; j<p2.size(); ++j)
				m|=(a[i]%p2[j]>0)<<j;
			for(int j=0; j<1<<p1.size(); ++j)
				for(int k=0; k<1<<p2.size(); ++k)
					if(dp[j][k][0]&&dp[j][k][1]^i&&!dp[j][k|m][0])
						dp[j][k|m]={2, i, j, k};
		}
		if(dp[(1<<p1.size())-1][(1<<p2.size())-1][0]) {
			for(array<int, 2> i{(1<<p1.size())-1, (1<<p2.size())-1}; i[0]||i[1]; i={dp[i[0]][i[1]][2], dp[i[0]][i[1]][3]})
				b[dp[i[0]][i[1]][1]]=dp[i[0]][i[1]][0];
			cout << "YES\n";
			for(int i=0; i<n; ++i)
				cout << max(b[i], 1) << " ";
			return 0;
		}
	}
	cout << "NO";
}
