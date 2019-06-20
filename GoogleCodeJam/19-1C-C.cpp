#include <bits/stdc++.h>
using namespace std;

const int mxN=15;
int t, r, c, dp[mxN+1][mxN+1][mxN+1][mxN+1], a1[mxN][mxN+1], a2[mxN+1][mxN];
string g[mxN];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> t;
	for(int ti=1; ti<=t; ++ti) {
		cin >> r >> c;
		for(int i=0; i<r; ++i) {
			cin >> g[i];
			for(int j=0; j<c; ++j) {
				a1[i][j+1]=a1[i][j]+(g[i][j]=='#');
				a2[i+1][j]=a2[i][j]+(g[i][j]=='#');
			}
		}
		for(int l1=r-1; ~l1; --l1) {
			for(int r1=l1+1; r1<=r; ++r1) {
				for(int l2=c-1; ~l2; --l2) {
					for(int r2=l2+1; r2<=c; ++r2) {
						vector<int> v{999};
						for(int i=l1; i<r1; ++i)
							if(!(a1[i][r2]-a1[i][l2]))
								v.push_back(dp[l1][i][l2][r2]^dp[i+1][r1][l2][r2]);
						for(int i=l2; i<r2; ++i)
							if(!(a2[r1][i]-a2[l1][i]))
								v.push_back(dp[l1][r1][l2][i]^dp[l1][r1][i+1][r2]);
						sort(v.begin(), v.end());
						v.resize(unique(v.begin(), v.end())-v.begin());
						for(int i=0; ; ++i) {
							if(i^v[i]) {
								dp[l1][r1][l2][r2]=i;
								break;
							}
						}
					}
				}
			}
		}
		int ans=0;
		for(int i=0; i<r; ++i)
			if(!(a1[i][c]|dp[0][i][0][c]^dp[i+1][r][0][c]))
				ans+=c;
		for(int i=0; i<c; ++i)
			if(!(a2[r][i]|dp[0][r][0][i]^dp[0][r][i+1][c]))
				ans+=r;
		cout << "Case #" << ti << ": " << ans << "\n";
	}
}
