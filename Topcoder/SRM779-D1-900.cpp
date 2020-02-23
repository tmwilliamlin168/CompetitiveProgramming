#include <bits/stdc++.h>
using namespace std;

#define ll long long

class ParadePlanner {
public:
	bool g[500][500];
	int p[500], d[500];
	ll count(int n, int seed, int threshold, vector<int> toggle) {
		for(int x=0; x<n; ++x) {
			for(int y=x+1; y<n; ++y) {
				seed=(seed*1103515245ll+12345)&((1ll<<31)-1);
				if(seed<threshold)
					g[x][y]=g[y][x]=1;
			}
		}
		for(int i=0; i<toggle.size(); i+=2) {
			int x=toggle[i], y=toggle[i+1];
			g[x][y]^=1;
			g[y][x]^=1;
		}
		ll ans=0;
		for(int i=0; i<n; ++i)
			for(int j=0; j<n; ++j)
				d[i]+=g[i][j];
		for(int i=0; i<n; ++i)
			for(int j=0; j<n; ++j)
				if(g[i][j])
					p[i]+=d[j]-1;
		for(int i=0; i<n; ++i) {
			for(int j=i+1; j<n; ++j) {
				int c=0;
				for(int k=0; k<n; ++k)
					c+=g[i][k]&&g[j][k];
				ans-=2*c*(c-1);
				if(g[i][j]) {
					ans+=2ll*(p[i]-d[j]+1)*(p[j]-d[i]+1);
					for(int k=j+1; k<n; ++k)
						if(g[i][k]&&g[j][k])
							ans-=6+6*(d[i]+d[j]+d[k]-6);
				}
			}
		}
		return ans;
	}
};
