#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pii pair<int, int>
#define pil pair<int, ll>

const int mxN=1e5+1;
int n, a[mxN];
ll k;
pil dp[mxN], ft[mxN+1];
vector<pii> b[mxN+1];
bool inlis[mxN];

pil operator+(const pil &a, const pil &b) {
	if(a.first>b.first)
		return a;
	if(a.first<b.first)
		return b;
	return {a.first, min(a.second+b.second, k)};
}

//fenwick tree update
void upd(int i, pil x) {
	for(i=n-i; i<=n; i+=i&-i)
		ft[i]=ft[i]+x;
}

//fenwick tree query
pil qry(int i) {
	pil r={};
	for(i=n-i; i; i-=i&-i)
		r=r+ft[i];
	return r;
}

int main() {
	ifstream cin("itout.in");
	ofstream cout("itout.out");
	
	//input
	//add a 0 in front to make things easier
	cin >> n >> k, ++n;
	for(int i=1; i<n; ++i)
		cin >> a[i];
	//do the normal LIS dp
	for(int i=n-1; i>=0; --i) {
		dp[i]=qry(a[i]);
		dp[i]=pil(dp[i].first+1, dp[i].second)+pil(1, 1);
		upd(a[i], dp[i]);
		//add element to bucket according to length of LIS
		b[dp[i].first].push_back({a[i], i});
	}
	//restore kth largest LIS
	for(int i=1; i<=n; ++i)
		sort(b[i].begin(), b[i].end(), greater<pii>());
	for(int i=0; ; ) {
		inlis[a[i]]=1;
		if(dp[i].first==1)
			break;
		//iterate over possible next elements
		for(pii p : b[dp[i].first-1]) {
			int j=p.second;
			if(j<i)
				continue;
			if(dp[j].second>=k) {
				i=j;
				break;
			} else
				k-=dp[j].second;
		}
	}
	//output the complement
	cout << n-dp[0].first << "\n";
	for(int i=0; i<n; ++i)
		if(!inlis[i])
			cout << i << "\n";
}
