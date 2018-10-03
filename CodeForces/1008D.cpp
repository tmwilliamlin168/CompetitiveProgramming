/*
	- http://codeforces.com/blog/entry/60572 (First solution)
*/

#include <bits/stdc++.h>
using namespace std;

const int mxN=1e5, m=3;
int d[mxN+1], t, a[m], b[1<<m], a1, a2, c;
map<int, int> mp;
unordered_set<int> s;

inline int gcd(int a, int b) {
	while((a%=b)&&(b%=a));
	return a^b;
}

void rec(int i) {
	if(i>=m) {
		a2=1;
		c=0;
		for(auto it=mp.begin(); it!=mp.end(); ++it) {
			for(int j=0; j<it->second; ++j) {
				a2*=(b[it->first]+j);
				a2/=(j+1);
				c=c<<3|it->first;
			}
		}
		if(!s.insert(c).second)
			return;
		a1+=a2;
		return;
	}
	for(int j=1<<i; j<1<<m; j=(j+1)|1<<i) {
		++mp[j];
		rec(i+1);
		if(!(--mp[j]))
			mp.erase(j);
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	for(int i=1; i<=mxN; ++i)
		for(int j=i; j<=mxN; j+=i)
			++d[j];
	cin >> t;
	while(t--) {
		for(int i=0; i<m; ++i)
			cin >> a[i];
		for(int i=0; i<1<<m; ++i) {
			b[i]=0;
			for(int j=0; j<m; ++j)
				if((i>>j)&1)
					b[i]=gcd(b[i], a[j]);
			b[i]=d[b[i]];
		}
		for(int i=0; i<m; ++i)
			for(int j=0; j<1<<m; ++j)
				if((j>>i)&1^1)
					b[j]-=b[j^1<<i];
		a1=0;
		rec(0);
		cout << a1 << "\n";
		s.clear();
	}
}
