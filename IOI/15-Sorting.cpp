/*
	- Binary search by answer
		- If there is a solution for the first i rounds, we can simply mirror the (i+1)th swap to get a solution for the first i+1 rounds
	- Assume that all of Aizhan's swaps are performed after all of Ermek's swaps
	- We can find cycles in the sequence after Ermek's swaps to know how Aizhan should swap
	- Each swap after Ermek's swaps can be replaced with a swap during Ermek's swaps
*/

#include <bits/stdc++.h>
using namespace std;

const int mxN=2e5;
int n, s[mxN], m, a[mxN], b[mxN], x[3*mxN], y[3*mxN];
bool vis[mxN];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	for(int i=0; i<n; ++i)
		cin >> s[i];
	cin >> m;
	for(int i=0; i<m; ++i)
		cin >> x[i] >> y[i];
	int lb=0, rb=n-1, mb, ss;
	while(lb<=rb) {
		mb=(lb+rb)/2, ss=0;
		memcpy(a, s, 4*n);
		for(int i=0; i<mb; ++i)
			swap(a[x[i]], a[y[i]]);
		memset(vis, 0, n);
		for(int i=0; i<n; ++i) {
			if(vis[i])
				continue;
			vis[i]=1;
			for(int j=i; !vis[a[j]]; j=a[j]) {
				vis[a[j]]=1;
				++ss;
			}
		}
		if(ss<=mb)
			rb=mb-1;
		else
			lb=mb+1;
	}
	cout << lb << "\n";
	ss=0;
	memcpy(a, s, 4*n);
	for(int i=0; i<lb; ++i)
		swap(a[x[i]], a[y[i]]);
	memset(vis, 0, n);
	for(int i=0; i<n; ++i)
		b[s[i]]=i;
	for(int i=0; i<n; ++i) {
		if(vis[i])
			continue;
		vis[i]=1;
		for(int j=i; !vis[a[j]]; j=a[j]) {
			vis[a[j]]=1;
			swap(s[x[ss]], s[y[ss]]);
			b[s[x[ss]]]=x[ss];
			b[s[y[ss]]]=y[ss];
			int pi=b[a[j]], qi=b[a[a[j]]];
			cout << pi << " " << qi << "\n";
			swap(s[pi], s[qi]);
			b[s[pi]]=pi;
			b[s[qi]]=qi;
			++ss;
		}
	}
	for(; ss<lb; ++ss)
		cout << "0 0\n";
}
