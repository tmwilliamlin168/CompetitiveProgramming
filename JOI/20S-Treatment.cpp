#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define ar array

const int mxN=1e5;
int w, n, t[mxN], l[mxN], r[mxN], c[mxN];
ll dp[mxN], ans=1e18;
vector<int> vx, ft[mxN+1];
priority_queue<ar<ll, 2>, vector<ar<ll, 2>>, greater<ar<ll, 2>>> pq;
bool vis[mxN];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> w >> n;
	memset(dp, 0x3f, 8*n);
	for(int i=0; i<n; ++i) {
		cin >> t[i] >> l[i] >> r[i] >> c[i], --l[i];
		if(!l[i]) {
			dp[i]=0;
			pq.push({c[i], i});
		} else
			vx.push_back(t[i]+l[i]);
	}
	sort(vx.begin(), vx.end());
	for(int i=0; i<n; ++i)
		if(l[i])
			for(int j=lower_bound(vx.begin(), vx.end(), t[i]+l[i])-vx.begin()+1; j<=vx.size(); j+=j&-j)
				ft[j].push_back(i);
	for(int i=1; i<=vx.size(); ++i) {
		sort(ft[i].begin(), ft[i].end(), [](const int &i, const int &j) {
			return t[i]-l[i]<t[j]-l[j];
		});
	}
	while(pq.size()) {
		ar<ll, 2> u=pq.top();
		pq.pop();
		for(int p=upper_bound(vx.begin(), vx.end(), t[u[1]]+r[u[1]])-vx.begin(); p; p-=p&-p) {
			while(ft[p].size()&&t[ft[p].back()]-l[ft[p].back()]>=t[u[1]]-r[u[1]]) {
				int v=ft[p].back();
				if(!vis[v]) {
					vis[v]=1;
					dp[v]=u[0];
					pq.push({u[0]+c[v], v});
				}
				ft[p].pop_back();
			}
		}
	}
	for(int i=0; i<n; ++i)
		if(r[i]>=w)
			ans=min(dp[i]+c[i], ans);
	cout << (ans>=1e18?-1:ans);
}
