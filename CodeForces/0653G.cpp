/*
	- https://codeforces.com/blog/entry/43886?#comment-285258
*/

#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int mxN=3e5, M=1e9+7;
int n, ti;
ll iv[mxN], f1[mxN], f2[mxN], a1, b1[mxN+1];
map<int, vector<int>> mp;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	for(int i=0; i<n; ++i) {
		cin >> ti;
		for(int j=2; j*j<=ti; ++j) {
			if(ti%j)
				continue;
			int c=0;
			while(ti%j==0) {
				++c;
				ti/=j;
			}
			mp[j].push_back(c);
		}
		if(ti>1)
			mp[ti].push_back(1);
	}
	iv[1]=1;
	for(int i=2; i<n; ++i)
		iv[i]=M-(M/i)*iv[M%i]%M;
	f1[0]=f2[0]=1;
	for(int i=1; i<n; ++i) {
		f1[i]=f1[i-1]*i%M;
		f2[i]=f2[i-1]*iv[i]%M;
	}
	for(int i=0; i<n; ++i)
		b1[i+1]=(b1[i]+f1[n-1]*f2[i]%M*f2[n-1-i])%M;
	for(auto it=mp.begin(); it!=mp.end(); ++it) {
		vector<int> &v=it->second;
		sort(v.begin(), v.end());
		for(int i=1; i<=v.size(); ++i)
			a1+=v[v.size()-i]*(b1[n-i]-b1[i-1]+M)%M;
	}
	cout << a1%M;
}
