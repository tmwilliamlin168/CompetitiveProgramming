/*
	- http://codeforces.com/blog/entry/12277
*/

#include <bits/stdc++.h>
using namespace std;

const int mxN=2e5;
int n;
long long a[mxN];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	for(int i=0; i<n; ++i)
		cin >> a[i];
	int i=0, p1, p2, ans=0;
	while(1) {
		++ans;
		int j=i;
		while(j<n&&a[j]==-1)
			++j;
		if(j>=n)
			break;
		p1=j++;
		while(j<n&&a[j]==-1)
			++j;
		if(j>=n)
			break;
		p2=j++;
		if((a[p2]-a[p1])%(p2-p1)) {
			i=p2;
			continue;
		}
		int d=(a[p2]-a[p1])/(p2-p1);
		for(int k=p1-1; k>=i; --k)
			a[k]=a[k+1]-d;
		if(a[i]<=0) {
			i=p2;
			continue;
		}
		bool c=0;
		for(int k=p2+1; k<n&&!c; ++k) {
			if(a[k]==-1?a[k-1]+d<=0:a[k]!=a[k-1]+d) {
				i=k;
				c=1;
			} else
				a[k]=a[k-1]+d;
		}
		if(!c)
			break;
	}
	cout << ans;
}
