#include <bits/stdc++.h>
using namespace std;

#define ll long long

pair<ll, int> w[200001];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n, i;
	ll l, u, sum=0;
	cin >> n >> l >> u;
	pair<ll, int> *w = new pair<ll, int>[n+1];
	for(i=0; i<n; ++i)
		cin >> w[i].first, w[i].second=i;
	sort(w, w+n);
	w[n]=make_pair(1LL<<31, -1);
	for(i=0; sum<=u; sum+=w[i].first, ++i);
	sum-=w[--i].first;
	for(int j=0; j<=min(i, n-i); sum+=w[n-1-j].first-w[j].first, ++j) {
		if(sum>=l) {
			cout << i << "\n";
			for(int k=j; k<i; ++k)
				cout << w[k].second << " ";
			for(int k=0; k<j; ++k)
				cout << w[n-1-k].second << " ";
			return 0;
		}
	}
	cout << 0;
}
