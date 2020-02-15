#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define ull unsigned long long

const int mxA=1e9, p2[6]={4, 9, 25, 49, 121, 169}, pp[7]={1, 4, 36, 900, 44100, 5336100, 901800900};
int ans=mxA+1, c0;
ull bs[mxA/64+1];
bool c[100000];
vector<int> pc[6];
ll x[6], r[6][6];
string s, t;

ll modI(ll a, ll m) {
	return (a%=m)<=1?1:(1-modI(m%a, a)*m)/a+m;
}

void chk(int i) {
	if(!i||i>=ans)
		return;
	for(int j=0; j<200; ++j)
		if((s[j]=='1')!=(bs[(i+j)/64]>>((i+j)%64)&1^1))
			return;
	ans=i;
}

void dfs(int i, int s=0) {
	if(i>=6) {
		for(int j=s; j<=mxA-199; j+=pp[6])
			chk(j);
		return;
	}
	for(int pci : pc[i]) {
		x[i]=pci;
		for(int j=0; j<i; ++j) {
			x[i]=r[j][i]*(x[i]-x[j])%p2[i];
			if(x[i]<0)
				x[i]+=p2[i];
		}
		dfs(i+1, s+x[i]*pp[i]);
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	for(int i=2; i*i<=mxA; ++i)
		if(!c[i]) {
			if(i==2) {
				ull a=0;
				for(int j=0; j<64; j+=4)
					a|=1ull<<j;
				for(int j=0; j<=mxA/64; ++j)
					bs[j]|=a;
			} else
				for(int j=0; (j+=i*i)<=mxA; )
					bs[j/64]|=1ull<<(j%64);
			for(int j=i*i; j<1e5; j+=i)
				c[j]=1;
		}
	for(int i=0; i<10; ++i) {
		cin >> t;
		s+=t;
	}
	for(char c : s)
		c0+=c=='0';
	for(int i=0; i<6; ++i) {
		for(int j=0; j<p2[i]; ++j) {
			bool ok=1;
			for(int k=j; k<200&&ok; k+=p2[i])
				ok=s[k]=='0';
			if(ok)
				pc[i].push_back((p2[i]-j)%p2[i]);
		}
	}
	if(c0>92||pc[0].size()>1||pc[1].size()>1||pc[2].size()>2||pc[3].size()>5) {
		cout << -1;
		return 0;
	}
	for(int i=1; i<6; ++i)
		for(int j=0; j<i; ++j)
			r[j][i]=modI(p2[j], p2[i]);
	dfs(0);
	cout << (ans>1e9?-1:ans);
}
