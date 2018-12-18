#include <bits/stdc++.h>
using namespace std;

const int mxN=100;
int n, k;
string g[mxN];
bool vis[mxN][10];

vector<array<int, 2>> getNeighbors(array<int, 2> u) {
	vector<array<int, 2>> v;
	if(u[0])
		v.push_back({u[0]-1, u[1]});
	if(u[0]<n-1)
		v.push_back({u[0]+1, u[1]});
	if(u[1])
		v.push_back({u[0], u[1]-1});
	if(u[1]<9)
		v.push_back({u[0], u[1]+1});
	return v;
}

int findSize(array<int, 2> u) {
	int s=1;
	vis[u[0]][u[1]]=1;
	for(array<int, 2> v : getNeighbors(u))
		if(!vis[v[0]][v[1]]&&g[v[0]][v[1]]==g[u[0]][u[1]])
			s+=findSize(v);
	return s;
}

void erase(array<int, 2> u) {
	char oc=g[u[0]][u[1]];
	g[u[0]][u[1]]='0';
	for(array<int, 2> v : getNeighbors(u))
		if(g[v[0]][v[1]]==oc)
			erase(v);
}

int main() {
	ifstream cin("mooyomooyo.in");
	ofstream cout("mooyomooyo.out");
	
	//input
	cin >> n >> k;
	for(int i=0; i<n; ++i)
		cin >> g[i];
	//simulate the process
	while(1) {
		bool changed=0;
		//find components to erase
		memset(vis, 0, n*sizeof(vis[0]));
		for(int i=0; i<n; ++i) {
			for(int j=0; j<10; ++j) {
				if(g[i][j]!='0'&&!vis[i][j]&&findSize({i, j})>=k) {
					erase({i, j});
					changed=1;
				}
			}
		}
		if(!changed)
			break;
		//move things down
		for(int j=0; j<10; ++j) {
			//two pointers
			int i1=n-1;
			for(int i2=n-1; i2>=0; --i2)
				if(g[i2][j]!='0')
					g[i1--][j]=g[i2][j];
			for(; i1>=0; --i1)
				g[i1][j]='0';
		}
	}
	//output
	for(int i=0; i<n; ++i)
		cout << g[i] << "\n";
}
