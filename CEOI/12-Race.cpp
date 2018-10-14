/*
	- dp1[l][r][a] = path with maximum length for range [l, r], going in direction a, ends at r
	- dp2[l][r][a] = same as dp1 except it doesn't end at r
	- dp3[l][r][a] = max of dp1[l][l..r][a]
	- We can find the answer with these DP's
	- Precompute (i+1)%n and (i-1)%n to not get TLE
*/

#include <bits/stdc++.h>
using namespace std;

const int mxN=500;
int n, ai, dp1[mxN][mxN][2], dp2[mxN][mxN][2], dp3[mxN][mxN][2], b[mxN][2];
bool k, adj[mxN][mxN];
array<int, 2> ans;

void c(int l, int r, int a) {
	if(adj[l][r]) {
		dp1[l][r][a]=1;
		dp2[l][r][a]=1+dp3[r][b[l][a]][a^1];
	} else
		dp1[l][r][a]=dp2[l][r][a]=-n;
	for(int k=b[l][a]; k!=r; k=b[k][a]) {
		dp1[l][r][a]=max(dp1[l][k][a]+dp1[k][r][a], dp1[l][r][a]);
		dp2[l][r][a]=max(dp1[l][k][a]+dp2[k][r][a], dp2[l][r][a]);
	}
	dp3[l][r][a]=max(dp2[l][r][a], dp3[l][b[r][a^1]][a]);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> k;
	for(int i=0; i<n; ++i) {
		cin >> ai;
		while(ai) {
			adj[i][ai-1]=1;
			cin >> ai;
		}
		b[i][0]=(i+n-1)%n;
		b[i][1]=(i+1)%n;
	}
	for(int l=1; l<n; ++l) {
		for(int i=0; i<n; ++i) {
			c(i, (i+l)%n, 1);
			c((i+l)%n, i, 0);
		}
	}
	for(int i=0; i<n; ++i)
		for(int j=0; j<n; ++j)
			for(int k=0; k<2; ++k)
				ans=max({{dp2[i][j][k], i}, ans});
	if(k) {
		for(int i=0; i<n; ++i) {
			for(int j=0; j<n; ++j) {
				for(int a=0; a<2; ++a) {
					if(dp1[i][j][a]<=0)
						continue;
					int k=b[j][a];
					for(; k!=i&&!adj[k][i]; k=b[k][a]);
					if(k!=i)
						for(int l=b[k][a]; l!=i; l=b[l][a])
							if(adj[j][l])
								ans=max({{2+dp1[i][j][a]+max(dp3[l][b[k][a]][a^1], dp3[l][b[i][a^1]][a]), k}, ans});
				}
			}
		}
	}
	cout << ans[0] << "\n" << ans[1]+1;
}
