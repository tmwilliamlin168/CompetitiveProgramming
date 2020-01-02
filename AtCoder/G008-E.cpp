/*
	- Obviously all degrees <= 2
	- Start with nodes with degree = 2
		- Traverse the "cycle", maintaining at most 2 nodes at a time
			- If 3 nodes appear then the answer doesn't exist
		- The answer is multiplied by 2 whenever 2 nodes becomes 1
		- Make sure that if in one state we contain 2 nodes including the root, the other node has degree 0
	- Find the rest of the cycles
		- Each cycle can be single or "merged" into another cycle with the same size
		- Odd cycles have 2 different ways to be single
		- Use DP to count the ways to arrange the cycles
*/

#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int mxN=1e5, M=1e9+7;
int n, c[mxN+1];
vector<int> a[mxN];
bool b[mxN];
ll ans=1, d[mxN+1];

void fk() {
	cout << 0;
	exit(0);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n;
	for(int i=0, b; i<n; ++i) {
		cin >> b, --b;
		a[b].push_back(i);
	}
	for(int i=0; i<n; ++i)
		if(a[i].size()>2)
			fk();
	for(int i=0; i<n; ++i) {
		if(b[i]||a[i].size()<2)
			continue;
		int u1=a[i][0], u2=a[i][1];
		while(1) {
			if(u2==i)
				swap(u1, u2);
			if(u1==i)
				break;
			b[u1]=1;
			vector<int> v=a[u1];
			if(~u2) {
				v.insert(v.end(), a[u2].begin(), a[u2].end());
				b[u2]=1;
			}
			if(v.size()>2||!v.size())
				fk();
			u1=v[0];
			if(v.size()>1)
				u2=v[1];
			else {
				ans=ans*(1+(u2>=0))%M;
				u2=-1;
			}
		}
		b[u1]=1;
		if(~u2) {
			if(a[u2].size())
				fk();
			b[u2]=1;
		}
	}
	for(int i=0; i<n; ++i) {
		if(b[i])
			continue;
		int s=0;
		for(int u=i; !b[u]; u=a[u][0]) {
			b[u]=1;
			++s;
		}
		++c[s];
	}
	d[0]=1;
	for(int i=1; i<=n; ++i) {
		for(int j=1; j<=c[i]; ++j)
			d[j]=(d[j-1]*(i&1&&i>1?2:1)+(j>1?d[j-2]*(j-1)%M*i:0))%M;
		ans=ans*d[c[i]]%M;
	}
	cout << ans;
}
