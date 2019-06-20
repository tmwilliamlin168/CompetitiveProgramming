#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	int t, n;
	cin >> t;
	for(int ti=1; ti<=t; ++ti) {
		cin >> n;
		string a[n], b[n];
		for(int i=0; i<n; ++i) {
			cin >> b[i];
			while(a[i].size()<n)
				a[i]+=b[i];
		}
		bool d[n]={};
		string ans;
		for(int i=0, dl=n; i<n; ++i) {
			bool br=0, bp=0, bs=0;
			for(int j=0; j<n; ++j) {
				if(d[j])
					continue;
				if(a[j][i]=='R')
					br=1;
				else if(a[j][i]=='P')
					bp=1;
				else
					bs=1;
			}
			if(br&&bp&&bs&&dl) {
				ans="IMPOSSIBLE";
				break;
			}
			if(br&&!bs)
				ans.push_back('P');
			else if(bp&&!br)
				ans.push_back('S');
			else
				ans.push_back('R');
			for(int j=0; j<n; ++j) {
				if(a[j][i]=='R'&&ans.back()=='P'||a[j][i]=='P'&&ans.back()=='S'||a[j][i]=='S'&&ans.back()=='R') {
					dl-=!d[j];
					d[j]=1;
				}
			}
		}
		cout << "Case #" << ti << ": " << ans << "\n";
	}
}
