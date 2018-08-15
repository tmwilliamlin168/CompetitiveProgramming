#include <bits/stdc++.h>
using namespace std;

const int mxN=1e4, mxQ=100;
int n, l, a[mxN], ps[mxN+1], ans[mxN][mxQ+1], b[mxN+1], q, k[mxQ], k2[mxQ+1];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> l;
	for(int i=0; i<n; ++i)
		cin >> a[i];
	cin >> q;
	for(int i=0; i<q; ++i)
		cin >> k[i], k2[i]=k[i];
	sort(k2, k2+q);
	k2[q]=l;
	for(int i=0, p=-1; i<=q; ++i) {
		for(int j=p+1; j<=k2[i]; ++j)
			b[j]=i;
		p=k2[i];
	}
	for(int i=1; i<n-l+1; ++i) {
		for(int j=0; i+j<n; ++j)
			ps[j+1]=ps[j]+(a[j]!=a[i+j]);
		for(int j=0; j+l+i<=n; ++j) {
			++ans[j][b[ps[j+l]-ps[j]]];
			++ans[j+i][b[ps[j+l]-ps[j]]];
		}
	}
	for(int i=0; i<n-l+1; ++i)
		for(int j=0; j<q-1; ++j)
			ans[i][j+1]+=ans[i][j];
	for(int i=0; i<q; ++i) {
		for(int j=0; j<n-l+1; ++j)
			cout << ans[j][lower_bound(k2, k2+q, k[i])-k2] << " ";
		cout << "\n";
	}
}
