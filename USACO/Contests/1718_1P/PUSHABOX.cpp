#include <bits/stdc++.h>
using namespace std;

const int di[]={1, 0, -1, 0}, dj[]={0, 1, 0, -1};

int n, m, q, dt=1, bccI=1, sh, tin[1500][1500], low[1500][1500], bcc[1500][1500][4];
bool dp[1500][1500][4];
string grid[1500];
stack<tuple<int, int, int>> st;

inline bool valid(int i, int j) {
	return i>=0&&i<n&&j>=0&&j<m&&grid[i][j]!='#';
}

void dfs1(int ui, int uj, int p) {
	tin[ui][uj]=low[ui][uj]=dt++;
	for(int k=0; k<4; ++k) {
		int vi=ui+di[k], vj=uj+dj[k], ss=st.size();
		if(!valid(vi, vj)||(k^2)==p)
			continue;
		if(bcc[ui][uj][k]==0)
			st.push(tuple<int, int, int>(ui, uj, k));
		if(tin[vi][vj]==0) {
			dfs1(vi, vj, k);
			low[ui][uj]=min(low[vi][vj], low[ui][uj]);
			if(low[vi][vj]>=tin[ui][uj]) {
				while(st.size()>ss) {
					tuple<int, int, int> t=st.top();
					st.pop();
					bcc[get<0>(t)][get<1>(t)][get<2>(t)]=bcc[get<0>(t)+di[get<2>(t)]][get<1>(t)+dj[get<2>(t)]][get<2>(t)^2]=bccI;
				}
				++bccI;
			}
		} else if(low[ui][uj]>tin[vi][vj])
			low[ui][uj]=tin[vi][vj];
	}
}

bool reachA(int i, int j) {
	if(grid[i][j]=='A')
		return 1;
	tin[i][j]=1;
	for(int k=0; k<4; ++k) {
		int i2=i+di[k], j2=j+dj[k];
		if(valid(i2, j2)&&grid[i2][j2]!='B'&&tin[i2][j2]==0&&reachA(i2, j2))
			return 1;
	}
	return 0;
}

void solve(int i, int j, int k) {
	if(dp[i][j][k])
		return;
	dp[i][j][k]=true;
	int k2=k^2, i2=i+di[k2], j2=j+dj[k2];
	if(valid(i2, j2))
		solve(i2, j2, k);
	for(k2=0; k2<4; ++k2)
		if(valid(i+di[k2], j+dj[k2])&&bcc[i][j][k]==bcc[i][j][k2])
			solve(i, j, k2);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	//freopen("pushabox.in", "r", stdin);
	//freopen("pushabox.out", "w", stdout);

	cin >> n >> m >> q;
	int bi=-1, bj=-1;
	for(int i=0; i<n; ++i) {
		cin >> grid[i];
		for(int j=0; j<m; ++j) {
			if(grid[i][j]=='B') {
				bi=i;
				bj=j;
			}
		}
	}
	dfs1(bi, bj, -1);
	for(int i=0; i<4; ++i) {
		memset(tin, 0, sizeof(tin));
		if(valid(bi+di[i], bj+dj[i])&&reachA(bi+di[i], bj+dj[i])) {
			solve(bi, bj, i);
			break;
		}
	}
	while(q--) {
		int r, c;
		cin >> r >> c;
		--r, --c;
		cout << ((r==bi&&c==bj)||dp[r][c][0]||dp[r][c][1]||dp[r][c][2]||dp[r][c][3]?"YES":"NO") << "\n";
	}
}
