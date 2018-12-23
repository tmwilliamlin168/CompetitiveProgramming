#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define ar array

const int mxN=1e5;
int n, a[mxN+2];
vector<ar<ll, 2>> ch;

ll cross(ar<ll, 2> o, ar<ll, 2> a, ar<ll, 2> b) {
	return (a[0]-o[0])*(b[1]-o[1])-(a[1]-o[1])*(b[0]-o[0]);
}

int main() {
	ifstream cin("balance.in");
	ofstream cout("balance.out");
	
	//input
	cin >> n;
	for(int i=1; i<=n; ++i)
		cin >> a[i];
	//find the convex hull
	//note we only need the upper part
	for(int i=0; i<=n+1; ++i) {
		while(ch.size()>1&&cross(ch[ch.size()-2], ch.back(), {i, a[i]})>0)
			ch.pop_back();
		ch.push_back({i, a[i]});
	}
	//two pointers to traverse the convex hull
	for(int i1=1, i2=0; i1<=n; ++i1) {
		while(i2+1<ch.size()&&ch[i2+1][0]<i1)
			++i2;
		//output height of the convex hull at point i1
		cout << (ll)(((__int128)100000*((ch[i2+1][1]-ch[i2][1])*(i1-ch[i2][0])+ch[i2][1]*(ch[i2+1][0]-ch[i2][0])))/(ch[i2+1][0]-ch[i2][0])) << "\n";
	}
}
