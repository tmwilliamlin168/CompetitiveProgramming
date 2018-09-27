#include <bits/stdc++.h>
using namespace std;

const int mxN=2e5, mxA=2e6, M=1e9+7;
int n, p[mxN], spf[mxA+1];
vector<int> pfs;
array<int, 2> a[mxA+1];
bool c[mxN];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	for(int i=2; i<=mxA; ++i) {
		if(!spf[i]) {
			pfs.push_back(i);
			spf[i]=i;
		}
		for(int j=0; j<pfs.size()&&pfs[j]<=spf[i]&&i*pfs[j]<=mxA; ++j)
			spf[i*pfs[j]]=pfs[j];
	}
	cin >> n;
	for(int i=0; i<n; ++i)
		cin >> p[i];
	sort(p, p+n, greater<int>());
	for(int i=0; i<n; ++i) {
		c[i]=a[p[i]][0];
		int b=c[i]?p[i]-1:p[i];
		while(spf[b]) {
			int c=spf[b], d=0;
			while(b%c==0) {
				b/=c;
				++d;
			}
			if(a[c][0]<d)
				a[c]={d};
			if(a[c][0]==d)
				++a[c][1];
		}
	}
	long long ans=1;
	for(int i=2; i<=mxA; ++i)
		for(int j=0; j<a[i][0]; ++j)
			ans=i*ans%M;
	for(int i=0; i<n; ++i) {
		if(!c[i])
			continue;
		int b=p[i]-1;
		bool ok=1;
		while(spf[b]&&ok) {
			int c=spf[b], d=0;
			while(b%c==0) {
				b/=c;
				++d;
			}
			ok=a[c]>array<int, 2>{d, 1};
		}
		if(ok) {
			++ans;
			break;
		}
	}
	cout << ans;
}
