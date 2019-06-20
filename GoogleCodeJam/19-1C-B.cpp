#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	int t, f;
	cin >> t >> f;
	for(string ans, ve; t--; ) {
		vector<int> v(119);
		iota(v.begin(), v.end(), 0);
		bool u[5]={};
		for(int i=0; i<5; ++i) {
			vector<int> w[5];
			for(int vi : v) {
				cout << vi*5+i+1 << endl;
				cin >> ve;
				w[ve[0]-'A'].push_back(vi);
			}
			int mi=-1;
			for(int j=0; j<5; ++j)
				if(!u[j]&&(mi==-1||w[j].size()<w[mi].size()))
					mi=j;
			u[mi]=1;
			ans+='A'+mi;
			v=w[mi];
		}
		cout << ans << endl;
		cin >> ve;
	}
}
