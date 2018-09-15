/*
	- The swaps form a binary tree
	- dp[i][j] = minimal permutation of subtree i if node i has been set to j
	- At most O(nlogn) states, O(subtree size) per transition, O(nlog^2n) total
*/

#include <bits/stdc++.h>
using namespace std;

const int mxN=2e5;
int n, a[mxN+1];
vector<int> dp[mxN+1][36], v1, v2;
bool v[mxN+1][36];

void mrg(vector<int> &v, vector<int> &a, vector<int> &b) {
	for(int l=1, i=0, j=0; i<a.size()||j<b.size(); i+=l, j+=l, l*=2) {
		for(int k=0; k<l&&i+k<a.size(); ++k)
			v.push_back(a[i+k]);
		for(int k=0; k<l&&j+k<b.size(); ++k)
			v.push_back(b[j+k]);
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	for(int i=1; i<=n; ++i)
		cin >> a[i];
	v[1][0]=1;
	for(int i=1; 2*i+1<=n; ++i) {
		for(int j=0; j<36; ++j) {
			if(!v[i][j])
				continue;
			int b=i>>j/2^j&1;
			if(2*i+1<=n) {
				if(a[2*i+1]<a[b]&&a[2*i+1]<a[2*i])
					v[2*i][0]=v[2*i+1][j+2]=v[2*i][j+2]=v[2*i+1][1]=1;
				else
					v[2*i][a[b]>a[2*i]?j+2:0]=v[2*i+1][0]=1;
			}
		}
	}
	for(int i=n; i; --i) {
		for(int j=0; j<36; ++j) {
			if(!v[i][j])
				continue;
			int b=i>>j/2^j&1;
			if(2*i+1<=n) {
				if(a[2*i+1]<a[b]&&a[2*i+1]<a[2*i]) {
					v1={a[2*i+1]};
					v2={a[2*i+1]};
					mrg(v1, dp[2*i][0], dp[2*i+1][j+2]);
					mrg(v2, dp[2*i][j+2], dp[2*i+1][1]);
					dp[i][j]=min(v1, v2);
				} else {
					dp[i][j]={min(a[b], a[2*i])};
					mrg(dp[i][j], dp[2*i][a[b]>a[2*i]?j+2:0], dp[2*i+1][0]);
				}
			} else if(2*i<=n)
				dp[i][j]={min(a[b], a[2*i]), max(a[b], a[2*i])};
			else
				dp[i][j]={a[b]};
		}
		if(2*i+1<=n)
			for(int j=0; j<2; ++j)
				for(int k=0; k<36; ++k)
					if(v[2*i+j][k])
						vector<int>().swap(dp[2*i+j][k]);
	}
	for(int b : dp[1][0])
		cout << b << " ";
}
