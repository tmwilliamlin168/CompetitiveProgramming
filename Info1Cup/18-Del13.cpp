#include <bits/stdc++.h>
using namespace std;

const int mxN=1e5;
int t, n, q, a[mxN+2], dp[mxN+2][3];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> t;
	while(t--) {
		cin >> n >> q;
		for(int i=1; i<=q; ++i)
			cin >> a[i];
		a[q+1]=n+1;
		memset(dp, -1, (q+2)*sizeof(dp[0]));
		dp[0][0]=-2;
		for(int i=0; i<=q; ++i) {
			for(int j=0; j<3; ++j) {
				if(dp[i][j]==-1||a[i+1]-a[i]-1-j<0)
					continue;
				if((a[i+1]-a[i]-1-j)&1^1) {
					if(!(a[i+1]-a[i]-1-j)||j)
						dp[i+1][0]=j;
					if(a[i+1]-a[i]-1-j)
						dp[i+1][2]=j;
				} else
					dp[i+1][1]=j;
			}
		}
		if(dp[q+1][0]==-1) {
			cout << "-1\n";
			continue;
		}
		vector<int> ans;
		for(int i=q, j=0; ~i; j=dp[i+1][j], --i)
			for(int k=a[i+1]-a[i]-1-j-dp[i+1][j]; k; k-=2)
				ans.push_back((a[i]+a[i+1])/2);
		for(int i=q, j=0; ~i; j=dp[i+1][j], --i)
			for(int k=j; k; --k)
				ans.push_back(a[i+1]);
		cout << ans.size() << "\n";
		for(int ai : ans)
			cout << ai << " ";
		cout << "\n";
	}
}
