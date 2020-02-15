#include <bits/stdc++.h>
using namespace std;

const int mxN=2e5;
int q, lst, p[2*mxN], a[2*mxN], b[2*mxN], qt, l, r, x;
map<int, int> mp;

int gi(int x) {
	if(mp.find(x)==mp.end())
		mp.insert({x, mp.size()});
	return mp[x];
}

array<int, 2> find(int x) {
	if(x==p[x])
		return {x, 0};
	array<int, 2> c=find(p[x]);
	p[x]=c[0];
	b[x]^=c[1];
	return {p[x], b[x]};
}

void join(int x, int y, int d) {
	array<int, 2> a1=find(x), a2=find(y);
	if((x=a1[0])==(y=a2[0]))
		return;
	d^=a1[1]^a2[1];
	if(a[x]<a[y]) {
		p[x]=y;
		b[x]=d;
	} else {
		p[y]=x;
		b[y]=d;
	}
	a[x]+=a[x]==a[y];
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> q;
	for(int i=0; i<2*q; ++i)
		p[i]=i;
	while(q--) {
		cin >> qt >> l >> r, l^=lst, r^=lst;
		if(l>r)
			swap(l, r);
		++r;
		l=gi(l), r=gi(r);
		if(qt==1) {
			cin >> x, x^=lst;
			join(l, r, x);
		} else {
			array<int, 2> a1=find(l), a2=find(r);
			if(a1[0]!=a2[0]) {
				cout << "-1\n";
				lst=1;
			} else
				cout << (lst=a1[1]^a2[1]) << "\n";
		}
	}
}
