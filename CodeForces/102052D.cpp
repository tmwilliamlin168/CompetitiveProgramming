#include <bits/stdc++.h>
using namespace std;

const int mxN=200;
int n, m, c1[mxN+1][mxN+1][mxN+1], c2[mxN+1][mxN+1][mxN+1];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> m;
	vector<int> oa(n), ob(m), a, b;
	for(int i=0; i<n; ++i)
		cin >> oa[i];
	for(int i=0; i<m; ++i)
		cin >> ob[i];
	int lb=-m, rb=n-1;
	while(lb<rb) {
		int mb=lb+(rb-lb+1)/2;
		if(mb>0) {
			a=vector<int>(oa.begin(), oa.end()-mb);
			b=ob;
		} else {
			a=oa;
			b=vector<int>(ob.begin(), ob.end()+mb);
		}
		bool ok;
		for(int i=0; i<=a.size(); ++i) {
			for(int j=0; j<=b.size(); ++j) {
				for(int k=0; k<=b.size(); ++k) {
					int dp1=i?c2[i-1][j][min(k+a[a.size()-i], (int)b.size())]:0, dp2=j?max(c1[i][j-1][k]-b[b.size()-j], 0):n;
					c1[i][j][k]=min(dp1, i?c1[i-1][j][k]+1:n);
					if(i==a.size()&&j==b.size()&&!k)
						ok=dp1;
					c2[i][j][k]=max(dp2, j&&k?c2[i][j-1][k-1]:0);
				}
			}
		}
		if(ok)
			lb=mb;
		else
			rb=mb-1;
	}
	if(lb>=0)
		cout << "Gandalf " << lb;
	else
		cout << "Saruman " << -lb-1;
}
