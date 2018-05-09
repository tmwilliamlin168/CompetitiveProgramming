/*
	- We can make the problem stricter by pairing up consecutive elements and forcing them to be different
	- It becomes a classic bipartite coloring problem
	- Kind of intuitive that there are no odd cycles in the graph, so I didn't bother to prove it
*/

#include <bits/stdc++.h>
using namespace std;

const int mxN=1e5;
int n, a[mxN], b[mxN], op[mxN*2], ans[mxN*2];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	for(int i=0; i<n; ++i) {
		cin >> a[i] >> b[i], --a[i], --b[i];
		op[a[i]]=b[i];
		op[b[i]]=a[i];
	}
	for(int i=0; i<n; ++i)
		for(int j=a[i]; !ans[j]; j=op[op[j]^1]^1)
			ans[j]=ans[op[j]^1]=1, ans[op[j]]=ans[op[op[j]^1]]=2;
	for(int i=0; i<n; ++i)
		cout << ans[a[i]] << " " << ans[b[i]] << "\n";
}
