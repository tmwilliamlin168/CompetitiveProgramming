/*
	- For the first graph, we can construct powers of 2 by using the structure of a complete graph
	- For the second graph, we can construct the fibonacci sequence
		- There is a well-known fact that we can represent x < F_n as the sum of non-adjacent fibonacci numbers below F_n
		- This makes sure that the number of edges does not exceed 214
*/

#include <bits/stdc++.h>
using namespace std;

#define ll long long

ll a;
vector<ll> v[2];
vector<array<int, 3>> adj[2];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	v[0]=v[1]={1, 1};
	adj[0]=adj[1]={{0, 1, 1}};
	for(int i=2; i<61; ++i) {
		v[0].push_back(1ll<<i-1);
		for(int j=0; j<i; ++j)
			adj[0].push_back({j, i, i-j});
	}
	for(int i=2; i<87; ++i) {
		v[1].push_back(v[1][i-1]+v[1][i-2]);
		adj[1].push_back({i-2, i, 2});
		adj[1].push_back({i-1, i, 1});
	}
	while(1) {
		cin >> a;
		if(a<0)
			break;
		for(int k : {0, 1}) {
			vector<array<int, 3>> ee;
			ll a2=a;
			for(int i=v[k].size()-1; ~i; --i) {
				if(a2>=v[k][i]) {
					a2-=v[k][i];
					ee.push_back({i+2, 1, 96-i});
				}
			}
			cout << "YES\n" << v[k].size()+1 << " " << adj[k].size()+ee.size() << "\n";
			for(array<int, 3> e : adj[k])
				cout << e[0]+2 << " " << e[1]+2 << " " << e[2] << "\n";
			for(array<int, 3> e : ee)
				cout << e[0] << " " << e[1] << " " << e[2] << "\n";
		}
	}
}
