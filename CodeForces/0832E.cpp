#include <bits/stdc++.h>
using namespace std;

const int mxN=500, mxQ=300, M=1e9+7;
int mi[5]={0, 1, 3, 2, 4}, n, m, q;
vector<int> a[mxN];
long long ans=1;

void rs(int n) {
	for(int i=0; i<n; ++i) {
		string s;
		cin >> s;
		for(int j=0; j<m; ++j)
			a[j].push_back(s[j]-'a');
	}	
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m;
	rs(n);
	cin >> q;
	rs(q);
	int ei=0;
	for(int j=0; j<n; ++j) {
		for(int i=ei+1; i<m; ++i)
			if(a[i][j])
				swap(a[i], a[ei]);
		if(ei>=m||!a[ei][j]) {
			ans=ans*5%M;
			continue;
		}
		for(int i=n+q-1; i>=j; --i)
			a[ei][i]=a[ei][i]*mi[a[ei][j]]%5;
		for(int i=ei+1; i<m; ++i)
			for(int k=n+q-1; k>=j; --k)
				a[i][k]=(a[i][k]+4*a[ei][k]*a[i][j])%5;
		++ei;
	}
	for(int i=0; i<q; ++i) {
		bool ok=1;
		for(int j=ei; j<m&&ok; ++j)
			ok=!a[j][n+i];
		cout << (ok?ans:0) << "\n";
	}
}
