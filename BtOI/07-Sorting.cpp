- Consider the moves (i, j) that we will perform
- In an optimal solution, j will not increase
- Precalculate c[i][j] = number of elements which are not in suffix i and are smaller than j
- dp[i][j] = cost of creating subsequence [j, j+1, ..., n-1] when we consider the suffix i
- dp[i][j] -> dp[i][j-1]
	- Add c[i][j-1]+1 (position of j-1)
	- Move j-1 to position c[i][j-1]
- dp[i][j] -> dp[i-1][j-1] if A[i-1] is j-1
- dp[i][j] -> dp[i-1][j]
	- Either A[i-1] < j or A[i-1] > j
	- We can use c to find the positions when we swap and add it to the dp

#include <bits/stdc++.h>
using namespace std;

const int mxN=1e3;
int n, b[mxN], c[mxN+1][mxN+1];
array<int, 2> a[mxN];
array<int, 5> dp[mxN+1][mxN+1];
vector<array<int, 2>> m;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n;
	for(int i=0; i<n; ++i) {
		cin >> a[i][0], a[i][0]=-a[i][0];
		a[i][1]=i;
	}
	sort(a, a+n);
	for(int i=0; i<n; ++i)
		b[a[i][1]]=i;
	for(int i=0; i<n; ++i)
		for(int j=0; j<=n; ++j)
			c[i+1][j]=c[i][j]+(b[i]<j);
	memset(dp, 0x3f, sizeof(dp));
	dp[n][n]={0, -1, -1};
	for(int i=n; i>=0; --i) {
		for(int j=n; j>=0; --j) {
			if(i&&b[i-1]==j-1)
				dp[i-1][j-1]=min({{dp[i][j][0], i, j, -1}, dp[i-1][j-1]});
			if(i&&b[i-1]<j-1)
				dp[i-1][j]=min({{dp[i][j][0]+c[n][j]-c[n][b[i-1]]+c[i][b[i-1]], i, j, -1}, dp[i-1][j]});
			if(i&&b[i-1]>j-1)
				dp[i-1][j]=min({{dp[i][j][0]+c[i][b[i-1]]+1, i, j, -1}, dp[i-1][j]});
			if(j)
				dp[i][j-1]=min({{dp[i][j][0]+c[i][j-1]+1, i, j, c[i][j-1], j-1}, dp[i][j-1]});
		}
	}
	for(int i=0, j=0; i<n||j<n; tie(i, j)={dp[i][j][1], dp[i][j][2]})
		if(dp[i][j][3]!=-1)
			m.push_back({dp[i][j][3], dp[i][j][4]});
	reverse(m.begin(), m.end());
	cout << m.size() << "\n";
	for(array<int, 2> mi : m) {
		int s=-1;
		for(int i=0; i<mi[0]; ++i) {
			if(b[i]!=mi[1])
				continue;
			if(s==-1)
				s=i;
			swap(b[i], b[i+1]);
		}
		for(int i=n-1; i>mi[0]; --i) {
			if(b[i]!=mi[1])
				continue;
			if(s==-1)
				s=i;
			swap(b[i], b[i-1]);
		}
		cout << s+1 << " " << mi[0]+1 << "\n";
	}
}
