#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int mxN=3e5;
int n, k, ai, bi, c[mxN], lb=1, rb=1e9;
ll a1, a2, s2;
map<int, int> mp{{1, -1}, {1e9, -1}};
vector<array<int, 2>> tp[mxN];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> k;
	for(int i=0; i<n; ++i) {
		cin >> ai >> bi;
		mp.insert({bi, (--mp.upper_bound(bi))->second});
		mp.insert({ai, (--mp.upper_bound(ai))->second});
		auto it=mp.find(ai);
		while(it->first<bi) {
			tp[i].push_back({it->second, it->first});
			it=mp.erase(it);
			tp[i].back()[1]-=it->first;
		}
		mp[ai]=i;
		tp[i].push_back({i, bi-ai});
	}
	while(lb<=rb) {
		int mb=(lb+rb)/2;
		a1=a2=s2=0;
		for(int i1=0, i2=-1, s1=0; i1<n; a1+=i2+1, a2+=s2, ++i1) {
			for(array<int, 2> a : tp[i1]) {
				if(a[0]==-1)
					continue;
				c[a[0]]+=a[1];
				if(i2<=a[0])
					s1+=a[1];
				s2+=(ll)min(a[0]+1, i2+1)*a[1];
			}
			while(i2+1<=i1&&s1-(i1==-1?0:c[i2])>=mb) {
				s1-=(i1==-1?0:c[i2++]);
				s2+=s1;
			}
		}
		if(a1>=k)
			lb=mb+1;
		else
			rb=mb-1;
		memset(c, 0, 4*n);
	}
	cout << a2+(k-a1)*rb;
}
