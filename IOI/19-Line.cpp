#include <bits/stdc++.h>
using namespace std;

#define ar array

const int mxN=1e5;
int n;
ar<int, 4> a[mxN];
vector<ar<int, 2>> ans, d[2];
priority_queue<ar<int, 2>> pq[4];
bool r[mxN];
vector<ar<int, 4>> rt;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	for(int i=0; i<n; ++i) {
		cin >> a[i][0] >> a[i][1];
		a[i][2]=-a[i][0];
		a[i][3]=-a[i][1];
		for(int j=0; j<4; ++j)
			pq[j].push({a[i][j], i});
	}
	while(pq[0].size()) {
		int u[4]={pq[0].top()[1]};
		if(r[u[0]]) {
			pq[0].pop();
			continue;
		}
		for(int k=1; k<4; ++k) {
			u[k]=pq[k].top()[1];
			while(r[u[k]]) {
				pq[k].pop();
				u[k]=pq[k].top()[1];
			}
		}
		bool ok=1;
		for(int k=0; k<4&&ok; ++k) {
			if(u[k]==u[(k+1)%4]) {
				r[u[k]]=1;
				d[k&1].push_back({a[u[k]][0], a[u[k]][1]});
				ok=0;
			}
		}
		if(ok) {
			rt.push_back({});
			for(int k=0; k<4; ++k) {
				rt.back()[k]=u[k];
				r[u[k]]=1;
			}
		}
	}
	ans={{}};
	for(int i=(int)rt.size()-1; ~i; --i) {
		ans.back()[1]=a[rt[i][3]][1];
		int r=0, l=2;
		if(ans.back()[0]>a[rt[i][3]][0])
			swap(r, l);
		ans.push_back({a[rt[i][r]][0], ans.back()[1]});
		ans.push_back({ans.back()[0], a[rt[i][1]][1]});
		ans.push_back({a[rt[i][l]][0], ans.back()[1]});
		ans.push_back({ans.back()[0]});
	}
	reverse(ans.begin(), ans.end());
	sort(d[0].begin(), d[0].end());
	ans.push_back({});
	for(int i=0; i<d[0].size(); ++i) {
		ans.back()[i&1^1]=d[0][i][i&1^1];
		ans.push_back(d[0][i]);
	}
	sort(d[1].begin(), d[1].end());
	if(d[0].size()&1)
		reverse(d[1].begin(), d[1].end());
	ans.back()[d[0].size()&1^1]=1e9;
	ans.push_back(ans.back());
	ans.back()[d[0].size()&1]=0;
	for(int i=0; i<d[1].size(); ++i) {
		ans.back()[i&1^d[0].size()&1]=d[1][i][i&1^d[0].size()&1];
		ans.push_back(d[1][i]);
	}
	cout << ans.size() << "\n";
	for(auto a : ans)
		cout << a[0] << " " << a[1] << "\n";
}
