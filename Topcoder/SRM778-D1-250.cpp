#include <bits/stdc++.h>
using namespace std;
 
#define ll long long
#define ar array
 
class KRectangleIntersection {
public:
	ll solve(vector<ar<ll, 2>> &v, int m) {
		ll ans=0;
		sort(v.begin(), v.end());
		priority_queue<ll, vector<ll>, greater<ll>> pq;
		for(int i=0; i<v.size(); ++i) {
			pq.push(v[i][1]);
			if(pq.size()>m)
				pq.pop();
			if(pq.size()>=m)
				ans=max(ans, pq.top()-v[i][0]);
		}
		return ans;
	}
	ll maxIntersection(vector<int> xl, vector<int> yl, vector<int> xh, vector<int> yh, int m) {
		int n=xl.size();
		ll ans=0;
		for(int i=0; i<n; ++i) {
			for(int j=0; j<n; ++j) {
				if(xl[i]<xh[j]) {
					vector<ar<ll, 2>> v;
					for(int k=0; k<n; ++k)
						if(xl[k]<=xl[i]&&xh[k]>=xh[j])
							v.push_back({yl[k], yh[k]});
					ans=max(ans, solve(v, m)*(xh[j]-xl[i]));
				}
			}
		}
		return ans;
	}
};
