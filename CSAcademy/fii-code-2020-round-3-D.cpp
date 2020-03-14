#include <bits/stdc++.h>
using namespace std;

const int mxN=2e6;
int n, p[2*mxN+2], ft[mxN+1];
string s;
char s2[2*mxN+3];
vector<int> ta[mxN];

void upd(int i, int x) {
	for(++i; i<=n; i+=i&-i)
		ft[i]+=x;
}

int qry(int i) {
	int r=0;
	for(; i; i-=i&-i)
		r+=ft[i];
	return r;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> s;
	n=s.size();
	s2[0]='!', s2[1]='#', s2[2*n+2]='@';
	for(int i=0; i<n; ++i) {
		s2[2*i+2]=s[i];
		s2[2*i+3]='#';
	}
	for(int i=1, c=0, r=0; i<2*n+2; ++i) {
		if(r>=i)
			p[i]=min(r-i, p[2*c-i]);
		while(s2[i+p[i]]==s2[i-p[i]])
			++p[i];
		--p[i];
		if(i+p[i]>r) {
			c=i;
			r=i+p[i];
		}
	}
	long long ans=0;
	for(int i=n-1; ~i; --i) {
		ans+=qry(i+1+p[2*i+3]/2);
		upd(i, 1);
		if(i-p[2*i+3]/2>=0)
			ta[i-p[2*i+3]/2].push_back(i);
		for(int j : ta[i])
			upd(j, -1);
	}
	cout << ans;
}
