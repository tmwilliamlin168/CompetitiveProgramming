/*
	- Construct the triangle with doubled dimensions of the triangle with maximum area
	- The constructed triangle's midpoints should be on the points of the original triangle
	- If a point is not in the constructed triangle, the original triangle doesn't have the maximum area
	- Triangle with maximum area is on convex hull
	- Brute force one point and use two pointers for the other two points to find the triangle with maximum area
*/

#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int mxN=5000;
int n, si;
ll s, x[mxN], y[mxN];
vector<int> ch;
bool used[mxN];

inline ll ta(int i, int j, int k) {
	i=ch[i], j=ch[j], k=ch[k];
	return abs(x[i]*y[j]+x[j]*y[k]+x[k]*y[i]-x[j]*y[i]-x[k]*y[j]-x[i]*y[k]);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> s;
	for(int i=0; i<n; ++i) {
		cin >> x[i] >> y[i];
		if(x[i]<x[si]||x[i]==x[si]&&y[i]<y[si])
			si=i;
	}
	ch.push_back(si);
	while(1) {
		int ni=-1;
		for(int i=0; i<n; ++i)
			if(!used[i]&&(i!=si||ch.size()>1)&&(ni==-1||(x[i]-x[ch.back()])*(y[ni]-y[ch.back()])>(y[i]-y[ch.back()])*(x[ni]-x[ch.back()])))
				ni=i;
		if(ni==si)
			break;
		ch.push_back(ni);
		used[ni]=1;
	}
	int a=0, b=1, c=2, ma=a, mb=b, mc=c, chs=ch.size();
	for(; a<chs; ++a) {
		for(b=(a+1)%chs, c=(a+2)%chs; (b+1)%chs!=a; b=(b+1)%chs) {
			while(c!=a&&ta(a, b, c)<=ta(a, b, (c+1)%chs))
				c=(c+1)%chs;
			if(ta(a, b, c)>ta(ma, mb, mc))
				ma=a, mb=b, mc=c;
		}
	}
	ma=ch[ma], mb=ch[mb], mc=ch[mc];
	cout << x[mb]+x[mc]-x[ma] << " " << y[mb]+y[mc]-y[ma] << "\n";
	cout << x[ma]+x[mc]-x[mb] << " " << y[ma]+y[mc]-y[mb] << "\n";
	cout << x[ma]+x[mb]-x[mc] << " " << y[ma]+y[mb]-y[mc] << "\n";
}
