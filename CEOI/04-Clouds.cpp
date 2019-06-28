/*
	- We can fix the polygons and treat the laser like a ray
	- Find the segments of intersection for each polygon
	- Find the union of all segments
	- long double is not precise enough
*/

#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define ar array

const int mxN=1e3;
const ll B=1ll<<31;
int n, vx, vy, k, ans, x[2*mxN], y[2*mxN];
vector<ar<ll, 2>> ae{{1ll<<62, 1}}, re{{1ll<<62, 1}};

ll cp(ll x1, ll y1, ll x2, ll y2, ll x3, ll y3) {
	return (y3-y1)*(x2-x1)-(y2-y1)*(x3-x1);
}

ar<ll, 2> intproj(ll x1, ll y1, ll x2, ll y2, ll x3, ll y3) {
	if(x2==x3&&y2==y3)
		return {x1*x2+y1*y2, x1*x1+y1*y1};
	ar<ll, 2> r{y3*x2-y2*x3, y1*(x2-x3)-(y2-y3)*x1};
	if(r[1]<0) {
		r[0]=-r[0];
		r[1]=-r[1];
	}
	return r;
}

ar<ll, 2> mul(ll a, ll b) {
	ll a0=a%B, a1=a/B, b0=b%B, b1=b/B, c=a0*b1+a1*b0;
	ar<ll, 2> r{a1*b1+c/B, a0*b0+c%B*B};
	if(r[1]>=1ll<<62) {
		r[1]-=1ll<<62;
		++r[0];
	}
	return r;
}

bool cmp(const ar<ll, 2> &a, const ar<ll, 2> &b) {
	if(b[0]<0)
		return 0;
	if(a[0]<0)
		return 1;
	ar<ll, 2> a1=mul(a[0], b[1]), b1=mul(b[0], a[1]);
	return a1<b1;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> vx >> vy, vx=-vx, vy=-vy;
	for(int _=0; _<n; ++_) {
		cin >> k;
		for(int i=0; i<k; ++i)
			cin >> x[i] >> y[i];
		memcpy(x+k, x, 4*k);
		memcpy(y+k, y, 4*k);
		for(int i=0; i<k; ++i) {
			if(cp(0, 0, vx, vy, x[i], y[i])<0&&cp(0, 0, vx, vy, x[i+1], y[i+1])>0)
				ae.push_back(intproj(vx, vy, x[i], y[i], x[i+1], y[i+1]));
			if(cp(0, 0, vx, vy, x[i], y[i])>0&&cp(0, 0, vx, vy, x[i+1], y[i+1])<0)
				re.push_back(intproj(vx, vy, x[i], y[i], x[i+1], y[i+1]));
		}
		int s=1;
		while(!cp(0, 0, x[s-1], y[s-1], x[s], y[s]))
			++s;
		for(int i=s, j=s; i<s+k; i=j) {
			for(; !cp(0, 0, x[i], y[i], x[j], y[j]); ++j);
			if(cp(0, 0, vx, vy, x[i], y[i]))
				continue;
			bool b1=cp(0, 0, vx, vy, x[i-1], y[i-1])>0, b2=cp(0, 0, vx, vy, x[j], y[j])>0;
			ar<ll, 2> e1=intproj(vx, vy, x[i], y[i], x[i], y[i]), e2=intproj(vx, vy, x[j-1], y[j-1], x[j-1], y[j-1]);
			if(b1==b2) {
				ae.push_back(min(e1, e2, cmp));
				re.push_back(max(e1, e2, cmp));
			} else if(b2)
				ae.push_back(min(e1, e2, cmp));
			else
				re.push_back(max(e1, e2, cmp));
		}
	}
	sort(ae.begin(), ae.end(), cmp);
	sort(re.begin(), re.end(), cmp);
	ae.erase(ae.begin(), lower_bound(ae.begin(), ae.end(), ar<ll, 2>{0, 1}, cmp));
	re.erase(re.begin(), lower_bound(re.begin(), re.end(), ar<ll, 2>{0, 1}, cmp));
	for(int i1=0, i2=0, c=0; i1<ae.size()-1||i2<re.size()-1; ) {
		if(!cmp(re[i2], ae[i1])) {
			if(!c)
				++ans;
			++c, ++i1;
		} else
			--c, ++i2;
	}
	cout << ans;
}
